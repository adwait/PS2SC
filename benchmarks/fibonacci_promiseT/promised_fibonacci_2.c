#include <pthread.h>

#define N 2
#define FIBN 8


int var0; 
int z1;
int fib1;
int fib2;

void *t0(){
  int _x;
  int _y;
  int _s;

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);
}

void *t1(){
  int _x;
  int _y;
  int _s;

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);
}

void *t2(){
  int __lv = 0;
  int __n;
  
  rlx_read_ps(z1, __lv);

  if (__lv == 1){
    assert(0);
  }
  else{
    rlx_read_ps(fib1, __n);
    rlx_write_ps(var0, __n);
  }
}

void *t3(){
  int __lv;
  
  rlx_read_ps(var0, __lv);
  assume(__lv == FIBN);

  rlx_write_ps(z1, 1);
}


int main(){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 

  var0 = 0;
  z1 = 0;

  fib1 = 1;
  fib2 = 1;
  
  pthread_create(&thr0, 0, t0, 0);
  pthread_create(&thr1, 0, t1, 0);
  pthread_create(&thr2, 0, t2, 0);
  pthread_create(&thr3, 0, t3, 0);
  
  return 0;
}
