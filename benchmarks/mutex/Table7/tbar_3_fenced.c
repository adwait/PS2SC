/* Inspiration from the SVCOMP-2018 benchmarks
 */

// Adapted for the tool PSChecker 

 

#include <pthread.h>
#define assert(e) if (!(e)) ERROR: goto ERROR;

int childnotready0_0 = 1, childnotready0_1 = 1;
int parentsense1 = 0, parentsense2 = 0;
int tdiff0 = 0, tdiff1 = 0, tdiff2 = 0;
int __fence_var;

void *t0()
{
    int rsense = 1;
    int rchildnotready0_0 = -1;
    int rchildnotready0_1 = -1;
    int rtdiff1 = -1;
    int rtdiff2 = -1;
    while (1)
    {
        tdiff0 = 1;
	sc_fence();
        rchildnotready0_0 = childnotready0_0;
        assume(rchildnotready0_0 ==0);
        rchildnotready0_1 = childnotready0_1;
        assume(rchildnotready0_1==0);
        childnotready0_0 = 1;
        childnotready0_1 = 1;
        sc_fence();
        parentsense1 = rsense;
        parentsense2 = rsense;
        rsense = 1 - rsense;
        sc_fence();
        rtdiff1 = tdiff1;
        rtdiff2 = tdiff2;
        assert(rtdiff1 != 0 && rtdiff2 != 0);
    }
}



void *t1()
{
    int rsense = 1;
    int rtdiff0 = -1;
    int rtdiff2 = -1;
    int rparentsense1 = -1;
    while (1)
    {
        tdiff1 = 1;
        sc_fence();
        childnotready0_0 = 0;
        sc_fence();
        rparentsense1 = parentsense1;
        assume(rparentsense1==rsense);
        rsense = 1 - rsense;
        sc_fence();
        rtdiff0 = tdiff0;
        rtdiff2 = tdiff2;
        assert(rtdiff0!=0 && rtdiff2 !=0);
    }
}

void *t2()
{
    int rsense = 1;
    int rtdiff0 = -1;
    int rtdiff1 = -1;
    int rparentsense2 = -1;
    while (1)
    {
        tdiff2 = 1;
        sc_fence();
        childnotready0_1 = 0;
        sc_fence();
        rparentsense2 = parentsense2;
        assume(rparentsense2==rsense);
        rsense = 1 - rsense;
        sc_fence();
        rtdiff0 = tdiff0;
        rtdiff1 = tdiff1;
        assert(rtdiff0!=0 && rtdiff1 !=0);
    }
}


int *propertyChecking(void* arg)
{
    return 0;
}

int main()
{
    childnotready0_0 = 1;
    childnotready0_1 = 1;
    pthread_t _cs_tdiff0, _cs_tdiff1, _cs_tdiff2;
    pthread_create(&_cs_tdiff0, 0, t0, 0);
    pthread_create(&_cs_tdiff1, 0, t1, 0);
    pthread_create(&_cs_tdiff2, 0, t2, 0);
    return 0;
}


