
/* Inspiration from the SVCOMP-2018 benchmarks
*/

// Adapted for the tool PSChecker 

#include <pthread.h>

int level0, level1, level2, level3, level4, level5, level6, level7;
int waiting0, waiting1, waiting2, waiting3, waiting4, waiting5, waiting6;
int _cc_x;

void* t0(){

int __level1;
int __level2;
int __level3;
int __level4;
int __level5;
int __level6;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
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
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level1 < 0 && __level2 < 0 && __level3 < 0 && __level4 < 0 && __level5 < 0 && __level6 < 0 && __level7 < 0 && 1));

rlx_write_ps(level0,1);
sc_fence();
rlx_write_ps(waiting1,0);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level1 < 1 && __level2 < 1 && __level3 < 1 && __level4 < 1 && __level5 < 1 && __level6 < 1 && __level7 < 1 && 1));

rlx_write_ps(level0,2);
sc_fence();
rlx_write_ps(waiting2,0);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level1 < 2 && __level2 < 2 && __level3 < 2 && __level4 < 2 && __level5 < 2 && __level6 < 2 && __level7 < 2 && 1));

rlx_write_ps(level0,3);
sc_fence();
rlx_write_ps(waiting3,0);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level1 < 3 && __level2 < 3 && __level3 < 3 && __level4 < 3 && __level5 < 3 && __level6 < 3 && __level7 < 3 && 1));

rlx_write_ps(level0,4);
sc_fence();
rlx_write_ps(waiting4,0);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level1 < 4 && __level2 < 4 && __level3 < 4 && __level4 < 4 && __level5 < 4 && __level6 < 4 && __level7 < 4 && 1));

rlx_write_ps(level0,5);
sc_fence();
rlx_write_ps(waiting5,0);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level1 < 5 && __level2 < 5 && __level3 < 5 && __level4 < 5 && __level5 < 5 && __level6 < 5 && __level7 < 5 && 1));

rlx_write_ps(level0,6);
sc_fence();
rlx_write_ps(waiting6,0);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level1 < 6 && __level2 < 6 && __level3 < 6 && __level4 < 6 && __level5 < 6 && __level6 < 6 && __level7 < 6 && 1));

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
int __level4;
int __level5;
int __level6;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
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
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level0 < 0 && __level2 < 0 && __level3 < 0 && __level4 < 0 && __level5 < 0 && __level6 < 0 && __level7 < 0 && 1));

rlx_write_ps(level1,1);
sc_fence();
rlx_write_ps(waiting1,1);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level0 < 1 && __level2 < 1 && __level3 < 1 && __level4 < 1 && __level5 < 1 && __level6 < 1 && __level7 < 1 && 1));

rlx_write_ps(level1,2);
sc_fence();
rlx_write_ps(waiting2,1);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level0 < 2 && __level2 < 2 && __level3 < 2 && __level4 < 2 && __level5 < 2 && __level6 < 2 && __level7 < 2 && 1));

rlx_write_ps(level1,3);
sc_fence();
rlx_write_ps(waiting3,1);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level0 < 3 && __level2 < 3 && __level3 < 3 && __level4 < 3 && __level5 < 3 && __level6 < 3 && __level7 < 3 && 1));

rlx_write_ps(level1,4);
sc_fence();
rlx_write_ps(waiting4,1);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level0 < 4 && __level2 < 4 && __level3 < 4 && __level4 < 4 && __level5 < 4 && __level6 < 4 && __level7 < 4 && 1));

rlx_write_ps(level1,5);
sc_fence();
rlx_write_ps(waiting5,1);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level0 < 5 && __level2 < 5 && __level3 < 5 && __level4 < 5 && __level5 < 5 && __level6 < 5 && __level7 < 5 && 1));

rlx_write_ps(level1,6);
sc_fence();
rlx_write_ps(waiting6,1);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level0 < 6 && __level2 < 6 && __level3 < 6 && __level4 < 6 && __level5 < 6 && __level6 < 6 && __level7 < 6 && 1));

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
int __level4;
int __level5;
int __level6;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
int ___cc_x;
while(1){
rlx_write_ps(level2,0);
rlx_write_ps(waiting0,2);

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level3 < 0 && __level4 < 0 && __level5 < 0 && __level6 < 0 && __level7 < 0 && 1));

rlx_write_ps(level2,1);
rlx_write_ps(waiting1,2);

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level3 < 1 && __level4 < 1 && __level5 < 1 && __level6 < 1 && __level7 < 1 && 1));

