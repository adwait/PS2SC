/* Inspiration from the SVCOMP-2018 benchmarks
 */

// Adapted for the tool PSChecker 

 

#include <pthread.h>


int c1 = 0, c2 = 0;
int n1 = 0, n2 = 0;
int _cc_x;
int __fence_var;


void *t0()
{
  int rn1 = -1;
  int rn2 = -1;
  int rc2 = -1;
  int rx = -1;
  while (1) {
    c1 = 1;
    sc_fence();
    rn2 = n2;
    rn1 = rn2 + 1;
    n1 = rn1;
    sc_fence();
    c1 = 0;
    sc_fence();
    rc2 = c2;
    assume(rc2 == 0);
    sc_fence();
    rn2 = n2;
    sc_fence();
    assume(rn2 == 0 || rn1 < rn2);
    _cc_x = 0;
    rx = _cc_x;
    assert(rx<=0);
    sc_fence();
    n1 = 0;
  }
}



void *t1()
{
  int rn1 = -1;
  int rn2 = -1;
  int rc1 = -1;
  int rx = -1;
  while (1) {
    c2 = 1;
    sc_fence();
    rn1 = n1;
    rn2 = rn1 + 1;
    n2 = rn2;
    sc_fence();
    c2 = 0;
    sc_fence();
    rc1 = c1;
    assume(rc1 == 0);
    sc_fence();
    rn1 = n1;
    sc_fence();
    assume(rn1 == 0 || rn2 <= rn1);
    _cc_x = 1;
    rx = _cc_x;
    assert(rx>=1);
    sc_fence();
    n2 = 0;
  }
}

int *propertyChecking(void* arg)
{
    return 0;
}

int main()
{
    pthread_t _cs_t0, _cs_t1;
    pthread_create(&_cs_t0, 0, t0, 0);
    pthread_create(&_cs_t1, 0, t1, 0);
    return 0;
}


