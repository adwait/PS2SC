/* Inspiration from the SVCOMP-2018 benchmarks
 */

// Adapted for the tool PSChecker 

 #include <pthread.h>
#define assert(e) if (!(e)) ERROR: goto ERROR;

int flag1 = 0, flag2 = 0;
int turn;
int _cc_x;

int __fence_var;
void *t0()
{
    int rflag2 = -1, rturn = -1, rx = -1;
    while(1){
    flag1 = 1;
    sc_fence();
    turn = 1;
    sc_fence();
    rflag2 = flag2;
    rturn = turn;
    sc_fence();
    assume(rflag2!=1 || rturn!=1);
    _cc_x = 0;
    rx = _cc_x;
    assert(rx<=0);
    sc_fence();
    flag1 = 0;
}
}

void *t1()
{
    int rflag1 = -1, rturn = -1, rx = -1;
    while(1){
    flag2 = 1;
    sc_fence();
    turn = 0;
    sc_fence();
    rflag1 = flag1;
    rturn = turn;
    sc_fence();
    assume(rflag1!=1 || rturn!=0);
    _cc_x = 1;
    rx = _cc_x;
    assert(rx>=1);
    sc_fence();
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
