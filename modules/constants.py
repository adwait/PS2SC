""" CSeq Constant Propagation module
    written by Omar Inverso, University of Southampton
    maintained by Truc Nguyen Lam, University of Southampton
"""
VERSION = 'constants-1.0-2020.06.18' # SwInG
# VERSION = 'constants-0.0-2014.12.24'  # CSeq-1.0beta
# #VERSION = 'constants-0.0-2014.12.09'
# ##VERSION = 'constants-0.0-2014.10.26'    # CSeq-Lazy-0.6: newseq-0.6a, newseq-0.6c, SVCOMP15
# ###VERSION = 'constants-0.0-2014.10.15'
# ####VERSION = 'constants-0.0-2014.03.14' (CSeq-Lazy-0.4)
# #####VERSION = 'constants-0.0-2014.02.25' (Cseq-Lazy-0.2)

"""
    Optimization 1:
    Constant expression simplifications: change  20 + 3  --->  23
    Optimization 2:
    Simple workaround for expression that contains share (global) variables

Limitations:
    Optimization 2:
    - Just use  int  type for the temporary variable
    - Only consider binary operation on the RHS

Changelog:
    2016.10.24  add fix for changing variable in assignment
    2015.10.22  add fix for ldv-races category in SVCOMP16
    2014.12.09  further code refactory to match the new organisation of the CSeq framework
    2014.10.26  removed dead/commented-out/obsolete code
    2014.10.15  removed visit() and moved visit call-stack handling to module class (module.py)
    2014.03.14  further code refactory to match  module.Module  class interface
    2014.02.25  switched to  module.Module  base class for modules

"""
import pycparser.c_parser, pycparser.c_ast, pycparser.c_generator
import core.common, core.module, core.parser, core.utils
import re


import sys
from collections import OrderedDict

class MyParser(pycparser.c_generator.CGenerator):
    def __init__(self):
        self.__considervar = ''
        self.__hasConsidervar = False

    def setConsidervar(self, string):
        self.__considervar = string

    def getHasConsidervar(self):
        return self.__hasConsidervar

    def setHasConsidervar(self, value):
        self.__hasConsidervar = value

    def visit(self, node):
        method = 'visit_' + node.__class__.__name__
        ret = getattr(self, method, self.generic_visit)(node)
        if ret == self.__considervar:
            self.__hasConsidervar = True
        return ret


