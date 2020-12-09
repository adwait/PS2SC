/* Inspired from example in Figure 2 in the PLDI 2015 paper: 
   https://dl.acm.org/citation.cfm?id=2737975
*/

// Adapted for the tool PSChecker

#include <pthread.h>

#define N 15

// shared variables
int x, y;
int cas_mutex;

void *thr1(void *arg)
{
	int i;

  	cas_ps(cas_mutex, 1, 0);
	x = 1;
	for (i=0; i<N; i++) {
		y = 1;
	}
  	cas_ps(cas_mutex, 0, 1);

  	cas_ps(cas_mutex, 1, 0);
	x = 1;
	for (i=0; i<N; i++) {
		y = 1;
	}
  	cas_ps(cas_mutex, 0, 1);

}

void *thr2(void *arg)
{
	int _y;

  	cas_ps(cas_mutex, 1, 0);
	x = 0;
  	cas_ps(cas_mutex, 0, 1);
	
	if (x > 0) {
		_y = y;
		y = _y + 1;
		x = 2;
	}

  	cas_ps(cas_mutex, 1, 0);
	x = 0;
  	cas_ps(cas_mutex, 0, 1);
	
	if (x > 0) {
		_y = y;
		y = _y + 1;
		x = 2;

	}
}


void *thr3(void *arg)
{
	
	if(x > 1) {
		if (y == 3) {
			assert(0);
		}
	}

	if(x > 1) {
		if(y == 3) {
			assert(0);
		}
	}
}

int main(int argc, char **argv)
{

	pthread_t t1, t2, t3;
	
	x = 0;
	y = 0;
	
  	cas_mutex = 0;


	pthread_create(&t1, NULL, thr1, NULL);
	pthread_create(&t2, NULL, thr2, NULL);
	pthread_create(&t3, NULL, thr3, NULL);


	return 0;
}
