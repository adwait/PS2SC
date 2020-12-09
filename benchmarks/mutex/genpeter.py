#!/usr/bin/python3

import sys

def genthreadpeter(nthreads, threadnum, fencefree):

	lnum = 'level' + str(threadnum)

	op = ''

	if not fencefree:
		sccmmds = 'sc_fence();\n'
	else:
		sccmmds = ''

	op += 'void* t%s(){\n' % (str(threadnum))
	op += '\n'

	for i in range(nthreads):
		if i != threadnum:
			op += 'int __level%s;\n' % (str(i))
	for i in range(nthreads-1):
		op += 'int __waiting%s;\n' % (str(i))
	op += 'int ___cc_x;\n'

	op += 'while(1){\n'

	for i in range(nthreads-1):
		op += 'rlx_write_ps(%s,%s);\n' % (lnum, str(i))
		op += sccmmds
		op += 'rlx_write_ps(%s,%s);\n' % ('waiting' + str(i), str(threadnum))
		op += sccmmds
		
		op += '\n'
		op += 'rlx_read_ps(%s, %s);\n' % ('waiting' + str(i), '__waiting' + str(i))
		for j in range(nthreads):
			if j != threadnum:
				op += 'rlx_read_ps(%s, %s);\n' % ('level' + str(j), '__level' + str(j))
				
		op += '\n'
		op += 'assume(%s' % ('__waiting' + str(i) + '!= 0 || (')
		for j in range(nthreads):
			if j != threadnum:
				op += '__level' + str(j) + ' < %s && ' % (str(i))
		op += '1));\n'
		op += '\n'

	op += 'rlx_write_ps(_cc_x, %s);\n' % (str(threadnum))
	op += 'rlx_read_ps(_cc_x, ___cc_x);\n'
	op += 'assert(___cc_x == %s);\n' % (str(threadnum))

	op += sccmmds
	op += 'rlx_write_ps(level%s, 0);\n' % (str(threadnum))

	op += '}\n'
	op += '}\n'

	return op


def genthreadszy(numthreads, threadnum, fencefree):
	localflag = 'flag' + str(threadnum)

	if not fencefree:
		sccmmds = 'sc_fence();\n'
	else:
		sccmmds = ''

	def getflagcheck(checks, junction, flags):
		checklist = ['__flag' + str(i) + j for i in flags for j in checks]
		return (' ' + junction + ' ').join(checklist)

	op = ''
	op += 'void* t%s(){\n' % (str(threadnum))
	op += '\n'

	for i in range(numthreads):
		if i != threadnum:
			op += 'int __flag%s;\n' % (str(i))
	# for i in range(nthreads-1):
	# 	op += 'int __waiting%s;\n' % (str(i))
	op += 'int ___cc_x;\n'

	op += 'while(1){\n'

	op += 'rlx_write_ps(%s, 1);\n' % (localflag)
	op += sccmmds

	# assume block 
	op += '\n'
	for j in range(numthreads):
		if j != threadnum:
			op += 'rlx_read_ps(%s, %s);\n' % ('flag' + str(j), '__flag' + str(j))
	
	op += 'assume(%s);\n' % (getflagcheck(['< 3'], '&&', [i for i in range(numthreads) if i != threadnum]))
	
	op += 'rlx_write_ps(%s, 3);\n' % (localflag)
	op += sccmmds

	op += '\n'
	for j in range(numthreads):
		if j != threadnum:
			op += 'rlx_read_ps(%s, %s);\n' % ('flag' + str(j), '__flag' + str(j))
	op += 'if(%s){\n' % (getflagcheck(['==1'], '||', [i for i in range(numthreads) if i != threadnum]))
	op += '	rlx_write_ps(%s,2);\n' % (localflag)
	op += '	sc_fence();\n'

	op += '\n'
	for j in range(numthreads):
		if j != threadnum:
			op += 'rlx_read_ps(%s, %s);\n' % ('flag' + str(j), '__flag' + str(j))
	op += '	assume(%s);\n' % (getflagcheck(['==4'], '||', [i for i in range(numthreads) if i != threadnum]))
	op += '}\n'

	op += 'rlx_write_ps(%s, 4);\n' % (localflag)
	op += sccmmds

	op += '\n'
	for j in range(numthreads):
		if j < threadnum:
			op += 'rlx_read_ps(%s, %s);\n' % ('flag' + str(j), '__flag' + str(j))
	if threadnum > 0:
		op += 'assume(%s);\n' % (getflagcheck([' < 2'], '&&', [i for i in range(threadnum)]))

	op += 'rlx_write_ps(_cc_x, %s);\n' % (str(threadnum))
	op += 'rlx_read_ps(_cc_x, ___cc_x);\n'
	op += 'assert(___cc_x == %s);\n' % (str(threadnum))

	op += '\n'
	for j in range(numthreads):
		if j > threadnum:
			op += 'rlx_read_ps(%s, %s);\n' % ('flag' + str(j), '__flag' + str(j))
	if threadnum != numthreads-1:
		op += 'assume(%s);\n' % (getflagcheck([' != 2', '!= 3'], '&&', [i for i in range(threadnum+1, numthreads)]))

	# op += 'sc_fence();\n'
	op += 'rlx_write_ps(%s, 0);\n' % (localflag)

	op += '}\n'
	op += '}\n'

	return op




def geninstance(numthreads, mutex, fencefree):

	op = '''
/* Inspiration from the SVCOMP-2018 benchmarks
*/

// Adapted for the tool PSChecker 

#include <pthread.h>
'''
	if mutex == 'p':
		levelmarker = 'level'
	elif mutex == 's':
		levelmarker = 'flag'
	else:
		print('invalid mutex type')
		exit(0)

	op += '\n'
	
	op += 'int %s0' % (levelmarker)
	for i in range(1, numthreads):
		op += ', %s%s' % (levelmarker, str(i))
	op += ';\n'

	if mutex == 'p':
		op += 'int waiting0'
		for i in range(1, numthreads-1):
			op += ', waiting%s' % (str(i))
		op += ';\n'

	op += 'int _cc_x;\n'
	op += '\n'
		
	if mutex == 'p':
		for i in range(numthreads):
			if i == 2:
				op += genthreadpeter(numthreads,i,fencefree)
			else:
				op += genthreadpeter(numthreads,i,False)
			op += '\n\n'
	elif mutex == 's':
		for i in range(numthreads):
			if i == 2:
				op += genthreadszy(numthreads,i,fencefree)
			else:
				op += genthreadszy(numthreads,i,False)
			op += '\n\n'
	else:
		print('Illegal mutex variant - in geninstance()')
		exit(0)		

	op += 'int main(){\n'
	op += '	pthread_t _cs_tdiff0'
	for i in range(1,numthreads):
		op += ', _cs_tdiff%s' % (str(i))
	op += ';\n'

	for i in range(numthreads):
		op += '	pthread_create(&_cs_tdiff%s, 0, t%s, 0);\n' % (str(i), str(i))

	op += '	return 0;\n'

	op += '}\n'

	return op


def main():

	numthreads = int(sys.argv[1])
	mutex = sys.argv[2]
	fencefree = bool(sys.argv[3])
	# buggy = bool(sys.argv[4])

	print(geninstance(numthreads, mutex, fencefree))

if __name__ == '__main__':
	main()