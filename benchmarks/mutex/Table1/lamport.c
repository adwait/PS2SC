/* This example is taken from the SV-COMP benchmarks
 */

// Adapted for the tool PSChecker 

#include <pthread.h>


int x, y;
int b1, b2;
int _cc_X;


void *t0()
{
  int ry1 = -1, ry2 = -1, ry3 = -1, ry4 = -1, rx = -1, rb2 = -1;
  while (1) {
    while (1)
    {
        b1 = 1;
        x = 1;
        ry1 = y;
        if (ry1 != 0)
        {
            b1 = 0;
            ry2 = y;
            while (ry2 != 0)
            {
                ry2 = y;
            };
            continue;
        }
        y = 1;
        rx = x;
        if (rx != 1)
        {
            b1 = 0;
            rb2 = b2;
            while (rb2 >= 1)
            {
                rb2 = b2;
            };
            ry3 = y;
            if (ry3 != 1)
            {
                ry4 = y;
                while (ry4 != 0)
                {
                    ry4 = y;
                };
                continue;
            }
        }
        break;
    }
    _cc_X = 0;
    rx = _cc_X;
    assert(rx <= 0);
    y = 0;
    b1 = 0;
  }
}

void *t1()
{
  int ry1 = -1, ry2 = -1, ry3 = -1, ry4 = -1, rx = -1, rb1 = -1;
  while (1) {
    while (1)
    {
        b2 = 1;
        x = 2;
        ry1 = y;
        if (ry1 != 0)
        {
            b2 = 0;
            ry2 = y;
            while (ry2 != 0)
            {
                ry2 = y;
            };
            continue;
        }
        y = 2;
        rx = x;
        if (rx != 2)
        {
            b2 = 0;
            rb1 = b1;
            while (rb1 >= 1)
            {
                rb1 = b1;
            };
            ry3 = y;
            if (ry3 != 2)
            {
                ry4 = y;
                while (ry4 != 0)
                {
                    ry4 = y;
                };
                continue;
            }
        }
        break;
    }
    _cc_X = 1;
    rx = _cc_X;
    assert(rx >= 1);
    y = 0;
    b2 = 0;
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
