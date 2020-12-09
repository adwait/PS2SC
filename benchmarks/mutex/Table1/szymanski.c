/* This example is taken from the SV-COMP benchmarks
 */

// Adapted for the tool PSChecker 

#include <pthread.h>
#define assert(e) if (!(e)) ERROR: goto ERROR;

int flag1 = 0, flag2 = 0;
int _cc_x;



void *t0()
{
  int rflag2 = -1, rx=-1;
  while (1) {
    flag1 = 1;
    rflag2 = flag2;
    assume(rflag2 <3);
    flag1 = 3;
    rflag2 = flag2;
    if (rflag2 == 1)
    {
        flag1 = 2;
        rflag2 = flag2;
        assume(rflag2 == 4);
    }
    flag1 = 4;
    rflag2 = flag2;
    assume(rflag2 < 2);
    _cc_x = 0;
    rx = _cc_x;
    assert(rx<=0);
    rflag2 = flag2;
    assume(2>rflag2 || rflag2 > 3);
    flag1 = 0;
  }
}

void *t1()
{
  int rflag1 = -1, rx=-1;
  while (1) {
    flag2 = 1;
    rflag1 = flag1;
    assume(rflag1 < 3);
    flag2 = 3;
    rflag1 = flag1;
    if (rflag1 == 1)
    {
        flag2 = 2;
        rflag1 = flag1;
        assume(rflag1 == 4);
    }
    flag2 = 4;
    rflag1 = flag1;
    assume(rflag1 < 2);
    _cc_x = 1;
    rx = _cc_x;
    assert(rx>=1);
    rflag1 = flag1;
    assume(2 > rflag1 || rflag1 > 3);
    flag2 = 0;
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
