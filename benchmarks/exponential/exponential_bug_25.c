/* Inspired from example in Figure 2 in the PLDI 2015 paper: 
   https://dl.acm.org/citation.cfm?id=2737975
*/

// Adapted for the tool PSChecker

#include <pthread.h>

#define N 25

// shared variables
int x, y;
int __cs_mlock;

void *thr1(void *arg)
{
	int i;

  	__cs_mutex_lock(&__cs_mlock);
	rlx_write_ps(x, 1);
	for (i=0; i<N; i++) {
		rlx_write_ps(y, 1);
	}
  	__cs_mutex_unlock(&__cs_mlock);

  	__cs_mutex_lock(&__cs_mlock);
	rlx_write_ps(x, 1);
	for (i=0; i<N; i++) {
		rlx_write_ps(y, 1);
	}
  	__cs_mutex_unlock(&__cs_mlock);

}

void *thr2(void *arg)
{
	int _x, _y;

  	__cs_mutex_lock(&__cs_mlock);
	rlx_write_ps(x, 0);
  	__cs_mutex_unlock(&__cs_mlock);
	
	rlx_read_ps(x, _x);
	if (_x > 0) {
		rlx_read_ps(y, _y);
		_y = _y + 1;
		rlx_write_ps(y, _y);
		rlx_write_ps(x, 2);
	}

  	__cs_mutex_lock(&__cs_mlock);
	rlx_write_ps(x, 0);
  	__cs_mutex_unlock(&__cs_mlock);
	
	rlx_read_ps(x, _x);
	if (_x > 0) {
		rlx_read_ps(y, _y);
		_y = _y + 1;
		rlx_write_ps(y, _y);
		rlx_write_ps(x, 2);
	}
}


void *thr3(void *arg)
{
	int _x, _y;

	rlx_read_ps(x, _x);
	if(_x > 1) {
		rlx_read_ps(y, _y);
		if (_y == 3) {
			assert(0);
		}
	}

	rlx_read_ps(x, _x);
	if(_x > 1) {
		rlx_read_ps(y, _y);
		if (_y == 3) {
			assert(0);
		}
	}
}

int main(int argc, char **argv)
{

	pthread_t t1, t2, t3;
	
	x = 0;
	y = 0;
	
  	// cas_mutex = 0;
  	__cs_mutex_init(&__cs_mlock, 0);


	pthread_create(&t1, NULL, thr1, NULL);
	pthread_create(&t2, NULL, thr2, NULL);
	pthread_create(&t3, NULL, thr3, NULL);


	return 0;
}
