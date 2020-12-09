""" CSeq backend instrumentation module
    written by Omar Inverso, Truc Nguyen Lam, University of Southampton.
"""
VERSION = 'instrumenter-0.1-2016.08.09'
# VERSION = 'instrumenter-0.0-2015.07.15'
# VERSION = 'instrumenter-0.0-2015.07.09'
#VERSION = 'instrumenter-0.0-2015.06.25'
"""
    Transformation 1 (convert function calls and add implementation):
        __CSEQ_assert()   -->   verifier-specific assert
        __CSEQ_assume()   -->   verifier-specific assume

    Transformation 2 (convert bitvectors)
        convert any  int  or  unsigned int  for which there is
        __CSEQ_bitvector[k] --> ...

    Transformation 3 (raw line injections and indentation):
        __CSEQ_rawline("string"); --> string

        this transformation uses
        separate indentation for raw and non-raw lines, where
        a raw line is a line inserted by __CSEQ_rawline()
        any other line is non-raw.
        Raw line are indentend fully left,
        non-raw are shifted to the right.

TODO:
    - Add bitvector option to esbmc backend
    - Deal with typedef

Changelog:
    2017.04.07  add linearizability header
    2017.02.24  add smack backend
    2017.02.23  add UAutomizer backend
    2016.12.06  add fix to type not integer (long)
    2016.12.02  add round integer types options
    2016.11.30  add svcomp option (disable assertions in lock/unlock)
    2016.11.29  disable hashed file number
    2016.09.26  add option to get more (system) headers
    2016.09.14  add more entry to nondet, and extra header to CBMC
    2016.08.15  set bits for structure and array
    2016.08.09  add backend Frama-C
    2015.07.15  back to output.strip to remove fake header content

"""
from time import gmtime, strftime
import math, re
import core.module, core.utils, core.common
import pycparser.c_ast

_backends = ['cbmc', 'esbmc', 'llbmc', 'blitz', 'satabs',
            '2ls', 'klee', 'cpachecker', 'framac', 'uautomizer',
            'smack']

fmap = {}

fmap['cbmc', '__CSEQ_assume'] = '__CPROVER_assume'
fmap['cbmc', '__CSEQ_assertext'] = '__CPROVER_assert'
fmap['cbmc', '__CSEQ_assert'] = 'assert'
fmap['cbmc', '__CSEQ_nondet_int'] = 'nondet_int'
fmap['cbmc', '__CSEQ_nondet_uint'] = 'nondet_uint'
fmap['cbmc', '__CSEQ_nondet_bool'] = 'nondet_bool'
fmap['cbmc', '__CSEQ_nondet_char'] = 'nondet_char'
fmap['cbmc', '__CSEQ_nondet_uchar'] = 'nondet_uchar'

fmap['esbmc', '__CSEQ_assume'] = '__ESBMC_assume'
fmap['esbmc', '__CSEQ_assertext'] = '__ESBMC_assert'
fmap['esbmc', '__CSEQ_assert'] = 'assert'
fmap['esbmc', '__CSEQ_nondet_int'] = '__VERIFIER_nondet_int'
fmap['esbmc', '__CSEQ_nondet_uint'] = '__VERIFIER_nondet_uint'
fmap['esbmc', '__CSEQ_nondet_bool'] = '__VERIFIER_nondet_bool'
fmap['esbmc', '__CSEQ_nondet_char'] = '__VERIFIER_nondet_char'
fmap['esbmc', '__CSEQ_nondet_uchar'] = '__VERIFIER_nondet_uchar'

fmap['llbmc', '__CSEQ_assume'] = '__llbmc_assume'
fmap['llbmc', '__CSEQ_assertext'] = '__llbmc_assert'
fmap['llbmc', '__CSEQ_assert'] = '__llbmc_assert'
fmap['llbmc', '__CSEQ_nondet_int'] = 'nondet_int'
fmap['llbmc', '__CSEQ_nondet_uint'] = 'nondet_int'
fmap['llbmc', '__CSEQ_nondet_bool'] = 'nondet_bool'
fmap['llbmc', '__CSEQ_nondet_char'] = 'nondet_char'
fmap['llbmc', '__CSEQ_nondet_uchar'] = 'nondet_uchar'

fmap['blitz', '__CSEQ_assume'] = '__CPROVER_assume'
fmap['blitz', '__CSEQ_assertext'] = 'assert'
fmap['blitz', '__CSEQ_assert'] = 'assert'
fmap['blitz', '__CSEQ_nondet_int'] = 'nondet_int'
fmap['blitz', '__CSEQ_nondet_uint'] = 'nondet_uint'
fmap['blitz', '__CSEQ_nondet_bool'] = 'nondet_bool'
fmap['blitz', '__CSEQ_nondet_char'] = 'nondet_char'
fmap['blitz', '__CSEQ_nondet_uchar'] = 'nondet_uchar'

fmap['satabs', '__CSEQ_assume'] = '__CPROVER_assume'
fmap['satabs', '__CSEQ_assertext'] = 'assert'
fmap['satabs', '__CSEQ_assert'] = 'assert'
fmap['satabs', '__CSEQ_nondet_int'] = 'nondet_int'
fmap['satabs', '__CSEQ_nondet_uint'] = 'nondet_uint'
fmap['satabs', '__CSEQ_nondet_bool'] = 'nondet_bool'
fmap['satabs', '__CSEQ_nondet_char'] = 'nondet_char'
fmap['satabs', '__CSEQ_nondet_uchar'] = 'nondet_uchar'

# fmap['2ls', '__CSEQ_assume'] = '__CPROVER_assume'
# fmap['2ls', '__CSEQ_assertext'] = 'assert'
# fmap['2ls', '__CSEQ_assert'] = 'assert'
# fmap['2ls', '__CSEQ_nondet_int'] = 'nondet_int'
# fmap['2ls', '__CSEQ_nondet_uint'] = 'nondet_uint'

