
/* Inspiration from the SVCOMP-2018 benchmarks
*/

// Adapted for the tool PSChecker 

#include <pthread.h>

int flag0, flag1, flag2, flag3, flag4, flag5, flag6;
int _cc_x;

void* t0(){

int __flag1;
int __flag2;
int __flag3;
int __flag4;
int __flag5;
int __flag6;
int ___cc_x;
while(1){
rlx_write_ps(flag0, 1);
sc_fence();

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag1< 3 && __flag2< 3 && __flag3< 3 && __flag4< 3 && __flag5< 3 && __flag6< 3);
rlx_write_ps(flag0, 3);
sc_fence();

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
if(__flag1==1 || __flag2==1 || __flag3==1 || __flag4==1 || __flag5==1 || __flag6==1){
	rlx_write_ps(flag0,2);
	sc_fence();

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
	assume(__flag1==4 || __flag2==4 || __flag3==4 || __flag4==4 || __flag5==4 || __flag6==4);
}
rlx_write_ps(flag0, 4);
sc_fence();

rlx_write_ps(_cc_x, 0);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 0);

rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag1 != 2 && __flag1!= 3 && __flag2 != 2 && __flag2!= 3 && __flag3 != 2 && __flag3!= 3 && __flag4 != 2 && __flag4!= 3 && __flag5 != 2 && __flag5!= 3 && __flag6 != 2 && __flag6!= 3);
rlx_write_ps(flag0, 0);
}
}


void* t1(){

int __flag0;
int __flag2;
int __flag3;
int __flag4;
int __flag5;
int __flag6;
int ___cc_x;
while(1){
rlx_write_ps(flag1, 1);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag0< 3 && __flag2< 3 && __flag3< 3 && __flag4< 3 && __flag5< 3 && __flag6< 3);
rlx_write_ps(flag1, 3);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
if(__flag0==1 || __flag2==1 || __flag3==1 || __flag4==1 || __flag5==1 || __flag6==1){
	rlx_write_ps(flag1,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
	assume(__flag0==4 || __flag2==4 || __flag3==4 || __flag4==4 || __flag5==4 || __flag6==4);
}
rlx_write_ps(flag1, 4);
sc_fence();

rlx_read_ps(flag0, __flag0);
assume(__flag0 < 2);
rlx_write_ps(_cc_x, 1);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 1);

rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag2 != 2 && __flag2!= 3 && __flag3 != 2 && __flag3!= 3 && __flag4 != 2 && __flag4!= 3 && __flag5 != 2 && __flag5!= 3 && __flag6 != 2 && __flag6!= 3);
rlx_write_ps(flag1, 0);
}
}


void* t2(){

int __flag0;
int __flag1;
int __flag3;
int __flag4;
int __flag5;
int __flag6;
int ___cc_x;
while(1){
rlx_write_ps(flag2, 1);

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag0< 3 && __flag1< 3 && __flag3< 3 && __flag4< 3 && __flag5< 3 && __flag6< 3);
rlx_write_ps(flag2, 3);

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
if(__flag0==1 || __flag1==1 || __flag3==1 || __flag4==1 || __flag5==1 || __flag6==1){
	rlx_write_ps(flag2,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
	assume(__flag0==4 || __flag1==4 || __flag3==4 || __flag4==4 || __flag5==4 || __flag6==4);
}
rlx_write_ps(flag2, 4);

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
assume(__flag0 < 2 && __flag1 < 2);
rlx_write_ps(_cc_x, 1);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 2);

rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag3 != 2 && __flag3!= 3 && __flag4 != 2 && __flag4!= 3 && __flag5 != 2 && __flag5!= 3 && __flag6 != 2 && __flag6!= 3);
rlx_write_ps(flag2, 0);
}
}


void* t3(){

int __flag0;
int __flag1;
int __flag2;
int __flag4;
int __flag5;
int __flag6;
int ___cc_x;
while(1){
rlx_write_ps(flag3, 1);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag0< 3 && __flag1< 3 && __flag2< 3 && __flag4< 3 && __flag5< 3 && __flag6< 3);
rlx_write_ps(flag3, 3);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
if(__flag0==1 || __flag1==1 || __flag2==1 || __flag4==1 || __flag5==1 || __flag6==1){
	rlx_write_ps(flag3,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
	assume(__flag0==4 || __flag1==4 || __flag2==4 || __flag4==4 || __flag5==4 || __flag6==4);
}
rlx_write_ps(flag3, 4);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
assume(__flag0 < 2 && __flag1 < 2 && __flag2 < 2);
rlx_write_ps(_cc_x, 3);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 3);

rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag4 != 2 && __flag4!= 3 && __flag5 != 2 && __flag5!= 3 && __flag6 != 2 && __flag6!= 3);
rlx_write_ps(flag3, 0);
}
}


