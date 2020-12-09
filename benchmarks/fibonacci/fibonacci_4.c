/* Adapted from: https://svn.sosy-lab.org/software/sv-benchmarks/trunk/c/pthread/fib_bench_false-unreach-call.c */

// Adapted for the tool PSChecker

#include <pthread.h>

int x;
int y;


void *worker1(void* arg)
{
	int _x;
	int _y;
	int i;
	int _s;

	// for (i = 0; i < ITER; i++) {
		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(x, _s);

		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(x, _s);
		
		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(x, _s);

		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(x, _s);
	// }
}

void *worker2(void* arg)
{
	int _x;
	int _y;
	int i;
	int _s;

	// for (i = 0; i < ITER; i++) {
		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(y, _s);

		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(y, _s);

		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(y, _s);

		rlx_read_ps(x, _x);
		rlx_read_ps(y, _y);
		_s = _x + _y;
		rlx_write_ps(y, _s);		
	// }
}

void *checker(void *arg)
{
	int true_val, _x,  _y;
	// true_val = fib(2 + 2*ITER);
	rlx_read_ps(x, _x);
	rlx_read_ps(y, _y);

	if (_x > 55 || _y > 55) {
		assert(0);
	}
}


int main()
{
	pthread_t t1, t2, t3;

	x = 1;
	y = 1;

	pthread_create(&t1, 0, worker1, 0);
	pthread_create(&t2, 0, worker2, 0);
	pthread_create(&t3, 0, checker, 0);

	return 0;
}
