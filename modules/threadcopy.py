""" CSeq Constant Propagation module
	written by Omar Inverso, University of Southampton
	maintained by Truc Nguyen Lam, University of Southampton
"""
VERSION = 'threadcopy-0.0-2014.12.24'  # SwInGv0.1

"""
Changelog:
	2020.6.3  initialize with copier functions

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


class threadcopy(core.module.Translator):
	
	__currentFunction = ''
	__can_promise = True
	__copyonce = True
	__no_exit = False

	def init(self):
		self.addInputParam('prom', 'Promises', 'string',  '1', True)
		# self.addInputParam('ee', 'Essential Events', '', '1', False)

	def loadfromstring(self, string, env):
		# self.__ps_rounds = int(env.paramvalues['ee'])
		if 'prom' in env.paramvalues:
			self.__can_promise = (env.paramvalues['prom'] != '0')
		super(self.__class__, self).loadfromstring(string, env)

	def visit_FuncDef(self, n):
		self.__currentFunction = n.decl.name
		# copydecl = pycparser.c_ast.Decl('_pscopy_' + n.decl.name, n.decl.quals, n.decl.storage, n.decl.funcspec, n.decl.type, n.decl.init, n.decl.bitsize)
		# copyn = pycparser.c_ast.FuncDef(copydecl, n.param_decls, n.body)
		decl = self.visit(n.decl)

		
		# copyl = decl.split('(')
		# copyl[0] = copyl[0].replace('*', '') + '_pscopy'
		# copydecl = '('.join(copyl)
		# if self.__currentFunction in self.Parser.threadName:
		# 	self.__isAtomicOpen = True
		copydecl = 'void %s_pscopy(int _ps_t1)' % (self.__currentFunction)

		body = self.visit(n.body)
		self.__no_exit = True
		copybody = self.visit(n.body)
		self.__no_exit = False

		if self.__currentFunction != 'main' and self.__can_promise:
			if n.param_decls:
				knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
				return decl + '\n' + knrdecls + ';\n' + body + '\n' + copydecl + '\n' + knrdecls + ';\n' + copybody + '\n'
			else:
				return decl + '\n' + body + '\n' + copydecl + '\n' + copybody + '\n'
		else:
			if n.param_decls:
				knrdecls = ';\n'.join(self.visit(p) for p in n.param_decls)
				return decl + '\n' + knrdecls + ';\n' + body + '\n'
			else:
				return decl + '\n' + body + '\n'

	def visit_FuncCall(self, n):
		if self.__no_exit:
			if 'exit' in self._visit_expr(n.name):
				return 'return;\n'
		return self._parenthesize_unless_simple(n.name) + '(' + self.visit(n.args) + ')'


