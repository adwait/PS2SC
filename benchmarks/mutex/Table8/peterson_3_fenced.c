/* Inspiration from the SVCOMP-2018 benchmarks
 */

// Adapted for the tool PSChecker 

 

#include <pthread.h>


 int level0 = 0, level1 = 0, level2 = 0;
 int waiting0 = 0, waiting1 = 0;
int _cc_x;
int __fence_var;

void *t0()
{
  int rwaiting = -1, rlevel1 = -1, rlevel2 = -1, rx = -1;
  while (1) {
    level0 = 0;
    sc_fence();
    waiting0 = 0;
    sc_fence();
    rwaiting = waiting0;
    rlevel1 = level1;
    rlevel2 = level2;
    assume(rwaiting != 0 || (rlevel1 < 0 && rlevel2 < 0));
    level0 = 1;
    sc_fence();
    waiting1 = 0;
    sc_fence();
    rwaiting = waiting1;
    rlevel1 = level1;
    rlevel2 = level2;
    sc_fence();
    assume(rwaiting != 0 || (rlevel1 < 1 && rlevel2 < 1));
    _cc_x = 0;
    rx = _cc_x;
    assert(rx==0);
    sc_fence();
    level0 = 0;
  }
}

void *t1()
{
  int rwaiting = -1, rlevel0 = -1, rlevel2 = -1, rx = -1;
  while (1) {
    level1 = 0;
    sc_fence();
    waiting0 = 1;
    sc_fence();
    rwaiting = waiting0;
    rlevel2 = level2;
    rlevel0 = level0;
    assume(rwaiting != 1 || (rlevel2 < 0 && rlevel0 < 0));
    level1 = 1;
    sc_fence();
    waiting1 = 1;
    sc_fence();
    rwaiting = waiting1;
    rlevel2 = level2;
    rlevel0 = level0;
    sc_fence();
    assume(rwaiting != 1 || (rlevel2 < 1 && rlevel0 < 1));
    _cc_x = 1;
    rx = _cc_x;
    sc_fence();
    assert(rx==1);
    level1 = 0;
  }
}


void *t2()
{
  int rwaiting = -1, rlevel0 = -1, rlevel1 = -1, rx = -1;
  while (1) {
    level2 = 0;
    sc_fence();
    waiting0 = 2;
    sc_fence();
    rwaiting = waiting0;
    rlevel1 = level1;
    rlevel0 = level0;
    assume(rwaiting != 2 || (rlevel1 < 0 && rlevel0 < 0));
    level2 = 1;
    sc_fence();
    waiting1 = 2;
    sc_fence();
    rwaiting = waiting1;
    rlevel1 = level1;
    rlevel0 = level0;
    sc_fence();
    assume(rwaiting != 2 || (rlevel1 < 1 && rlevel0 < 1));
    _cc_x = 2;
    rx = _cc_x;
    assert(rx==2);
    sc_fence();
    level2 = 0;
  }
}


int *propertyChecking(void* arg)
{
    return 0;
}

int main()
{
    pthread_t _cs_t0, _cs_t1, _cs_t2;
    pthread_create(&_cs_t0, 0, t0, 0);
    pthread_create(&_cs_t1, 0, t1, 0);
    pthread_create(&_cs_t2, 0, t2, 0);
    return 0;
}
