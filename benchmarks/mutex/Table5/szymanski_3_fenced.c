
/* Inspiration from the SVCOMP-2018 benchmarks
*/

// Adapted for the tool PSChecker 

#include <pthread.h>

int flag0, flag1, flag2;
int _cc_x;

void* t0(){

int __flag1;
int __flag2;
int ___cc_x;
while(1){
rlx_write_ps(flag0, 1);
sc_fence();

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
assume(__flag1< 3 && __flag2< 3);
rlx_write_ps(flag0, 3);
sc_fence();

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
if(__flag1==1 || __flag2==1){
	rlx_write_ps(flag0,2);
	sc_fence();

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
	assume(__flag1==4 || __flag2==4);
}
rlx_write_ps(flag0, 4);
sc_fence();

rlx_write_ps(_cc_x, 0);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 0);

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
assume(__flag1 != 2 && __flag1!= 3 && __flag2 != 2 && __flag2!= 3);
rlx_write_ps(flag0, 0);
}
}


void* t1(){

int __flag0;
int __flag2;
int ___cc_x;
while(1){
rlx_write_ps(flag1, 1);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag2, __flag2);
assume(__flag0< 3 && __flag2< 3);
rlx_write_ps(flag1, 3);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag2, __flag2);
if(__flag0==1 || __flag2==1){
	rlx_write_ps(flag1,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag2, __flag2);
	assume(__flag0==4 || __flag2==4);
}
rlx_write_ps(flag1, 4);
sc_fence();

rlx_read_ps(flag0, __flag0);
assume(__flag0 < 2);
rlx_write_ps(_cc_x, 1);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 1);

rlx_read_ps(flag2, __flag2);
assume(__flag2 != 2 && __flag2!= 3);
rlx_write_ps(flag1, 0);
}
}


void* t2(){

int __flag0;
int __flag1;
int ___cc_x;
while(1){
rlx_write_ps(flag2, 1);

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
assume(__flag0< 3 && __flag1< 3);
rlx_write_ps(flag2, 3);

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
if(__flag0==1 || __flag1==1){
	rlx_write_ps(flag2,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
	assume(__flag0==4 || __flag1==4);
}
rlx_write_ps(flag2, 4);

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
assume(__flag0 < 2 && __flag1 < 2);
rlx_write_ps(_cc_x, 1);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 2);

rlx_write_ps(flag2, 0);
}
}


int main(){
	pthread_t _cs_tdiff0, _cs_tdiff1, _cs_tdiff2;
	pthread_create(&_cs_tdiff0, 0, t0, 0);
	pthread_create(&_cs_tdiff1, 0, t1, 0);
	pthread_create(&_cs_tdiff2, 0, t2, 0);
	return 0;
}