rlx_write_ps(level2,2);
rlx_write_ps(waiting2,2);

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level3 < 2 && __level4 < 2 && __level5 < 2 && __level6 < 2 && __level7 < 2 && 1));

rlx_write_ps(level2,3);
rlx_write_ps(waiting3,2);

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level0 < 3 && __level1 < 3 && __level3 < 3 && __level4 < 3 && __level5 < 3 && __level6 < 3 && __level7 < 3 && 1));

rlx_write_ps(level2,4);
rlx_write_ps(waiting4,2);

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level0 < 4 && __level1 < 4 && __level3 < 4 && __level4 < 4 && __level5 < 4 && __level6 < 4 && __level7 < 4 && 1));

rlx_write_ps(level2,5);
rlx_write_ps(waiting5,2);

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level0 < 5 && __level1 < 5 && __level3 < 5 && __level4 < 5 && __level5 < 5 && __level6 < 5 && __level7 < 5 && 1));

rlx_write_ps(level2,6);
rlx_write_ps(waiting6,2);

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level0 < 6 && __level1 < 6 && __level3 < 6 && __level4 < 6 && __level5 < 6 && __level6 < 6 && __level7 < 6 && 1));

rlx_write_ps(_cc_x, 2);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 2);
rlx_write_ps(level2, 0);
}
}


void* t3(){

int __level0;
int __level1;
int __level2;
int __level4;
int __level5;
int __level6;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
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
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level2 < 0 && __level4 < 0 && __level5 < 0 && __level6 < 0 && __level7 < 0 && 1));

rlx_write_ps(level3,1);
sc_fence();
rlx_write_ps(waiting1,3);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level2 < 1 && __level4 < 1 && __level5 < 1 && __level6 < 1 && __level7 < 1 && 1));

rlx_write_ps(level3,2);
sc_fence();
rlx_write_ps(waiting2,3);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level2 < 2 && __level4 < 2 && __level5 < 2 && __level6 < 2 && __level7 < 2 && 1));

rlx_write_ps(level3,3);
sc_fence();
rlx_write_ps(waiting3,3);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level0 < 3 && __level1 < 3 && __level2 < 3 && __level4 < 3 && __level5 < 3 && __level6 < 3 && __level7 < 3 && 1));

rlx_write_ps(level3,4);
sc_fence();
rlx_write_ps(waiting4,3);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level0 < 4 && __level1 < 4 && __level2 < 4 && __level4 < 4 && __level5 < 4 && __level6 < 4 && __level7 < 4 && 1));

rlx_write_ps(level3,5);
sc_fence();
rlx_write_ps(waiting5,3);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level0 < 5 && __level1 < 5 && __level2 < 5 && __level4 < 5 && __level5 < 5 && __level6 < 5 && __level7 < 5 && 1));

rlx_write_ps(level3,6);
sc_fence();
rlx_write_ps(waiting6,3);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level0 < 6 && __level1 < 6 && __level2 < 6 && __level4 < 6 && __level5 < 6 && __level6 < 6 && __level7 < 6 && 1));

rlx_write_ps(_cc_x, 3);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 3);
sc_fence();
rlx_write_ps(level3, 0);
}
}


void* t4(){

int __level0;
int __level1;
int __level2;
int __level3;
int __level5;
int __level6;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
int ___cc_x;
while(1){
rlx_write_ps(level4,0);
sc_fence();
rlx_write_ps(waiting0,4);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level2 < 0 && __level3 < 0 && __level5 < 0 && __level6 < 0 && __level7 < 0 && 1));

rlx_write_ps(level4,1);
sc_fence();
rlx_write_ps(waiting1,4);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level2 < 1 && __level3 < 1 && __level5 < 1 && __level6 < 1 && __level7 < 1 && 1));

rlx_write_ps(level4,2);
sc_fence();
rlx_write_ps(waiting2,4);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level2 < 2 && __level3 < 2 && __level5 < 2 && __level6 < 2 && __level7 < 2 && 1));

rlx_write_ps(level4,3);
sc_fence();
rlx_write_ps(waiting3,4);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level0 < 3 && __level1 < 3 && __level2 < 3 && __level3 < 3 && __level5 < 3 && __level6 < 3 && __level7 < 3 && 1));

rlx_write_ps(level4,4);
sc_fence();
rlx_write_ps(waiting4,4);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level0 < 4 && __level1 < 4 && __level2 < 4 && __level3 < 4 && __level5 < 4 && __level6 < 4 && __level7 < 4 && 1));