fmap['klee', '__CSEQ_assume'] = 'KLEE_assume'
fmap['klee', '__CSEQ_assertext'] = 'KLEE_assert'
fmap['klee', '__CSEQ_assert'] = 'KLEE_assert'
fmap['klee', '__CSEQ_nondet_int'] = 'KLEE_nondet_int'
fmap['klee', '__CSEQ_nondet_uint'] = 'KLEE_nondet_uint'
fmap['klee', '__CSEQ_nondet_bool'] = 'KLEE_nondet_bool'
fmap['klee', '__CSEQ_nondet_char'] = 'KLEE_nondet_char'
fmap['klee', '__CSEQ_nondet_uchar'] = 'KLEE_nondet_uchar'

fmap['cpachecker', '__CSEQ_assume'] = '__VERIFIER_assume'
fmap['cpachecker', '__CSEQ_assertext'] = '__VERIFIER_assert'
fmap['cpachecker', '__CSEQ_assert'] = '__VERIFIER_assert'
fmap['cpachecker', '__CSEQ_nondet_int'] = '__VERIFIER_nondet_int'
fmap['cpachecker', '__CSEQ_nondet_uint'] = '__VERIFIER_nondet_uint'
fmap['cpachecker', '__CSEQ_nondet_bool'] = '__VERIFIER_nondet_bool'
fmap['cpachecker', '__CSEQ_nondet_char'] = '__VERIFIER_nondet_char'
fmap['cpachecker', '__CSEQ_nondet_uchar'] = '__VERIFIER_nondet_uchar'

fmap['framac', '__CSEQ_assume'] = '__FRAMAC_assume'
fmap['framac', '__CSEQ_assertext'] = '__FRAMAC_assert'
fmap['framac', '__CSEQ_assert'] = '__FRAMAC_assert'
fmap['framac', '__CSEQ_nondet_int'] = '__VERIFIER_nondet_int'
fmap['framac', '__CSEQ_nondet_uint'] = '__VERIFIER_nondet_uint'
fmap['framac', '__CSEQ_nondet_bool'] = '__VERIFIER_nondet_bool'
fmap['framac', '__CSEQ_nondet_char'] = '__VERIFIER_nondet_char'
fmap['framac', '__CSEQ_nondet_uchar'] = '__VERIFIER_nondet_uchar'

fmap['uautomizer', '__CSEQ_assume'] = '__VERIFIER_assume'
fmap['uautomizer', '__CSEQ_assertext'] = '__VERIFIER_assert'
fmap['uautomizer', '__CSEQ_assert'] = '__VERIFIER_assert'
fmap['uautomizer', '__CSEQ_nondet_int'] = '__VERIFIER_nondet_int'
fmap['uautomizer', '__CSEQ_nondet_uint'] = '__VERIFIER_nondet_uint'
fmap['uautomizer', '__CSEQ_nondet_bool'] = '__VERIFIER_nondet_bool'
fmap['uautomizer', '__CSEQ_nondet_char'] = '__VERIFIER_nondet_char'
fmap['uautomizer', '__CSEQ_nondet_uchar'] = '__VERIFIER_nondet_uchar'

fmap['smack', '__CSEQ_assume'] = '__VERIFIER_assume'
fmap['smack', '__CSEQ_assertext'] = '__VERIFIER_assert'
fmap['smack', '__CSEQ_assert'] = '__VERIFIER_assert'
fmap['smack', '__CSEQ_nondet_int'] = '__VERIFIER_nondet_int'
fmap['smack', '__CSEQ_nondet_uint'] = '__VERIFIER_nondet_uint'
fmap['smack', '__CSEQ_nondet_bool'] = '__VERIFIER_nondet_bool'
fmap['smack', '__CSEQ_nondet_char'] = '__VERIFIER_nondet_char'
fmap['smack', '__CSEQ_nondet_uchar'] = '__VERIFIER_nondet_uchar'

_maxrightindent = 40   # max columns right for non-raw lines
_rawlinemarker = '__CSEQ_removeindent'


