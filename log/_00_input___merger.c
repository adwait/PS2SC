#include <pthread.h>



int var0; 
// int var1; 
int z1;
// int z2;
int casvar;
// int lv;
int fib1;
int fib2;

void *t0(){
  int __lv = 0;
  // int __fib = 0;
  // int _prev = 0;
  // int _curr = 1;
  int _n;
  
  rlx_read_ps(z1, __lv);
  if (__lv == 1){

    // rlx_write_ps(var0, 42);
    assert(0);
  }
  else{
    // cas_ps(casvar, 0, 1);

    rlx_read_ps(fib1, _n);
    
    // while(_n--){
    //   _curr = _prev + _curr;
    //   _prev = _curr - _prev;
    // }

    // _prev = 1;
    // assert(_prev != 1);

    // cas_ps(casvar, 0, 1);
    rlx_write_ps(var0, _n);
  }

}

void *t1(){
  int __lv;
  
  rlx_read_ps(var0, __lv);
  assume(__lv == 8);

  rlx_write_ps(z1, 1);
}


void *t2(){
  int _x;
  int _y;
  // int i;
  int _s;

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib1, _s);

    // rlx_read_ps(fib1, _x);
    // rlx_read_ps(fib2, _y);
    // _s = _x + _y;
    // rlx_write_ps(fib1, _s);

}

void *t3(){
  int _x;
  int _y;
  // int i;
  int _s;

  // for (i = 0; i < ITER; i++) {
    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);

    rlx_read_ps(fib1, _x);
    rlx_read_ps(fib2, _y);
    _s = _x + _y;
    rlx_write_ps(fib2, _s);

    // rlx_read_ps(fib1, _x);
    // rlx_read_ps(fib2, _y);
    // _s = _x + _y;
    // rlx_write_ps(fib2, _s);

    // rlx_read_ps(fib1, _x);
    // rlx_read_ps(fib2, _y);
    // _s = _x + _y;
    // rlx_write_ps(fib2, _s);
}




// void *t2(){
//   int __lv;
  
//   rlx_read_ps(var1, __lv);
//   assume(__lv == 42);

//   rlx_write_ps(z2, 1);
// }


int main(){
  pthread_t thr0; 
  pthread_t thr1; 
  pthread_t thr2; 
  pthread_t thr3; 
  // pthread_t thr2; 

  var0 = 0;
  // var1 = 0;
  // casvar = 0;
  z1 = 0;

  fib1 = 1;
  fib2 = 1;
  
  pthread_create(&thr2, 0, t2, 0);
  pthread_create(&thr3, 0, t3, 0);
  pthread_create(&thr0, 0, t0, 0);
  pthread_create(&thr1, 0, t1, 0);
  
  return 0;
}
