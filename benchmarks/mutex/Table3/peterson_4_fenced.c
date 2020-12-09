
/* Inspiration from the SVCOMP-2018 benchmarks
*/

// Adapted for the tool PSChecker 

#include <pthread.h>

int level0, level1, level2, level3;
int waiting0, waiting1, waiting2;
int _cc_x;

void* t0(){

int __level1;
int __level2;
int __level3;
int __waiting0;
int __waiting1;
int __waiting2;
int ___cc_x;
while(1){
rlx_write_ps(level0,0);
sc_fence();
rlx_write_ps(waiting0,0);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);

assume(__waiting0!= 0 || (__level1 < 0 && __level2 < 0 && __level3 < 0 && 1));

rlx_write_ps(level0,1);
sc_fence();
rlx_write_ps(waiting1,0);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);

assume(__waiting1!= 0 || (__level1 < 1 && __level2 < 1 && __level3 < 1 && 1));

rlx_write_ps(level0,2);
sc_fence();
rlx_write_ps(waiting2,0);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);

assume(__waiting2!= 0 || (__level1 < 2 && __level2 < 2 && __level3 < 2 && 1));

rlx_write_ps(_cc_x, 0);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 0);
sc_fence();
rlx_write_ps(level0, 0);
}
}


void* t1(){

int __level0;
int __level2;
int __level3;
int __waiting0;
int __waiting1;
int __waiting2;
int ___cc_x;
while(1){
rlx_write_ps(level1,0);
sc_fence();
rlx_write_ps(waiting0,1);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);

assume(__waiting0!= 0 || (__level0 < 0 && __level2 < 0 && __level3 < 0 && 1));

rlx_write_ps(level1,1);
sc_fence();
rlx_write_ps(waiting1,1);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);

assume(__waiting1!= 0 || (__level0 < 1 && __level2 < 1 && __level3 < 1 && 1));

rlx_write_ps(level1,2);
sc_fence();
rlx_write_ps(waiting2,1);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);

assume(__waiting2!= 0 || (__level0 < 2 && __level2 < 2 && __level3 < 2 && 1));

rlx_write_ps(_cc_x, 1);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 1);
sc_fence();
rlx_write_ps(level1, 0);
}
}


void* t2(){

int __level0;
int __level1;
int __level3;
int __waiting0;
int __waiting1;
int __waiting2;
int ___cc_x;
while(1){
rlx_write_ps(level2,0);
rlx_write_ps(waiting0,2);

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level3 < 0 && 1));

rlx_write_ps(level2,1);
rlx_write_ps(waiting1,2);

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level3 < 1 && 1));

rlx_write_ps(level2,2);
rlx_write_ps(waiting2,2);

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level3 < 2 && 1));

rlx_write_ps(_cc_x, 1);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 2);
rlx_write_ps(level2, 0);
}
}


void* t3(){

int __level0;
int __level1;
int __level2;
int __waiting0;
int __waiting1;
int __waiting2;
int ___cc_x;
while(1){
rlx_write_ps(level3,0);
sc_fence();
rlx_write_ps(waiting0,3);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level2 < 0 && 1));

rlx_write_ps(level3,1);
sc_fence();
rlx_write_ps(waiting1,3);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level2 < 1 && 1));

rlx_write_ps(level3,2);
sc_fence();
rlx_write_ps(waiting2,3);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level2 < 2 && 1));

rlx_write_ps(_cc_x, 3);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 3);
sc_fence();
rlx_write_ps(level3, 0);
}
}


int main(){
	pthread_t _cs_tdiff0, _cs_tdiff1, _cs_tdiff2, _cs_tdiff3;
	pthread_create(&_cs_tdiff0, 0, t0, 0);
	pthread_create(&_cs_tdiff1, 0, t1, 0);
	pthread_create(&_cs_tdiff2, 0, t2, 0);
	pthread_create(&_cs_tdiff3, 0, t3, 0);
	return 0;
}