class constants(core.module.Translator):
    __temp_var_no = -1
    __globalMemoryAccessed = False
    __currentFunction = ''
    __atomicSection = False
    # Use another parser to avoid breaking line mapping system
    __myparser = MyParser()


    # new additions for SwInG
    # new variable additions
    __active_threads = 0
    __isAtomicOpen = False
    # __atomicSection =  False
    __atomicPrint = 0
    __globalVarsStack = []
    # __once_create = True
    # __initialisations = {} ... is not used in code
    __initialisations = {}
    __ps_rounds = 1
    __ps_goto_helper_dict = {}
    __ps_threadgoto_pointer_dict = {}

    # Use another parser to avoid breaking line mapping system
    __labelcounter = 0
    __to_declare_local_vars = True
    __write_seen = False
    __can_promise = True
    __atomic_open = False
    __enable_prom = ''


    def init(self):
        self.addInputParam('ee', 'Essential Events', 'int', '1', False)
        self.addInputParam('anno', 'Annotated Speculation', 'int', '0', False)
        self.addInputParam('eprom', 'Are promises enabled for thread?', 'string', '0', False)

    def loadfromstring(self, string, env):
        self.__ps_rounds = int(env.paramvalues['ee'])
        self.__anno = int(env.paramvalues['anno'])
        if 'prom' in env.paramvalues:
            self.__can_promise = (env.paramvalues['prom'] != '0')
        if 'eprom' in env.paramvalues:
            self.__enable_prom = str(env.paramvalues['eprom'])
        else:
            self.__enable_prom = ''

        super(self.__class__, self).loadfromstring(string, env)

    # helper functions

    # tracking reads from control
    '''
    maybe not required if we specify the memory 
    accesses as explicit function calls
    
    def _is_read_class(self, node):
        return node.__class__.__name__ in ['Assignment', 'FuncCall', 'If', 'For', 'While']
    '''

    def _is_array_type(self, var_name):
        return self.Parser.varArity[('', var_name)] != 0

    def _skip_ps_ops(self):
        return self.__currentFunction == 'main' and self.__active_threads == 0

    def get_array_ref(self, node):
        indices = ''
        tnode = node

        while not isinstance(tnode, pycparser.c_ast.ID):
            if isinstance(tnode.subscript, pycparser.c_ast.ID):
                indices = '[' + tnode.subscript.name + ']' + indices
            else:
                indices = '[' + tnode.subscript.value + ']' + indices

        return tnode.name + indices

    def get_read_stats(self):
        retval = ''
        for gVar in set(self.__globalVarsStack.pop()):
            retval += '%s(%s);\n' % (self.reserved_functions[0], gVar)

        return retval

    def get_write_stats(self):
        retval = ''
        return ';\n%s(%s)' % (self.reserved_functions[1], self.get_array_ref(node)) 

    # add the unavail, upd variables
    def initialise_helper_vars(self):
        # print 'psords' + str(self.__ps_rounds)
        s = ''
        s += 'unsigned int helper_temporary = 1;\n'
        for gVar in self.Parser.varNames['']:
            if not gVar.startswith('__cs'):
                for indices in self.gen_all(self.Parser.varSize[('', gVar)]):
                    s += '%s_%s%s[0] = 1;\n' % (self._helper_names('unavail'), gVar, indices)
                    s += '%s_%s%s[0] = 1;\n' % (self._helper_names('upd'), gVar, indices)
                    # s += '%s_%s%s[0] = 0;\n' % (self._helper_names('usedReservations'), gVar, indices)
        # not required due to auto initialisation to zero for global variables
        # s += '%s[0] = 0;\n' % (self._helper_names('checkMode'))
        # s += '%s[0] = 0;\n' % (self._helper_names('active'))
        return s

    # generates all possible indices for n-dim array
    def gen_all(self, arities):
        s = []
        if len(arities) == 0:
            return ['']
        rec = self.gen_all(arities[1:])
        for k in range(arities[0]):
            for h in rec:
                s.append('[' + str(k) + ']' + h)
        return s

    def get_local_view_name(self):
        if self.__currentFunction=="main":
            return self._helper_names('view_main')
        return '_view'


    # -------
    # need to add more variables here
    # -------
    # per globvar variables view, liveChain and extView to main 
    # (these may copied to other threads by the merge view function)
    def initialise_struct_view(self):
        # view_name = self.get_local_view_name()
        s = ''
        if self.__currentFunction == "main":
            if self.__can_promise:
                for k in self.Parser.varNames['']:
                    if not k.startswith('__cs'):
                        for indices in self.gen_all(self.Parser.varSize[('', k)]):
                            s += k + "_view" + "_l%s[0] = 1;\n" % indices
                            s += k + "_view" + "_u%s[0] = 1;\n" % indices
                            s += k + "_liveChain" + "%s[0] = 0;\n" % indices
                            s += k + "_extView" + "%s[0] = 1;\n" % indices
                            s += k + "_blockPromise" + "%s[0] = 0;\n" % indices
                            # s += k + "_usedReservations" + "%s[0] = 0;\n" % indices
                            s += k + "_view_v%s[0] = 1;\n" % indices
            else:
                for k in self.Parser.varNames['']:
                    if not k.startswith('__cs'):
                        for indices in self.gen_all(self.Parser.varSize[('', k)]):
                            s += k + "_view" + "_l%s[0] = 1;\n" % indices
                            s += k + "_view" + "_u%s[0] = 1;\n" % indices
                            # new addition for sc-fences
                            s += k + "_view" + "_v%s[0] = 1;\n" % indices
        return s

    
    # -------
    # need to add more variables here
    # -------
    # global variables to copy local state into
    def declare_local_vars(self):
        s = ''
        # done = []
        for th in self.Parser.threadName:
            thname = '_'.join(th.split('_')[:-1])
            for k in self.Parser.varNames[th]:
                if '__cs_unused' not in k:
                    tup = (th, k)
                    decl_str = ''
                    for p in self.Parser.varSize[tup]:
                        decl_str = decl_str + '[' + str(p) + ']'
                    s += self.Parser.varTypeUnExpanded[tup] + " __cs_pscopy_%s_%s%s;\n" % (th, k, decl_str)
            # done.append(thname)
        return s

    # -------
    # need to add more variables here
    # -------
    # local helper variables + preinitialized copy in top-scope of process
    # required for setting up local variables state in helper function 
    def define_local_vars(self):
        s = ''
        # may need to add more helper vars here (check_later())
        s += "static unsigned int _ps_non_det_int_var;\n"
        s += "static _Bool _ps_non_det_bool_var;\n"
        if 'pscopy' in self.__currentFunction:
            parentthread = '_'.join(self.__currentFunction.split('_')[:-1])
            for k in self.Parser.varNames[parentthread]:
                if k.startswith('__cs'):
                    continue
                tup = (parentthread, k)
                decl_str = ''
                for p in self.Parser.varSize[tup]:
                    decl_str = decl_str + '[' + str(p) + ']'
                s += self.Parser.varTypeUnExpanded[tup] + " %s%s;\n" % (k, decl_str)
                for indices in self.gen_all(self.Parser.varSize[tup]):
                    s += "%s%s = __cs_pscopy_%s_%s%s;\n" % (k, indices, parentthread, k, indices)
        elif self.__currentFunction in self.Parser.threadName and self.__can_promise and self.__enable_prom in self.__currentFunction:
            for k in self.Parser.varNames[self.__currentFunction]:
                if k.startswith('__cs'):
                    continue
                tup = (self.__currentFunction, k)
                decl_str = ''
                for p in self.Parser.varSize[tup]:
                    decl_str = decl_str + '[' + str(p) + ']'
                s += self.Parser.varTypeUnExpanded[tup] + " %s%s;\n" % (k, decl_str)
        done = []
        for v, k in self.Parser.varTypeUnExpanded:
            type_temp = self.Parser.varTypeUnExpanded[(v, k)]
            if v == '' and type_temp not in done:
                s += "%s _%s_update_helper_var;\n"%(type_temp, type_temp)
                done.append(type_temp)
        return s

    # load local variables when switching mode
    def get_loadhelper_stats(self):
        s = ''
        for k in self.Parser.varNames[self.__currentFunction]:
            if k.startswith('__cs'):
                continue
            tup = (self.__currentFunction, k)
            for indices in self.gen_all(self.Parser.varSize[tup]):
                s += '__cs_pscopy_%s_%s%s = %s%s;\n' % (self.__currentFunction, k, indices, k, indices)
        return s


    # -------
    # need to add more variables here
    # -------
    # atomic statements for guessing thread context switches, 'active' keeps track of thread states
    # for ending, promises are made and consistency checker is called
    # added only to the parent threads and not the helper functions (or main)
    # also labels and checkMode are no more required
    def get_atomic_stmt(self, isBegin):
        s = ''
        p = ''
        if isBegin:
            if self.__can_promise and self.__enable_prom in self.__currentFunction:
                s += '\n\nif(%s[ps_thread_num] == 0){\n' % (self._helper_names("active"))
                s += '  %s;\n' % ('__CSEQ_atomic_begin()')
                s += '  %s[ps_thread_num] = 1;\n'  % (self._helper_names("active"))
                s += '}\n\n'
            else:
                s += '  %s;\n' % ('__CSEQ_atomic_begin()')
        else:
            if self.__can_promise and self.__enable_prom in self.__currentFunction:
                labelind = 0
                if self.__currentFunction in self.__ps_goto_helper_dict.keys():
                    labelind = self.__ps_goto_helper_dict[self.__currentFunction]
                self.__ps_goto_helper_dict[self.__currentFunction] = labelind + 1
                for pint in range(1):
                    s = ''
                    s += 'if(nondet_bool()){\n'
                    s += '      if(%s[ps_thread_num] == 0){\n' % (self._helper_names("active"))
                    s += '          %s;\n' % ('__CSEQ_atomic_begin()')
                    s += '          %s[ps_thread_num] = 1;\n' % (self._helper_names("active"))
                    s += '      }\n'
                    s += '      %s[ps_thread_num] = %s;\n' % (self._helper_names('retAddr'), labelind)
                    s += '      %s();\n'  % (self.reserved_functions['save'])
                    s += self.get_loadhelper_stats()
                    s += '      %s(ps_thread_num);\n' % (self.__currentFunction + '_pscopy')
                    s += '      %s();\n' % (self.reserved_functions['conscheck'])
                    s += '      %s();\n' % (self.reserved_functions['load'])
                    s += '      %s[ps_thread_num] = 0;\n' % (self._helper_names('active'))
                    s += '      %s;\n' % ('__CSEQ_atomic_end()')
                    s += p
                    s += '}\n'
                    p = s
            else:
                s += '      %s;\n' % ('__CSEQ_atomic_end()')
        return s


    # add goto in helper function (move to current position)
    def get_helpergoto_stats(self):
        s = ''
        parentthread = '_'.join(self.__currentFunction.split('_')[:-1])
        if parentthread in self.__ps_goto_helper_dict.keys():
            s += 'if(%s[_ps_t1] < 0){\n' % (self._helper_names('retAddr'))
            s += '  \n}\n'
            for val in range(self.__ps_goto_helper_dict[parentthread]):
                s += 'else if(%s[_ps_t1] == %s){\n' % (self._helper_names('retAddr'), str(val))
                s += '  goto %s_pslabel_%s;\n}\n' % (self.__currentFunction, str(val))
        return s

    def get_simple_atomic_stmt(self):
        s = ''
        s += '  if(%s[ps_thread_num] == 1){\n' % (self._helper_names("active"))
        s += '      %s[ps_thread_num] = 0;\n' % (self._helper_names("active"))
        s += '      %s;\n' % ('__CSEQ_atomic_end()')
        s += '  }\n'
        return s
    
    def get_simple_helperexit_stmt(self):
        parentthread = '_'.join(self.__currentFunction.split('_')[:-1])
        s = ''
        s += '  goto __exit_%s;\n' % (parentthread)
        return s
                    
    # add label in helper function at each possible context switch point
    def get_helperlabel_stats(self):
        labelind = 0
        parentthread = '_'.join(self.__currentFunction.split('_')[:-1])
        if parentthread in self.__ps_threadgoto_pointer_dict.keys():
            labelind = self.__ps_threadgoto_pointer_dict[parentthread]
        self.__ps_threadgoto_pointer_dict[parentthread] = labelind + 1
        # self.__labelcounter += 1
        return '%s_pslabel_%s: ;\n' % (self.__currentFunction, str(labelind))

    # add nondeterminisitc exit from helper function at each possible context switch point
    def get_helperexit_stats(self):
        parentthread = '_'.join(self.__currentFunction.split('_')[:-1])
        s = ''
        s += 'if(nondet_bool()){\n'
        s += '  goto __exit_%s;\n' % (parentthread)
        s += '}\n'
        return s

    # atomic exit for end of thread (called during exit label generation)
    # added only to the parent threads and not the helper functions (or main)
    def exit_atomic_stmt(self):
        s = ''
        s += '\nif(%s[ps_thread_num] == 1){\n' % (self._helper_names("active"))
        s += '  %s();\n' % (self.reserved_functions['conscheck'])
        s += '  %s[ps_thread_num] = 0;\n' % (self._helper_names('active'))
        s += '  %s;\n' % ('__CSEQ_atomic_end()')
        s += '}\n'
        return s

    # is fun amongst main, threads, threadcopies
    # def _is_function_thread(self, fun):
    #     return fun in self.threadName or fun == "main" or 'pscopy' in fun


    def visit_FuncDef(self, n):
        self.__currentFunction = n.decl.name
        decl = self.visit(n.decl)
        self.__atomicSection = False
        if n.decl.name.startswith("__CSEQ_atomic_"):
            self.__atomicSection = True
        self.indent_level = 0

        tempDecl = ''
        # declare copies of local vars into global scope 
        # for pscopy to access
        if self.__to_declare_local_vars and self.__can_promise:
            decl = self.declare_local_vars() + decl
            self.__to_declare_local_vars = False
        # this is not required since we manually will insert
        # speculation positions?
        if self.__currentFunction in self.Parser.threadName and self.__can_promise and self.__enable_prom in self.__currentFunction:
            self.__atomic_open = True
            self.__write_seen = True

        body = self.visit(n.body)
        
        if self.__currentFunction in self.Parser.threadName or self.__currentFunction == "main" or 'pscopy' in self.__currentFunction:
            if self.__currentFunction == "main":
                tempDecl += self.initialise_helper_vars() + self.initialise_struct_view()
            tempDecl += self.define_local_vars()
            # define local vars at the top o
            # if self.__currentFunction in self.Parser.threadName and self.__currentFunction != 'main' and 'pscopy' not in self.__currentFunction and self.__can_promise:
            #     tempDecl = tempDecl  # + self.get_atomic_stmt(False)  ... not needed at start of thread
            if 'pscopy' in self.__currentFunction:
                tempDecl = tempDecl + self.get_helpergoto_stats() # + self.get_helperlabel_stats()  + self.get_helperexit_stats() ... not needed at start of thread
            elif self.__currentFunction in self.Parser.threadName and self.__currentFunction != 'main' and (not self.__can_promise or self.__enable_prom not in self.__currentFunction): #<review>
                tempDecl = tempDecl + self.get_atomic_stmt(True)
                # self.__atomic_open = True     # keep ttrack of open atmoic environments
            # <review> removed 
            # if 'pscopy' in self.__currentFunction or self.__can_promise:
            body = '{\n' + tempDecl + body + '}\n'
            # elif self.__currentFunction in self.Parser.threadName and self.__currentFunction != 'main': #<review>
            #     body = '{\n' + tempDecl + body + self.get_atomic_stmt(False) + '}\n'

        self.__currentFunction = ''
        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            return decl + '\n' + body + '\n'

    def visit_Label(self, n):
        prefix = ''
        if self.__can_promise and self.__currentFunction != 'main' and 'exit' in n.name and 'pscopy' not in self.__currentFunction and self.__enable_prom in self.__currentFunction:
            # prefix = self.get_atomic_stmt(True) + self.get_promise_stats() + self.get_atomic_stmt(False) + self.get_goto_stats(n.name)
            prefix = self.exit_atomic_stmt() # + self.get_goto_stats(n.name)
        elif self.__currentFunction != 'main' and 'exit' in n.name and (not self.__can_promise or self.__enable_prom not in self.__currentFunction):
            prefix = self.get_atomic_stmt(False)
        # if self.__isAtomicOpen and self.__currentFunction!='main' and 'exit' in n.name:
        #     prefix=self.get_atomic_stmt(0) #Close remaining atomic_open
        return prefix + n.name + ':\n' + self._generate_stmt(n.stmt)


    def visit_Assignment(self, n):
        oldGlobalMemoryAccessed = self.__globalMemoryAccessed
        globalAccess = False
        self.__globalMemoryAccessed = False
        lval_str = self.visit(n.lvalue)

        # Optimization 2
        self.__myparser.setConsidervar(lval_str)
        self.__myparser.setHasConsidervar(False)
        self.__myparser._parenthesize_if(n.rvalue, lambda n: isinstance(n, pycparser.c_ast.Assignment))

        rval_str = self._parenthesize_if(n.rvalue, lambda n: isinstance(n, pycparser.c_ast.Assignment))
        globalAccess = self.__globalMemoryAccessed

        ret = ''
        if (not self.__atomicSection and
                globalAccess and
                type(n.rvalue) == pycparser.c_ast.BinaryOp and
                self.__myparser.getHasConsidervar() and
                self.__getType(self.__currentFunction, lval_str) != "UNKNOWN"
            ):
            self.__temp_var_no += 1    # Declare a temporary variable for this statement
            ret = '; %s __cs_temporary_%s = 0; __cs_temporary_%s = %s; ' % (self.__getType(self.__currentFunction, lval_str), self.__temp_var_no, self.__temp_var_no, lval_str)
            newrval_str = " " + rval_str + " "
            newrval_str = newrval_str.replace(" %s " % lval_str, ' __cs_temporary_%s ' % self.__temp_var_no, 1).strip()
            ret += '%s %s %s' % (lval_str, n.op, newrval_str)
        else:
            ret = '%s %s %s' % (lval_str, n.op, rval_str)

        return ret


    def visit_ID(self, n):
        # If this ID corresponds either to a global variable,
        # or to a pointer...
        #
        
        if n.name.startswith('__cs'):
            return n.name
        if self.__isGlobal(self.__currentFunction, n.name) and 'main' in self.__currentFunction:
            self.__globalMemoryAccessed = True
            return n.name + '_view' + '[ps_thread_num]'
        
        if ((self.__isGlobal(self.__currentFunction, n.name) or self.__isPointer(self.__currentFunction, n.name)) and not n.name.startswith('__cs_thread_local_')):
            self.__globalMemoryAccessed = True

        return n.name


    # Checks whether variable  v  from function  f  is a pointer.
    #
    def __isPointer(self, f, v):
        if v in self.Parser.varNames[f] and self.Parser.varType[f,v].endswith('*'): return True
        elif v in self.Parser.varNames[''] and self.Parser.varType['',v].endswith('*'): return True
        else: return False


    # Checks whether variable  v  from function  f  is global.
    #
    def __isGlobal(self, f, v):
        if (v in self.Parser.varNames[''] and v not in self.Parser.varNames[f]): return True
        else: return False

    def __getType(self, f, v):
        if (v in self.Parser.varNames[f]):
            return self.Parser.varType[f, v]
        elif '.' in v:  # This variable is a field
            # TODO: this needs proper implementation, quick hack for ldv-races
            return 'int'
        else:
            return "UNKNOWN"

    def visit_FuncCall(self, n):
        fref = self._parenthesize_unless_simple(n.name)
        _is_reserved = self.is_function_reserved(n)
        if fref == "__CS_atomic_begin":
            self.__atomicSection = True
        elif fref == "__CS_atomic_end":
            self.__atomicSection = False

        if fref=="__cs_create" and self.__currentFunction=='main':
            self.__active_threads = self.__active_threads+1
            # self.__once_create = True
        elif fref=="__cs_join" and self.__currentFunction=='main':
            self.__active_threads = self.__active_threads-1

        # if _is_reserved:
        if n.name.name == self.reserved_functions['fence']:
            if 'pscopy' in self.__currentFunction:
                return self.get_simple_helperexit_stmt() + fref + '();\n'
            elif (not self.__can_promise or self.__enable_prom not in self.__currentFunction):
                self.__write_seen = True
                return self.get_atomic_stmt(False) + self.get_atomic_stmt(True) + fref + '();\n' 
            return self.get_simple_atomic_stmt() + self.get_atomic_stmt(True) + fref + '();\n'
        
        # needs to be thought out well
        # use a uniform speculation strategy in the main process and the pscopy_helper
        # currently allows switches only before reads 
        elif n.name.name.startswith('rlx_') or n.name.name.startswith('ra_'): # n.name.name == self.reserved_functions['read_rlx'] or n.name.name == self.reserved_functions['read_ra']:
            if self.__can_promise  and self.__enable_prom in self.__currentFunction:
                if 'pscopy' in self.__currentFunction:
                    prefix = self.get_helperlabel_stats() + self.get_helperexit_stats()
                elif self.__currentFunction in self.Parser.threadName and self.__currentFunction != "main":
                    prefix = self.get_atomic_stmt(False) + self.get_atomic_stmt(True)
            elif 'read' in n.name.name:
                prefix = self.get_atomic_stmt(False) + self.get_atomic_stmt(True)
            else:
                prefix = ''

            args = self.visit(n.args)
            return prefix + fref + '(' + args + ')'

            # handle global reads explicitly in lazyseqnew schedule
            # else:
                # first_arg = n.args.exprs[0]
                # args = self.get_array_ref(n.args.exprs[0])
                # mod_arg = ''
                # for k in n.args.exprs[1:]:
                #     args += ', ' + self.visit(k) 
                # if n.name.name == self.reserved_functions[1]:
                #     view_name = self.get_local_view_name()
                #     temp= self.get_local_view_name()+"." + self.get_array_ref(n.args.exprs[0]) + "="+self.visit(n.args.exprs[1])+";\n"
                #     fref = temp+fref
                # elif n.name.name == self.reserved_functions[2]:
                #     temp = self.get_update_var(n.args.exprs[0]) + " ="+self.visit(n.args.exprs[1])+";\n"
                #     fref = temp+fref
        else:    
            args = self.visit(n.args)
        return fref + '(' + args + ')'



        args = self.visit(n.args)
        return fref + '(' + args + ')'


    def visit_BinaryOp(self, n):
        lval_str = self._parenthesize_if(n.left, lambda d: not self._is_simple_node(d))
        rval_str = self._parenthesize_if(n.right, lambda d: not self._is_simple_node(d))

        if n.op == '-' and self._isInteger(lval_str) and self._isInteger(rval_str):
            return str(int(lval_str) - int(rval_str))
        if n.op == '+' and self._isInteger(lval_str) and self._isInteger(rval_str):
            return str(int(lval_str) + int(rval_str))
        if n.op == '*' and self._isInteger(lval_str) and self._isInteger(rval_str):
            return str(int(lval_str) * int(rval_str))
        if n.op == '/' and self._isInteger(lval_str) and self._isInteger(rval_str):
            return str(int(lval_str) / int(rval_str))

        return '%s %s %s' % (lval_str, n.op, rval_str)


    def _isInteger(self, s):
        if s[0] in ('-', '+'): return s[1:].isdigit()
        else: return s.isdigit()
        