/* This example is taken from the SV-COMP benchmarks
 */

// Adapted for the tool PSChecker 

#include <pthread.h>


int flag1 = 0, flag2 = 0;
int turn;
int _cc_x;


void *t0()
{
    int rflag2 = -1, rturn_1 = -1, rturn_2 = -1, rx = -1;

    while (1) {
      flag1 = 1;
      rflag2 = flag2;
      while (rflag2 >= 1)
      {
        rturn_1 = turn;
        if (rturn_1 != 0)
        {
            flag1 = 0;
            rturn_2 = turn;
            assume(rturn_2 == 0);
            flag1 = 1;
        }
        rflag2 = flag2;
      }
      _cc_x = 0;
      rx = _cc_x;
      assert(rx<=0);
      turn = 1;
      flag1 = 0;
    }
}

void *t1()
{
    int rflag1 = -1, rturn_1 = -1, rturn_2 = -1, rx = -1;
    
    while (1) {
      flag2 = 1;
      rflag1 = flag1;
      while (rflag1 >= 1)
      {
        rturn_1 = turn;
        if (rturn_1 != 1)
        {
            flag2 = 0;
            rturn_2 = turn;
            assume(rturn_2 == 1);
            flag2 = 1;
        }
        rflag1 = flag1;
      }
      _cc_x = 1;
      rx = _cc_x;
      assert(rx>=1);
      turn = 0;
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


