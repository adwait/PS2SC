/* Inspiration from the SVCOMP-2018 benchmarks
 */

// Adapted for the tool PSChecker 

 

#include <pthread.h>


int childnotready = 1;
int parentsense = 0;
int tdiff0 = 0, tdiff1 = 0;
int __fence_var;

void *t0()
{
    int rsense = 1;
    int rchildnotready = -1;
    int rtdiff1 = -1;
    while (1)
    {
        tdiff0 = 1;
        sc_fence();
        rchildnotready = childnotready;
        assume(rchildnotready==0);
        childnotready = 1;
        parentsense = rsense;
        rsense = 1 - rsense;
        sc_fence();
        rtdiff1 = tdiff1;
        assert(rtdiff1!=0);
    }
}



void *t1()
{
    int rsense = 1;
    int rtdiff0 = -1;
    int rparentsense = -1;
    while (1)
    {
        tdiff1 = 1;
        sc_fence();
        childnotready = 0;
        sc_fence();
        rparentsense = parentsense;
        assume(rparentsense==rsense);
        rsense = 1 - rsense;
        sc_fence();
        rtdiff0 = tdiff0;
        assert(rtdiff0!=0);
    }
}

int *propertyChecking(void* arg)
{
    return 0;
}

int main()
{
    childnotready =1;
    pthread_t _cs_tdiff0, _cs_tdiff1;
    pthread_create(&_cs_tdiff0, 0, t0, 0);
    pthread_create(&_cs_tdiff1, 0, t1, 0);
    return 0;
}


