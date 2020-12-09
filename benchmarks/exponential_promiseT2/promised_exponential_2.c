/* Inspired from example in Figure 2 in the PLDI 2015 paper: 
   https://dl.acm.org/citation.cfm?id=2737975
*/

// Adapted for the tool PSChecker

#include <pthread.h>

#define N 2

// shared variables
int x, y;
int z1, var0;
int __cs_mlock;

void *t0(void *arg)
{
	int i;

  	__cs_mutex_lock(&__cs_mlock);
		rlx_write_ps(x, 1);

		rlx_write_ps(y, 1);
		rlx_write_ps(y, 1);
  	__cs_mutex_unlock(&__cs_mlock);

  	__cs_mutex_lock(&__cs_mlock);
		rlx_write_ps(x, 1);
	
		rlx_write_ps(y, 1);
		rlx_write_ps(y, 1);
	__cs_mutex_unlock(&__cs_mlock);

}

void *t1(void *arg)
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


void *t2(void *arg)
{
	int _x, _y;
	int __lv;

	rlx_read_ps(z1, __lv);
	if (__lv == 1){
		assert(0);
	}
	else{
		rlx_read_ps(x, _x); 
		assume(_x > 1);  
		rlx_read_ps(y, _y);
		rlx_write_ps(var0, _y);
	}
}

void *t3(void *arg)
{
  int __lv;
  
  rlx_read_ps(var0, __lv);
  assume(__lv == 3);

  rlx_write_ps(z1, 1);
}

int main(int argc, char **argv)
{

	pthread_t thr0, thr1, thr2, thr3;
	
	x = 0;
	y = 0;
	var0 = 0;
	z1 = 0;
	
  	// cas_mutex = 0;
  	__cs_mutex_init(&__cs_mlock, 0);


	pthread_create(&thr0, NULL, t0, NULL);
	pthread_create(&thr1, NULL, t1, NULL);
	pthread_create(&thr2, NULL, t2, NULL);
	pthread_create(&thr3, NULL, t3, NULL);

	return 0;
}