void* t4(){

int __flag0;
int __flag1;
int __flag2;
int __flag3;
int __flag5;
int __flag6;
int ___cc_x;
while(1){
rlx_write_ps(flag4, 1);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag0< 3 && __flag1< 3 && __flag2< 3 && __flag3< 3 && __flag5< 3 && __flag6< 3);
rlx_write_ps(flag4, 3);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
if(__flag0==1 || __flag1==1 || __flag2==1 || __flag3==1 || __flag5==1 || __flag6==1){
	rlx_write_ps(flag4,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
	assume(__flag0==4 || __flag1==4 || __flag2==4 || __flag3==4 || __flag5==4 || __flag6==4);
}
rlx_write_ps(flag4, 4);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
assume(__flag0 < 2 && __flag1 < 2 && __flag2 < 2 && __flag3 < 2);
rlx_write_ps(_cc_x, 4);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 4);

rlx_read_ps(flag5, __flag5);
rlx_read_ps(flag6, __flag6);
assume(__flag5 != 2 && __flag5!= 3 && __flag6 != 2 && __flag6!= 3);
rlx_write_ps(flag4, 0);
}
}


void* t5(){

int __flag0;
int __flag1;
int __flag2;
int __flag3;
int __flag4;
int __flag6;
int ___cc_x;
while(1){
rlx_write_ps(flag5, 1);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag6, __flag6);
assume(__flag0< 3 && __flag1< 3 && __flag2< 3 && __flag3< 3 && __flag4< 3 && __flag6< 3);
rlx_write_ps(flag5, 3);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag6, __flag6);
if(__flag0==1 || __flag1==1 || __flag2==1 || __flag3==1 || __flag4==1 || __flag6==1){
	rlx_write_ps(flag5,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag6, __flag6);
	assume(__flag0==4 || __flag1==4 || __flag2==4 || __flag3==4 || __flag4==4 || __flag6==4);
}
rlx_write_ps(flag5, 4);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
assume(__flag0 < 2 && __flag1 < 2 && __flag2 < 2 && __flag3 < 2 && __flag4 < 2);
rlx_write_ps(_cc_x, 5);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 5);

rlx_read_ps(flag6, __flag6);
assume(__flag6 != 2 && __flag6!= 3);
rlx_write_ps(flag5, 0);
}
}


void* t6(){

int __flag0;
int __flag1;
int __flag2;
int __flag3;
int __flag4;
int __flag5;
int ___cc_x;
while(1){
rlx_write_ps(flag6, 1);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
assume(__flag0< 3 && __flag1< 3 && __flag2< 3 && __flag3< 3 && __flag4< 3 && __flag5< 3);
rlx_write_ps(flag6, 3);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
if(__flag0==1 || __flag1==1 || __flag2==1 || __flag3==1 || __flag4==1 || __flag5==1){
	rlx_write_ps(flag6,2);
	sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
	assume(__flag0==4 || __flag1==4 || __flag2==4 || __flag3==4 || __flag4==4 || __flag5==4);
}
rlx_write_ps(flag6, 4);
sc_fence();

rlx_read_ps(flag0, __flag0);
rlx_read_ps(flag1, __flag1);
rlx_read_ps(flag2, __flag2);
rlx_read_ps(flag3, __flag3);
rlx_read_ps(flag4, __flag4);
rlx_read_ps(flag5, __flag5);
assume(__flag0 < 2 && __flag1 < 2 && __flag2 < 2 && __flag3 < 2 && __flag4 < 2 && __flag5 < 2);
rlx_write_ps(_cc_x, 6);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 6);

rlx_write_ps(flag6, 0);
}
}


int main(){
	pthread_t _cs_tdiff0, _cs_tdiff1, _cs_tdiff2, _cs_tdiff3, _cs_tdiff4, _cs_tdiff5, _cs_tdiff6;
	pthread_create(&_cs_tdiff0, 0, t0, 0);
	pthread_create(&_cs_tdiff1, 0, t1, 0);
	pthread_create(&_cs_tdiff2, 0, t2, 0);
	pthread_create(&_cs_tdiff3, 0, t3, 0);
	pthread_create(&_cs_tdiff4, 0, t4, 0);
	pthread_create(&_cs_tdiff5, 0, t5, 0);
	pthread_create(&_cs_tdiff6, 0, t6, 0);
	return 0;
}

