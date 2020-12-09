/* Adapted from: https://github.com/sosy-lab/sv-benchmarks/blob/master/c/pthread/triangular-1.c */

// Adapted for the tool PSChecker

#include <pthread.h>

int i;
int j;

#define NUM 6
#define LIMIT (2*NUM+6)

void *worker1(void* arg)
{
	int _i;
	int _j;
	int k;
	
	_j = j;
	i = _j + 1;
	_j = j;
	i = _j + 1;
	_j = j;
	i = _j + 1;
	_j = j;
	i = _j + 1;
	_j = j;
	i = _j + 1;
	_j = j;
	i = _j + 1;

}

void *worker2(void* arg)
{
	int _i;
	int _j;
	int k;
	
	_i = i;
	j = _i + 1;
	_i = i;
	j = _i + 1;
	_i = i;
	j = _i + 1;
	_i = i;
	j = _i + 1;
	_i = i;
	j = _i + 1;
	_i = i;
	j = _i + 1;
}

void *checker(void *arg)
{
	int _i,  _j;
	_i = i;
	_j = j;

	if (_i > LIMIT || _j > LIMIT) {
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
