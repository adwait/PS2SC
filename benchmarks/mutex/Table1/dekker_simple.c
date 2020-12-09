/* This example is taken from the SV-COMP benchmarks
 */

// Adapted for the tool PSChecker 

#include <pthread.h>


int x = 0, y = 0;
int _cc_X;


void *t0()
{
  int ry = -1;
  int rX  = -1;

  while (1) {
    x = 1;
    ry = y;     
    assume(ry == 0);
    _cc_X = 0;
    rX = _cc_X;
    assert(rX<=0);
    x = 0;
  }
}



void *t1()
{
  int rx = -1;
  int rX = -1;
  
  while (1) {
    y = 1;
    rx = x;
    assume(rx == 0);
    _cc_X = 1;
    rX = _cc_X;
    assert(rX>=1);
    y = 0;
  }
}

int *propertyChecking(void* arg)
{
    return 0;
}


int main()
{
    pthread_t _cs_t1, _cs_t2;
    pthread_create(&_cs_t1, 0, t0, 0);
    pthread_create(&_cs_t2, 0, t1, 0);
    return 0;
}