class instrumenter(core.module.Translator):
    __visiting_struct = False
    __struct_stack = []               # stack of struct name
    __svcomp = False
    __roundint = False

    __avoid_type = []
    __ignore_list = []
    __bit_pthread = False
    __currentFunction = ''
    __can_edit_global_scope = True
    __time_bits = 8
    __ps_rounds = 1
    __can_promise = True
    __enable_prom = ''

    def init(self):
        self.addInputParam('backend','backend to use for analysis, available choices are:\n  bounded model-checkers: (blitz, cbmc, esbmc, llbmc, smack)\n  abstraction-based: (cpachecker, satabs, uautomizer, framac)\n  testing: (klee)','b','cbmc',False)
        self.addInputParam('bitwidth','custom bidwidths for integers','w',None,True)
        self.addInputParam('header', 'raw text file to add on top of the instrumented file', 'h', '', True)
        self.addInputParam('svcomp', 'extra instrumentation for SVCOMP', '', None, True)
        self.addInputParam('roundint', 'round to integer built-in types', '', None, True)
        self.addInputParam('bit-pthread', 'set bit vector for pthread types', '', None, True)
        self.addInputParam('totalThreads', 'total thread\'s seen', '', None, True)

    def loadfromstring(self,string,env):
        self.env = env
        self.__ps_rounds = int(env.paramvalues['ee'])
        if 'prom' in env.paramvalues:   
            self.__can_promise = (env.paramvalues['prom'] != '0')

        if 'eprom' in env.paramvalues:
            self.__enable_prom = str(env.paramvalues['eprom'])
        else:
            self.__enable_prom = ''

        self.backend = self.getInputParamValue('backend')
        self.bitwidths = self.getInputParamValue('bitwidth')
        self.extheader = self.getInputParamValue('header')

        self.totalThreads = self.getInputParamValue('totalThreads')
        self.threadIndex = self.getInputParamValue('threadIndex')
        self.__after_run = self.totalThreads is not None

        if self.getInputParamValue('svcomp') is not None:
            self.__svcomp = True

        if self.getInputParamValue('roundint') is not None:
            self.__roundint = True

        if self.getInputParamValue('bit-pthread') is not None:
            self.__bit_pthread = True

        self.__intervals = env.intervals if hasattr(env, 'intervals') else {}

        if self.backend not in _backends:
            raise core.module.ModuleError("backend '%s' not supported" % self.backend)

        self.__avoid_type = [core.common.changeID[x] for x in core.common.changeID]
        self.__ignore_list = [
            '__cs_active_thread',
            '__cs_pc',
            '__cs_pc_cs',
            '__cs_last_thread',
            '__cs_thread_lines',
            '__cs_thread_index'
        ]

        super(self.__class__, self).loadfromstring(string, env)
        self.lastoutputlineno = 0
        self.removelinenumbers()
        # self.output = core.utils.strip(self.output)
        # self.inputtooutput = {}
        # self.outputtoinput = {}
        # self.generatelinenumbers()

        # Transformation 3:
        # shift indentation of raw lines fully left
        # removing the trailing marker _rawlinemarker+semicolon, and
        # shift any other line to the right depending to the longest rawline, and
        # in any case no longer than _maxrightindent.
        maxlinemarkerlen = max(len(l) for l in self.output.splitlines()) - len(_rawlinemarker + ';') - 2
        maxlinemarkerlen = min(maxlinemarkerlen, _maxrightindent)

        newstring = ''

        for l in self.output.splitlines():
            if l.endswith(_rawlinemarker+';'):
                newstring += l[:-len(_rawlinemarker+';')].lstrip() + '\n'
            else:
                newstring += ' '*(maxlinemarkerlen)+l+'\n'

        self.output = newstring

        self.insertheader(self.extheader)          # header passed by previous module

        # linearizability instrumentation
        liheaderfile = self.getInputParamValue("liheader")
        if liheaderfile is not None:
            header = core.utils.printFile(liheaderfile)
            header = header.replace("__CSEQ_assume", fmap[self.backend, "__CSEQ_assume"])
            header = header.replace("__CSEQ_assert", fmap[self.backend, "__CSEQ_assert"])
            self.insertheader(header)
            if not env.debug:
                core.utils.removeFile(liheaderfile)

        # Specific instrumentation for backend
        if self.backend == 'klee':
            self.insertheader(core.utils.printFile('modules/klee_extra.c'))
        elif self.backend == 'cpachecker':
            self.insertheader(core.utils.printFile('modules/cpa_extra.c'))
        elif self.backend == 'framac':
            self.insertheader(core.utils.printFile('modules/framac_extra.c'))
        elif self.backend == 'uautomizer':
            self.insertheader(core.utils.printFile('modules/uautomizer_extra.c'))
        elif self.backend == 'cbmc':
            self.insertheader(core.utils.printFile('modules/cbmc_extra.c'))
        elif self.backend == 'smack':
            self.insertheader(core.utils.printFile('modules/smack_extra.c'))

        # Insert external 'system' header if there are (from the file)
        if hasattr(self.env, "systemheaders"):
            self.insertheader(getattr(self.env, "systemheaders"))

        self.insertheader(core.utils.printFile('modules/pthread_defs.c'))

        self.insertheader(self._generateheader())  # top comment with translation parameters

    def _get_type_by_bits(self, numbit):
        if numbit <= 8: return 'char'
        if numbit <= 16: return 'short'
        if numbit <= 32: return 'int'
        return 'int'

    def _is_ps_helper(self, x):
        return 'lazyps' in x.split('_')

    ''' not use '''
    # def get_view_struct(self):
    #   return ''

    # generates suffix only for general n-dim arrays
    def get_array_suffix(self, var, func):
        decl_str = ''
        for p in self.Parser.varSize[(func, var)]:
            decl_str = decl_str + "[" + str(p) + "]"
        return decl_str

    # not required (inlining all calls)
    # def get_publish_message_stats(self, var_arr, var_num, thread_num):
    #     # static pre inlined translation
    #     s = ''
    #     # p = self.__time_bits
    #     s += '\n  __CPROVER_assume(%s < %s);\n' % (self._helper_names('index_used'), self._helper_names('rounds'))
    #     # temp_store = {}
    #     # for k in self.Parser.varNames['']:
    #     #     if k.startswith('__cs') or self._is_ps_helper(k):
    #     #         continue
    #     #     temp_store[k] = self.gen_all(self.Parser.varSize[('', k)])
    #         # for indices in  temp_store[k]:
    #             # var_arr = [k, indices, k+indices]
    #             # q = "__CPROVER_assume((%s_view_l)%s%s);\n" % (var_arr[0], var_arr[1], "[thread_num]") 
    #             # s+=q
    #     # for k in self.Parser.varNames['']:
    #     #     if k.startswith('__cs') or self._is_ps_helper(k):
    #     #         continue
    #     #     for indices in temp_store[k]:
    #     #         var_arr = [k, indices, k+indices]
    #     s += "  _ps_time[%s] = %s_view_t%s[%d];\n" % (self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
    #     s += "  _ps_flag[%s] = %d;\n" % (self._helper_names('index_used'), thread_num)
    #     s += "  _ps_var[%s] = %s;\n"%(self._helper_names('index_used'), var_num)
    #     s += "  _ps_val[%s] = %s_view%s[%d];\n" % (self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
    #     s += "  %s = %s + 1;\n" % (self._helper_names("index_used"), self._helper_names("index_used"))
    #     # s += "}\n"
    #     return s

    # not required (inlining all calls)
    # def get_update_view_stats(self, var_arr, var_num, thread_num, message_num):
    #     # pre - inlined function since variable-name of choice is not known statically (and variable name is embedded)
    #     s = ''
    #     p = self.__time_bits
    #     s += '\n  __CPROVER_assume((%s_view_l)%s[%s]);\n' % (var_arr[0], var_arr[1], thread_num)
    #     s += '  __CPROVER_assume((%s_view_t)%s[%s] <= _ps_time[%d]);\n' % (var_arr[0], var_arr[1], thread_num, message_num) 
    #     s += '  %s_view%s[%d] = _ps_val[%s];\n' % (var_arr[0], var_arr[1], thread_num, message_num)
    #     s += '  (%s_view_t)%s[%d] = _ps_time[%s];\n' % (var_arr[0], var_arr[1], thread_num, message_num) 
    #     # check whether numEE increment is needed
    #     return s

    def gen_indices(self, arities):
        s = []
        if len(arities)==0:
            return ''
        paddedarr = map(lambda x: '[' + str(x) + ']', arities)
        return ''.join(paddedarr)

    def get_message_struct(self):
        # done = []
        s = ''
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            # for indices in self.gen_all(self.Parser.varSize[('', k)]):
            var_arr = [k, self.gen_indices(self.Parser.varSize[('', k)])]#indices, k+indices]
            s += 'unsigned __CPROVER_bitvector[%d] %s_ps_time%s[%s];\n' % (self.__time_bits, var_arr[0], var_arr[1], self.__ps_rounds+1)
            s += 'unsigned __CPROVER_bitvector[1] %s_ps_timeL%s[%s];\n' % (var_arr[0], var_arr[1], self.__ps_rounds+1)
        s += 'unsigned __CPROVER_bitvector[%d] _ps_flag[%s];\n' % (self.__time_bits, self.__ps_rounds+1)
        s += 'unsigned __CPROVER_bitvector[%d] _ps_var[%s];\n' % (self.__time_bits, self.__ps_rounds+1)
  #       s += 'unsigned __CPROVER_bitvector[%d] _ps_reserve[%s];\n' % (self.__time_bits, self.__ps_rounds+1)
        # s += 'unsigned __CPROVER_bitvector[1] _ps_usedReservation[%s];\n' % (self.__ps_rounds+1)
        s += '\n'
        # for v, k in self.Parser.varTypeUnExpanded:
        #   type_temp = self.Parser.varTypeUnExpanded[(v, k)]
        #   if v == '' and type_temp not in done:
        #       s += '%s  _ps_val_%s[%s];\n' % (type_temp, type_temp, self.__ps_rounds)
        #       done.append(type_temp)
        #         self.__varTypes.append(type_temp)
        return s

    def gen_all(self, arities):
        s = []
        if len(arities)==0:
            return ['']
        rec = self.gen_all(arities[1:])
        for k in range(arities[0]):
            for h in rec:
                s.append('[' + str(k) + ']' + h)
        return s

    def get_readwrite_helper_stats(self):
        s = ''
        s += 'void publish_stats_ra_ps(unsigned int t1){\n'
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_arr = [k, indices, k+indices]
                s += "  %s_ps_time%s[%s] = %s_view_t%s[%s];\n" % (var_arr[0], var_arr[1], self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
                s += "  %s_ps_timeL%s[%s] = %s_view_l%s[%s];\n" % (var_arr[0], var_arr[1], self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
        s += '}\n'
        s += '\n'

        s += 'void acquire_message_ra_ps(unsigned int t1,  unsigned int messNum){\n'
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_arr = [k, indices, k+indices]
                s += "  if(%s_ps_time%s[messNum] == %s_view_t%s[t1]){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                # s += "      %s_ps_time%s[%s] = %s_view_t%s[t1];\n" % (var_arr[0], var_arr[1], self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
                s += "      %s_view_l%s[t1] = %s_ps_timeL%s[messNum] && %s_view_l%s[t1];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "  }\n"
                s += "  else if(%s_ps_time%s[messNum] > %s_view_t%s[t1]){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "      %s_view_l%s[t1] = %s_ps_timeL%s[messNum];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "      %s_view_t%s[t1] = %s_ps_time%s[messNum];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "  }\n"
        s += '}\n'
        s += '\n'

        s += 'void acquire_message_ra_copy_ps(unsigned int t1,  unsigned int messNum){\n'
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_arr = [k, indices, k+indices]
                s += "  if(%s_ps_time%s[messNum] == %s_view_t%s[t1]){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                # s += "      %s_ps_time%s[%s] = %s_view_t%s[t1];\n" % (var_arr[0], var_arr[1], self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
                s += "      %s_view_l%s[t1] = %s_ps_timeL%s[messNum] && %s_view_l%s[t1];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "  }\n"
                s += "  else if(%s_ps_time%s[messNum] > %s_view_t%s[t1]){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "      __CPROVER_assume(%s_liveChain%s[0] == 0);\n" % (var_arr[0], var_arr[1])
                s += "      %s_view_l%s[t1] = %s_ps_timeL%s[messNum];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "      %s_view_t%s[t1] = %s_ps_time%s[messNum];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "  }\n"
        s += '}\n'
        s += '\n'
        return s

    def get_merge_view_fun(self):
        s = ''
        s += "void merge_views_ps(unsigned int t1, unsigned int t2){\n"
        s += "  if(t1==0){\n"
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_arr = [k, indices, k+indices]
                s += "      (%s_view_l)%s[t2] = 1;\n" % (var_arr[0], var_arr[1])
                s += "      (%s_view_u)%s[t2] = 1;\n" % (var_arr[0], var_arr[1])
                s += "      (%s_view_v)%s[t2] = 1;\n" % (var_arr[0], var_arr[1])
                s += '      (%s_view)%s[t2] = (%s_view%s)[t1];\n' % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                # if self.__can_promise:    s += "      %s_extView%s[t2] = 1;\n" % (var_arr[0], var_arr[1])
        s += "  }\n"
        s += '  else{\n'
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_arr = [k, indices, k+indices]
                # s += "        __CPROVER_assume((%s_view_l)%s[t1]);\n" % (var_arr[0], var_arr[1])
                # s += "        __CPROVER_assume((%s_view_l)%s[t2]);\n" % (var_arr[0], var_arr[1])
                # new addition
                s += "      __CPROVER_assume((%s_view_u)%s[t1]);\n" % (var_arr[0], var_arr[1])
                s += "      if(%s_view_t%s[t2] <= %s_view_t%s[t1]){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "          %s_view_t%s[t2] = %s_view_t%s[t1];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "          %s_view%s[t2] = %s_view%s[t1];\n" % (var_arr[0], var_arr[1],var_arr[0], var_arr[1],)
                s += "      }\n"
        s += '  }\n'
        s += "}\n"
        return s
        
    def get_scfence_fun(self):
        s = ''
        s += 'void scfence_ps(unsigned int t1){\n'
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_arr = [k, indices, k+indices]
                # s += "        __CPROVER_assume((%s_view_l)%s[t1]);\n" % (var_arr[0], var_arr[1])
                s += "      if(%s_view_t%s[t1] < %s_fence_t%s){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += "          %s_view_t%s[t1] = %s_fence_t%s;\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                s += '          %s_view_v%s[t1] = 0;\n' % (var_arr[0], var_arr[1])
                s += '          %s_view_l%s[t1] = 1;\n' % (var_arr[0], var_arr[1])
                # s += "        %s_view%s[t2] = %s_view%s[t1];\n" % (var_arr[0], var_arr[1],var_arr[0], var_arr[1],)
                s += "      }\n"
                # s += "        else if(%s_view_t%s[t1] > %s_fence_t%s){\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                # s += "        else if(%s_view_l%s[t1] == 1){\n" % (var_arr[0], var_arr[1])
                # s += "        %s_fence_t%s = %s_view_t%s[t1];\n" % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])
                # # s += "          %s_view%s[t2] = %s_view%s[t1];\n" % (var_arr[0], var_arr[1],var_arr[0], var_arr[1],)
                # s += "        }\n"
                s += "      else{"
                s += "          %s_fence_t%s = %s_view_t%s[t1];\n"  % (var_arr[0], var_arr[1], var_arr[0], var_arr[1])      
                s += "      }"
        s += '}\n'
        return s
        

    def get_savestate_stats(self):
        s = ''
        # bits = self.__time_bits
        # will need convert to thread specific definition
        s += "void save_state_ps(unsigned int t1){\n"
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            # decl_str = '' 
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                # decl_str = decl_str + '[' + str(p) + ']'
                var_name = k + indices
                for itvar in range(2*self.__ps_rounds+1):
                    s += '%s_%s[%s] = %s_%s[%s];\n' % (self._helper_names("save_unavail"), var_name, str(itvar), self._helper_names("unavail"), var_name, str(itvar))
                    s += '%s_%s[%s] = %s_%s[%s];\n' % (self._helper_names("save_upd"), var_name, str(itvar), self._helper_names("upd"), var_name, str(itvar))
                s += k + "_save_view" + indices + " = " + k + "_view" + indices + "[t1];\n"
                s += k + "_save_view_t" + indices + " = " + k + "_view_t" + indices + "[t1];\n"
                # s += k + "_save_view_tL" + indices + " = " + k + "_view_tL" + indices + "[t1];\n"
                s += k + "_save_fence_t" + indices + " = " + k + "_fence_t" + indices + ";\n"
                s += k + "_save_view_l" + indices + " = " + k + "_view_l" + indices + "[t1];\n"
                s += k + "_save_view_u" + indices + " = " + k + "_view_u" + indices + "[t1];\n"
                s += k + "_save_view_v" + indices + " = " + k + "_view_v" + indices + "[t1];\n"
                s += k + "_save_liveChain" + indices + " = " + k + "_liveChain" + indices + "[0];\n"
                s += k + "_save_extView" + indices + " = " + k + "_extView" + indices + "[0];\n"
        # for k  in self.Parser.varNames[self.__currentFunction]:
        #   tup = (self.currentFunction, k)
        #   if k.startswith ('__cs') or self._is_ps_helper(k):
        #       continue
        #   for indices in self.gen_all(self.Parser.varSize[('', k)]):
        #       # decl_str = decl_str + '[' + str(p) + ']'
        #       var_name = k + indices
        #       # TODO:
        #       # complete loading global copies of local variables
        s += "}\n"
        return s

    def get_func_decls(self):
        s = ''
        done = []
        for th in self.Parser.threadName:
            thname = '_'.join(th.split('_')[:-1])
            if thname not in done:
                s += 'void %s_pscopy(int);\n' % (thname)
                done.append(thname)
        return s
    
    def get_loadstate_stats(self):
        s = ''
        # bits = self.__time_bits
        s += "void load_state_ps(unsigned int t1){\n"
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            for indices in self.gen_all(self.Parser.varSize[('', k)]):
                var_name = k + indices
                for itvar in range(2*self.__ps_rounds+1):
                    s += '%s_%s[%s] = %s_%s[%s];\n' % (self._helper_names("unavail"), var_name, str(itvar), self._helper_names("save_unavail"), var_name, str(itvar))
                    s += '%s_%s[%s] = %s_%s[%s];\n' % (self._helper_names("upd"), var_name, str(itvar), self._helper_names("save_upd"), var_name, str(itvar))
                s += k + "_view" + indices + "[t1] = " + k + "_save_view" + indices + ";\n"
                s += k + "_view_t" + indices + "[t1] = " + k + "_save_view_t" + indices + ";\n"
                # s += k + "_view_tL" + indices + "[t1] = " + k + "_save_view_tL" + indices + ";\n"
                s += k + "_fence_t" + indices + " = " + k + "_save_fence_t" + indices + ";\n"
                s += k + "_view_l" + indices + "[t1] = " + k + "_save_view_l" + indices + ";\n"
                s += k + "_view_u" + indices + "[t1] = " + k + "_save_view_u" + indices + ";\n"
                s += k + "_view_v" + indices + "[t1] = " + k + "_save_view_v" + indices + ";\n"
                s += k + "_liveChain" + indices + "[0] = " + k + "_save_liveChain" + indices + ";\n"
                s += k + "_extView" + indices + "[0] = " + k + "_save_extView" + indices + ";\n"
                s += k + "_blockPromise"+ indices + "[0] = 0;\n"
        s += "}\n"
        return s

    def get_time_bits(self):
        return self.__time_bits

    def get_state_vars(self):
        s = ''
        bits = self.__time_bits
        # s += 'unsigned __CPROVER_bitvector[%d] %s = 0;\n' %(bits, self._helper_names('save_numEE'))
        # index used is not required since all messages published to the memory pool are neccesarily promises
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            decl_str = ''
            for p in self.Parser.varSize[tup]:
                decl_str = decl_str + '[' + str(p) + ']'
            s += "unsigned __CPROVER_bitvector[1] %s_%s[%s];\n" % (self._helper_names("save_unavail"), k + self.get_array_suffix(k, ''), str(2*self.__ps_rounds+1))
            s += "unsigned __CPROVER_bitvector[1] %s_%s[%s];\n"%(self._helper_names("save_upd"), k + self.get_array_suffix(k, ''), str(2*self.__ps_rounds+1))
            s += self.Parser.varTypeUnExpanded[tup] + " " + k + "_save_view" + decl_str + ";\n"
            # s += self.Parser.varTypeUnExpanded[tup] + " " + k + "_save_values" + decl_str + "[%s];\n" % str((2*self.__ps_rounds+1)) 
            s += "unsigned __CPROVER_bitvector[%d] " % bits+ k + "_save_view_t" + decl_str + ";\n"
            # s += "unsigned __CPROVER_bitvector[%d] " % bits+ k + "_save_view_tL" + decl_str + ";\n"
            s += "unsigned __CPROVER_bitvector[%d] " % bits+ k + "_save_fence_t" + decl_str + ";\n"
            s += "unsigned __CPROVER_bitvector[1] " + k + "_save_view_l" + decl_str + ";\n"
            s += "unsigned __CPROVER_bitvector[1] " + k + "_save_view_u" + decl_str + ";\n"
            s += "unsigned __CPROVER_bitvector[1] " + k + "_save_view_v" + decl_str + ";\n"
            s += "unsigned __CPROVER_bitvector[1] " + k + "_save_liveChain" + decl_str + ";\n"
            s += "unsigned __CPROVER_bitvector[1] " + k + "_save_extView" + decl_str + ";\n"
        return s

    def get_global_vars(self):
        s = ''
        bits = self.__time_bits
        s += 'unsigned __CPROVER_bitvector[%d] %s = 0;\n' % (bits, self._helper_names('numEE'))
        s += 'const unsigned __CPROVER_bitvector[%d] %s = %s;\n' % (bits, self._helper_names('rounds'), str(self.__ps_rounds))
        s += 'unsigned __CPROVER_bitvector[%d] %s = 0;\n' % (bits, self._helper_names('index_used'))
        for k in self.Parser.varNames['']:
            tup = ('', k)
            if k.startswith('__cs') or self._is_ps_helper(k):
                continue
            decl_str = ''
            for p in self.Parser.varSize[tup]:
                decl_str = decl_str + "[" + str(p) + "]"
            s += "unsigned __CPROVER_bitvector[1] %s_%s[%s];\n" % (self._helper_names("unavail"), k + self.get_array_suffix(k, ''), str(self.__ps_rounds+1))
            s += "unsigned __CPROVER_bitvector[1] %s_%s[%s];\n" % (self._helper_names("upd"), k + self.get_array_suffix(k, ''), str(self.__ps_rounds+1))
            s += "unsigned __CPROVER_bitvector[1] %s_%s[%s];\n" % (self._helper_names("usedReservation"), k + self.get_array_suffix(k, ''), str(self.__ps_rounds+1))
            s += "unsigned __CPROVER_bitvector[%s] %s_ps_reserve%s[%s];\n" % (self.__time_bits, k, decl_str, str(self.__ps_rounds+1))
            s += self.Parser.varTypeUnExpanded[tup] + " " + k + "_view" + decl_str + "[%s];\n" % (str(self.totalThreads+1))
            s += self.Parser.varTypeUnExpanded[tup] + " " + k + "_values" + decl_str + "[%s];\n" % (str(self.__ps_rounds+1)) 
            s += "unsigned __CPROVER_bitvector[%d] " % bits + k + "_view_t" + decl_str + "[%s];\n" % str((self.totalThreads+1))
            # s += "unsigned __CPROVER_bitvector[%d] " % bits + k + "_view_tL" + decl_str + "[%s];\n" % str((self.totalThreads+1))
            s += 'unsigned __CPROVER_bitvector[%d] ' % bits + k + '_fence_t' + decl_str + ';\n'
            s += 'unsigned __CPROVER_bitvector[1] ' + k + '_view_v' + decl_str + '[%s];\n' % (str(self.totalThreads+1))
            s += "unsigned __CPROVER_bitvector[1] " + k + "_view_l" + decl_str + "[%s];\n" % (str(self.totalThreads+1))
            s += "unsigned __CPROVER_bitvector[1] " + k + "_view_u" + decl_str + "[%s];\n" % (str(self.totalThreads+1))
            if self.__can_promise:
                # all these are now single copies (not one per process)
                s += "unsigned __CPROVER_bitvector[1] " + k + "_liveChain" + decl_str + "[1];\n"  #% (str(self.totalThreads+1))
                s += "unsigned __CPROVER_bitvector[1] " + k + "_extView" + decl_str + "[1];\n" #% (str(self.totalThreads+1))
                s += "unsigned __CPROVER_bitvector[1] " + k + "_blockPromise" + decl_str + "[1];\n" #% (str(self.totalThreads+1))
        # s += "unsigned __CPROVER_bitvector[1] %s[%s];\n" % (self._helper_names("checkMode"), str(self.totalThreads+1))
        if self.__can_promise: 
            s += "unsigned __CPROVER_bitvector[1] %s[%s];\n" % (self._helper_names("active"), str(self.totalThreads+1))
            s += 'unsigned __CPROVER_bitvector[%s] %s[%s];\n' % (self.__time_bits, self._helper_names('retAddr'), str(self.totalThreads+1))
            #[0 for non-necessary, 1 for necessary, 2 for unnecessary]
            # essential for pthread_create() and pthread_join()
        # if self.__can_promise:
            s += self.get_loadstate_stats() + self.get_savestate_stats()
        s += self.get_merge_view_fun()
        s += self.get_scfence_fun()
        return s
    
    def visit_FuncDef(self, n):
        self.__currentFunction = n.decl.name
        decl = self.visit(n.decl)
        self.indent_level = 0
        body = self.visit(n.body)
        if self.__can_edit_global_scope and self.__after_run:
            self.__can_edit_global_scope = False
            if self.__can_promise:
                decl = self.get_func_decls() + self.get_state_vars() + self.get_message_struct() + self.get_global_vars() + decl
            else:
                decl = self.get_message_struct() + self.get_global_vars() + decl       # non-functional translation (in lazyseqnewschedule) self.get_publish_message_fun() + self.get_update_view_fun()
        if n.param_decls:
            knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
            return decl + '\n' + knrdecls + ';\n' + body + '\n'
        else:
            return decl + '\n' + body + '\n'
       
    def visit_ID(self, n):
        s = n.name
        if "ps_thread_num" in s and self.__after_run:
            ind = 0
            if self.__currentFunction in self.threadIndex:
                ind = self.threadIndex[self.__currentFunction]
            return str(ind)
        return s

    def visit_Decl(self,n,no_type=False):
        # no_type is used when a Decl is part of a DeclList, where the type is
        # explicitly only for the first delaration in a list.
        #
        s = n.name if no_type else self._generate_decl(n)

        # In case  x  has a custom bitwidth (passed by a previous module), convert
        # 'int x'  to  'bitvectors[k] x' or
        # 'unsigned int x'  to  'unsigned bitvectors[k] x'.
        ninitextra = ''
        prefix = ''

        if self.backend == 'cbmc':
            if s.startswith('static '):
                s = s[7:]    # remove static
                prefix = 'static '
            if s.startswith("_Bool "): pass
            elif self.bitwidths is not None:
                if self.__visiting_struct:
                    if (self.__struct_stack[-1], n.name) in self.bitwidths:
                        if s.startswith("unsigned int "):
                            if (self.__roundint
                                    # not (n.name in self.__ignore_list or
                                    #     n.name.startswith('__cs_tmp_t') or
                                    #     n.name.startswith('__cs_run_t'))
                                ):
                                s = s.replace("unsigned int ","unsigned %s " % (self._get_type_by_bits(self.bitwidths[self.__struct_stack[-1],n.name])),1)
                            else:
                                s = s.replace("unsigned int ","unsigned __CPROVER_bitvector[%s] " % self.bitwidths[self.__struct_stack[-1],n.name],1)
                        elif s.startswith("int "):
                            if (self.__roundint
                                    # not (n.name in self.__ignore_list or
                                    #     n.name.startswith('__cs_tmp_t') or
                                    #     n.name.startswith('__cs_run_t'))
                                ):
                                s = s.replace("int ","%s " % (self._get_type_by_bits(self.bitwidths[self.__struct_stack[-1],n.name])),1)
                            else:
                                s = s.replace("int ","__CPROVER_bitvector[%s] " % self.bitwidths[self.__struct_stack[-1],n.name],1)
                        else:
                            temp = s.split()   # split the declaration
                            for i, item in enumerate(temp):
                                if item.lstrip('*') == n.name and i > 0 and temp[i-1] not in self.__avoid_type and temp[i-1] in ('long', 'short', 'char',):   # temp[i-1] is the type
                                    if (self.__roundint
                                            # not (n.name in self.__ignore_list or
                                            #     n.name.startswith('__cs_tmp_t') or
                                            #     n.name.startswith('__cs_run_t'))
                                        ):
                                        temp[i-1] = '%s' % self._get_type_by_bits(self.bitwidths[self.__struct_stack[-1],n.name])
                                    else:
                                        temp[i-1] = '__CPROVER_bitvector[%s]' % self.bitwidths[self.__struct_stack[-1],n.name]
                                    break
                            s = " ".join(temp)
                else:
                    currentFunct = self.currentFunct if self.currentFunct != 'main_thread' else 'main'
                    if s.startswith("unsigned int ") and (currentFunct,n.name) in self.bitwidths:
                        if (self.__roundint
                                # not (n.name in self.__ignore_list or
                                #     n.name.startswith('__cs_tmp_t') or
                                #     n.name.startswith('__cs_run_t'))
                            ):
                            s = s.replace("unsigned int ","unsigned %s " % self._get_type_by_bits(self.bitwidths[currentFunct,n.name]),1)
                            ninitextra = '(unsigned %s)' % self._get_type_by_bits(self.bitwidths[currentFunct,n.name])
                        else:
                            s = s.replace("unsigned int ","unsigned __CPROVER_bitvector[%s] " % self.bitwidths[currentFunct,n.name],1)
                            ninitextra = '(unsigned __CPROVER_bitvector[%s])' % self.bitwidths[currentFunct,n.name]
                    elif s.startswith("int ") and (currentFunct, n.name) in self.bitwidths:
                        numbit = self.bitwidths[currentFunct, n.name]
                        if (self.__roundint
                                # not (n.name in self.__ignore_list or
                                #     n.name.startswith('__cs_tmp_t') or
                                #     n.name.startswith('__cs_run_t'))
                            ):
                            s = s.replace("int ","%s " % self._get_type_by_bits(numbit),1)
                            ninitextra = '(%s)' % self._get_type_by_bits(numbit)
                        else:
                            s = s.replace("int ","__CPROVER_bitvector[%s] " % numbit,1)
                            ninitextra = '(__CPROVER_bitvector[%s])' % numbit
                    elif (currentFunct, n.name) in self.bitwidths:
                        numbit = self.bitwidths[currentFunct, n.name]
                        temp = s.split()
                        for i, item in enumerate(temp):
                            if item.lstrip('*') == n.name and i > 0 and temp[i-1] not in self.__avoid_type and temp[i-1] in ('long', 'short', 'char',):
                                if (self.__roundint
                                        # not (n.name in self.__ignore_list or
                                        #     n.name.startswith('__cs_tmp_t') or
                                        #     n.name.startswith('__cs_run_t'))
                                    ):
                                    temp[i-1] = '%s' % self._get_type_by_bits(numbit)
                                else:
                                    temp[i-1] = '__CPROVER_bitvector[%s]' % numbit
                                break
                        s = " ".join(temp)
            if prefix != '':
                s = prefix + s

        if n.bitsize: s += ' : ' + self.visit(n.bitsize)
        if n.init:
            if isinstance(n.init,pycparser.c_ast.InitList):
                s += ' = {' + self.visit(n.init) + '}'
            elif isinstance(n.init,pycparser.c_ast.ExprList):
                s += ' = (' + self.visit(n.init) + ')'
            else:
                s += ' = ' + ninitextra + '(' + self.visit(n.init) + ')'
        return s

    def _generate_struct_union(self, n, name):
        """ Generates code for structs and unions. name should be either
            'struct' or union.
        """
        s = name + ' ' + (n.name or '')
        # There should be no anonymous struct, handling in workarounds module
        self.__visiting_struct = True
        if n.name:
            self.__struct_stack.append(n.name)
        if n.decls:
            s += '\n'
            s += self._make_indent()
            self.indent_level += 2
            s += '{\n'
            for decl in n.decls:
                s += self._generate_stmt(decl)
            self.indent_level -= 2
            s += self._make_indent() + '}'
        self.__visiting_struct = False
        self.__struct_stack.pop()
        return s

    def visit_Typedef(self, n):
        s = ''
        if n.storage: s += ' '.join(n.storage) + ' '
        s += self._generate_type(n.type)
        if (self.backend == 'cbmc' and self.__bit_pthread and
                ('int __cs_t' in s or
                'int __cs_mutex_t' in s or
                'int __cs_cond_t' in s )
            ):
            import math
            k = int(math.floor(math.log(len(self.Parser.threadName) + 1, 2)))+1

            if '__cs_t' in s: k += 1
            if '__cs_mutex_t' in s: k += 1
            if '__cs_cond_t' in s: k = 3

            if self.__roundint:
                s = s.replace('int ', '%s ' % self._get_type_by_bits(k), 1)
            else:
                s = s.replace('int ', '__CPROVER_bitvector[%s] ' % k, 1)
        return s

    ''' converts function calls '''
    def visit_FuncCall(self,n):
        fref = self._parenthesize_unless_simple(n.name)

        # Transformation 3.
        if fref == '__CSEQ_rawline':
            return self.visit(n.args)[1:-1]+_rawlinemarker

        sync_dict = {
            '__cs_mutex_destroy' : True,
            '__cs_mutex_lock' : True,
            '__cs_mutex_unlock' : True,
            '__cs_cond_wait_1' : True,
            '__cs_cond_wait_2' : True,
            '__cs_barrier_init' : True,
            '__cs_barrier_wait_1' : True,
            '__cs_barrier_wait_2' : True
        }
        if (fref == '__CSEQ_assertext' and
                self.__svcomp and
                self.backend != 'framac' and
                self.currentFunct in sync_dict):
            return fmap[self.backend, '__CSEQ_assume'] + '(' + self.visit(n.args.exprs[0]) + ')'

        args = self.visit(n.args)

        if (fref == '__CSEQ_assertext' and
                self.backend not in ('cbmc', 'esbmc')):
            args = self.visit(n.args.exprs[0])   # Only get the first expression

        if (self.backend, fref) in fmap:
            fref = fmap[self.backend, fref]

        if (fref == '__VERIFIER_error' and
                self.backend == 'framac'
            ):
            return '__FRAMAC_assert(0)'

        return fref + '(' + args + ')'

    def _generateheader(self):
        masterhash_framework = '0000'
        masterhash_modulechain = '0000'

        #swarm
        instanceVersion = ''
        import json
        instanceVersion = json.dumps(self.__intervals)

        h = '/*\n'
        h += ' *  generated by CSeq [ %s / %s ]\n' % (masterhash_framework,masterhash_modulechain)
        h += ' * \n'
        h += ' *  instance version    %s\n' % instanceVersion
        # h += ' *                      %s %s\n' % (core.utils.shortfilehash('core/merger.py'),core.merger.VERSION)
        # h += ' *                      %s %s\n' % (core.utils.shortfilehash('core/parser.py'),core.parser.VERSION)
        # h += ' *                      %s %s ]\n' % (core.utils.shortfilehash('core/module.py'),core.module.VERSION)
        h += ' *\n'
        h += ' *  %s\n' %strftime("%Y-%m-%d %H:%M:%S",gmtime())
        h += ' *\n'
        h += ' *  params:\n'

        h += ' *    '
        for o,a in self.env.opts:
             h+='%s %s, ' % (o,a)
        h+= '\n'
        h += ' *\n'

        # h += ' *  modules:\n'
        # h += ' *'

        # for transforms,m in enumerate(self.env.modules):
        #     paramin = ' '.join(p.id for p in m.inputparamdefs)
        #     params = '(%s)'  % paramin
        #     h += '  %s %s-%s %s' %(core.utils.shortfilehash('modules/%s.py' % m.getname()),m.getname(),'0.0',params) # m.VERSION
        # h += '\n'
        # h += ' *\n'

        h += ' */\n'
        return h
