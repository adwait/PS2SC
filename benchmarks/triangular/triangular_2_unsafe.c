/* Adapted from: https://github.com/sosy-lab/sv-benchmarks/blob/master/c/pthread/triangular-1.c */

// Adapted for the tool PSChecker

#include <pthread.h>

int i;
int j;

#define NUM 2
#define LIMIT (2*NUM+6)

void *worker1(void* arg)
{
	int _i;
	int _j;
	int k;
	
	rlx_read_ps(j, _j);
	_j = _j + 1;
	rlx_write_ps(i, _j);
	rlx_read_ps(j, _j);
	_j = _j + 1;
	rlx_write_ps(i, _j);
}

void *worker2(void* arg)
{
	int _i;
	int _j;
	int k;
	
	rlx_read_ps(i, _i);
	_i = _i + 1;
	rlx_write_ps(j, _i);
	rlx_read_ps(i, _i);
	_i = _i + 1;
	rlx_write_ps(j, _i);
}

void *checker(void *arg)
{
	int _i,  _j;
	rlx_read_ps(i, _i);
	rlx_read_ps(j, _j);

	if (_i >= LIMIT || _j >= LIMIT) {
		assert(0);
	}
}


int main()
{
	pthread_t t1, t2, t3;

	i = 3;
	j = 6;

	pthread_create(&t1, 0, worker1, 0);
	pthread_create(&t2, 0, worker2, 0);
	pthread_create(&t3, 0, checker, 0);

	return 0;
}