rlx_write_ps(level4,5);
sc_fence();
rlx_write_ps(waiting5,4);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level0 < 5 && __level1 < 5 && __level2 < 5 && __level3 < 5 && __level5 < 5 && __level6 < 5 && __level7 < 5 && 1));

rlx_write_ps(level4,6);
sc_fence();
rlx_write_ps(waiting6,4);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level0 < 6 && __level1 < 6 && __level2 < 6 && __level3 < 6 && __level5 < 6 && __level6 < 6 && __level7 < 6 && 1));

rlx_write_ps(_cc_x, 4);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 4);
sc_fence();
rlx_write_ps(level4, 0);
}
}


void* t5(){

int __level0;
int __level1;
int __level2;
int __level3;
int __level4;
int __level6;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
int ___cc_x;
while(1){
rlx_write_ps(level5,0);
sc_fence();
rlx_write_ps(waiting0,5);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level2 < 0 && __level3 < 0 && __level4 < 0 && __level6 < 0 && __level7 < 0 && 1));

rlx_write_ps(level5,1);
sc_fence();
rlx_write_ps(waiting1,5);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level2 < 1 && __level3 < 1 && __level4 < 1 && __level6 < 1 && __level7 < 1 && 1));

rlx_write_ps(level5,2);
sc_fence();
rlx_write_ps(waiting2,5);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level2 < 2 && __level3 < 2 && __level4 < 2 && __level6 < 2 && __level7 < 2 && 1));

rlx_write_ps(level5,3);
sc_fence();
rlx_write_ps(waiting3,5);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level0 < 3 && __level1 < 3 && __level2 < 3 && __level3 < 3 && __level4 < 3 && __level6 < 3 && __level7 < 3 && 1));

rlx_write_ps(level5,4);
sc_fence();
rlx_write_ps(waiting4,5);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level0 < 4 && __level1 < 4 && __level2 < 4 && __level3 < 4 && __level4 < 4 && __level6 < 4 && __level7 < 4 && 1));

rlx_write_ps(level5,5);
sc_fence();
rlx_write_ps(waiting5,5);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level0 < 5 && __level1 < 5 && __level2 < 5 && __level3 < 5 && __level4 < 5 && __level6 < 5 && __level7 < 5 && 1));

rlx_write_ps(level5,6);
sc_fence();
rlx_write_ps(waiting6,5);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level6, __level6);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level0 < 6 && __level1 < 6 && __level2 < 6 && __level3 < 6 && __level4 < 6 && __level6 < 6 && __level7 < 6 && 1));

rlx_write_ps(_cc_x, 5);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 5);
sc_fence();
rlx_write_ps(level5, 0);
}
}


void* t6(){

int __level0;
int __level1;
int __level2;
int __level3;
int __level4;
int __level5;
int __level7;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
int ___cc_x;
while(1){
rlx_write_ps(level6,0);
sc_fence();
rlx_write_ps(waiting0,6);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level2 < 0 && __level3 < 0 && __level4 < 0 && __level5 < 0 && __level7 < 0 && 1));

rlx_write_ps(level6,1);
sc_fence();
rlx_write_ps(waiting1,6);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level2 < 1 && __level3 < 1 && __level4 < 1 && __level5 < 1 && __level7 < 1 && 1));

rlx_write_ps(level6,2);
sc_fence();
rlx_write_ps(waiting2,6);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level2 < 2 && __level3 < 2 && __level4 < 2 && __level5 < 2 && __level7 < 2 && 1));

rlx_write_ps(level6,3);
sc_fence();
rlx_write_ps(waiting3,6);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting3!= 0 || (__level0 < 3 && __level1 < 3 && __level2 < 3 && __level3 < 3 && __level4 < 3 && __level5 < 3 && __level7 < 3 && 1));

rlx_write_ps(level6,4);
sc_fence();
rlx_write_ps(waiting4,6);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting4!= 0 || (__level0 < 4 && __level1 < 4 && __level2 < 4 && __level3 < 4 && __level4 < 4 && __level5 < 4 && __level7 < 4 && 1));

rlx_write_ps(level6,5);
sc_fence();
rlx_write_ps(waiting5,6);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting5!= 0 || (__level0 < 5 && __level1 < 5 && __level2 < 5 && __level3 < 5 && __level4 < 5 && __level5 < 5 && __level7 < 5 && 1));

rlx_write_ps(level6,6);
sc_fence();
rlx_write_ps(waiting6,6);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level7, __level7);

assume(__waiting6!= 0 || (__level0 < 6 && __level1 < 6 && __level2 < 6 && __level3 < 6 && __level4 < 6 && __level5 < 6 && __level7 < 6 && 1));

rlx_write_ps(_cc_x, 6);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 6);
sc_fence();
rlx_write_ps(level6, 0);
}
}


void* t7(){

int __level0;
int __level1;
int __level2;
int __level3;
int __level4;
int __level5;
int __level6;
int __waiting0;
int __waiting1;
int __waiting2;
int __waiting3;
int __waiting4;
int __waiting5;
int __waiting6;
int ___cc_x;
while(1){
rlx_write_ps(level7,0);
sc_fence();
rlx_write_ps(waiting0,7);
sc_fence();

rlx_read_ps(waiting0, __waiting0);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting0!= 0 || (__level0 < 0 && __level1 < 0 && __level2 < 0 && __level3 < 0 && __level4 < 0 && __level5 < 0 && __level6 < 0 && 1));

rlx_write_ps(level7,1);
sc_fence();
rlx_write_ps(waiting1,7);
sc_fence();

rlx_read_ps(waiting1, __waiting1);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting1!= 0 || (__level0 < 1 && __level1 < 1 && __level2 < 1 && __level3 < 1 && __level4 < 1 && __level5 < 1 && __level6 < 1 && 1));

rlx_write_ps(level7,2);
sc_fence();
rlx_write_ps(waiting2,7);
sc_fence();

rlx_read_ps(waiting2, __waiting2);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting2!= 0 || (__level0 < 2 && __level1 < 2 && __level2 < 2 && __level3 < 2 && __level4 < 2 && __level5 < 2 && __level6 < 2 && 1));

rlx_write_ps(level7,3);
sc_fence();
rlx_write_ps(waiting3,7);
sc_fence();

rlx_read_ps(waiting3, __waiting3);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting3!= 0 || (__level0 < 3 && __level1 < 3 && __level2 < 3 && __level3 < 3 && __level4 < 3 && __level5 < 3 && __level6 < 3 && 1));

rlx_write_ps(level7,4);
sc_fence();
rlx_write_ps(waiting4,7);
sc_fence();

rlx_read_ps(waiting4, __waiting4);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting4!= 0 || (__level0 < 4 && __level1 < 4 && __level2 < 4 && __level3 < 4 && __level4 < 4 && __level5 < 4 && __level6 < 4 && 1));

rlx_write_ps(level7,5);
sc_fence();
rlx_write_ps(waiting5,7);
sc_fence();

rlx_read_ps(waiting5, __waiting5);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting5!= 0 || (__level0 < 5 && __level1 < 5 && __level2 < 5 && __level3 < 5 && __level4 < 5 && __level5 < 5 && __level6 < 5 && 1));

rlx_write_ps(level7,6);
sc_fence();
rlx_write_ps(waiting6,7);
sc_fence();

rlx_read_ps(waiting6, __waiting6);
rlx_read_ps(level0, __level0);
rlx_read_ps(level1, __level1);
rlx_read_ps(level2, __level2);
rlx_read_ps(level3, __level3);
rlx_read_ps(level4, __level4);
rlx_read_ps(level5, __level5);
rlx_read_ps(level6, __level6);

assume(__waiting6!= 0 || (__level0 < 6 && __level1 < 6 && __level2 < 6 && __level3 < 6 && __level4 < 6 && __level5 < 6 && __level6 < 6 && 1));

rlx_write_ps(_cc_x, 7);
rlx_read_ps(_cc_x, ___cc_x);
assert(___cc_x == 7);
sc_fence();
rlx_write_ps(level7, 0);
}
}


int main(){
	pthread_t _cs_tdiff0, _cs_tdiff1, _cs_tdiff2, _cs_tdiff3, _cs_tdiff4, _cs_tdiff5, _cs_tdiff6, _cs_tdiff7;
	pthread_create(&_cs_tdiff0, 0, t0, 0);
	pthread_create(&_cs_tdiff1, 0, t1, 0);
	pthread_create(&_cs_tdiff2, 0, t2, 0);
	pthread_create(&_cs_tdiff3, 0, t3, 0);
	pthread_create(&_cs_tdiff4, 0, t4, 0);
	pthread_create(&_cs_tdiff5, 0, t5, 0);
	pthread_create(&_cs_tdiff6, 0, t6, 0);
	pthread_create(&_cs_tdiff7, 0, t7, 0);
	return 0;
}

