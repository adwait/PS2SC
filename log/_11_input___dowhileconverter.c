typedef int _____STARTSTRIPPINGFROMHERE_____;
typedef int __cs_barrier_t;
typedef int __cs_barrierattr_t;
typedef int __cs_attr_t;
typedef int __cs_cond_t;
typedef int __cs_condattr_t;
typedef int __cs_key_t;
typedef int __cs_mutex_t;
typedef int __cs_mutexattr_t;
typedef int __cs_once_t;
typedef int __cs_rwlock_t;
typedef int __cs_rwlockattr_t;
typedef int __cs_t;
typedef int size_t;
typedef int __builtin_va_list;
typedef int __gnuc_va_list;
typedef int __int8_t;
typedef int __uint8_t;
typedef int __int16_t;
typedef int __uint16_t;
typedef int __int_least16_t;
typedef int __uint_least16_t;
typedef int __int32_t;
typedef int __uint32_t;
typedef int __int64_t;
typedef int __uint64_t;
typedef int __int_least32_t;
typedef int __uint_least32_t;
typedef int __s8;
typedef int __u8;
typedef int __s16;
typedef int __u16;
typedef int __s32;
typedef int __u32;
typedef int __s64;
typedef int __u64;
typedef int _LOCK_T;
typedef int _LOCK_RECURSIVE_T;
typedef int _off_t;
typedef int __dev_t;
typedef int __uid_t;
typedef int __gid_t;
typedef int _off64_t;
typedef int _fpos_t;
typedef int _ssize_t;
typedef int wint_t;
typedef int _mbstate_t;
typedef int _flock_t;
typedef int _iconv_t;
typedef int __ULong;
typedef int __FILE;
typedef int ptrdiff_t;
typedef int wchar_t;
typedef int __off_t;
typedef int __pid_t;
typedef int __loff_t;
typedef int u_char;
typedef int u_short;
typedef int u_int;
typedef int u_long;
typedef int ushort;
typedef int uint;
typedef int clock_t;
typedef int time_t;
typedef int daddr_t;
typedef int caddr_t;
typedef int ino_t;
typedef int off_t;
typedef int dev_t;
typedef int uid_t;
typedef int gid_t;
typedef int pid_t;
typedef int key_t;
typedef int ssize_t;
typedef int mode_t;
typedef int nlink_t;
typedef int fd_mask;
typedef int _types_fd_set;
typedef int fd_set;
typedef int clockid_t;
typedef int timer_t;
typedef int useconds_t;
typedef int suseconds_t;
typedef int FILE;
typedef int fpos_t;
typedef int cookie_read_function_t;
typedef int cookie_write_function_t;
typedef int cookie_seek_function_t;
typedef int cookie_close_function_t;
typedef int cookie_io_functions_t;
typedef int div_t;
typedef int ldiv_t;
typedef int lldiv_t;
typedef int sigset_t;
typedef int __sigset_t;
typedef int _sig_func_ptr;
typedef int sig_atomic_t;
typedef int __tzrule_type;
typedef int __tzinfo_type;
typedef int mbstate_t;
typedef int sem_t;
typedef int pthread_t;
typedef int pthread_attr_t;
typedef int pthread_mutex_t;
typedef int pthread_mutexattr_t;
typedef int pthread_cond_t;
typedef int pthread_condattr_t;
typedef int pthread_key_t;
typedef int pthread_once_t;
typedef int pthread_rwlock_t;
typedef int pthread_rwlockattr_t;
typedef int pthread_spinlock_t;
typedef int pthread_barrier_t;
typedef int pthread_barrierattr_t;
typedef int jmp_buf;
typedef int rlim_t;
typedef int sa_family_t;
typedef int sigjmp_buf;
typedef int stack_t;
typedef int siginfo_t;
typedef int z_stream;
typedef int int8_t;
typedef int uint8_t;
typedef int int16_t;
typedef int uint16_t;
typedef int int32_t;
typedef int uint32_t;
typedef int int64_t;
typedef int uint64_t;
typedef int int_least8_t;
typedef int uint_least8_t;
typedef int int_least16_t;
typedef int uint_least16_t;
typedef int int_least32_t;
typedef int uint_least32_t;
typedef int int_least64_t;
typedef int uint_least64_t;
typedef int int_fast8_t;
typedef int uint_fast8_t;
typedef int int_fast16_t;
typedef int uint_fast16_t;
typedef int int_fast32_t;
typedef int uint_fast32_t;
typedef int int_fast64_t;
typedef int uint_fast64_t;
typedef int intptr_t;
typedef int uintptr_t;
typedef int intmax_t;
typedef int uintmax_t;
typedef _Bool bool;
typedef void BZFILE;
typedef int va_list;
typedef int loff_t;
typedef int _____STOPSTRIPPINGFROMHERE_____;
int var0;
int z1;
int casvar;
int fib1;
int fib2;
static int __cs_pscopy_t2__x;
static int __cs_pscopy_t2__y;
static int __cs_pscopy_t2__s;
static int __cs_pscopy_t3__x;
static int __cs_pscopy_t3__y;
static int __cs_pscopy_t3__s;
static int __cs_pscopy_t0___lv;
static int __cs_pscopy_t0__n;
static int __cs_pscopy_t1___lv;
void *t0(void *__cs_unused)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
static int __lv;
static int _n;
int _int_update_helper_var;
{
static int __lv;
__lv = 0;
static int _n;
_n = __CSEQ_nondet_int();
if(nondet_bool()){
      if(_lazyps_active[ps_thread_num] == 0){
          __CSEQ_atomic_begin();
          _lazyps_active[ps_thread_num] = 1;
      }
      _lazyps_retAddr[ps_thread_num] = 0;
      savestate_ps();
__cs_pscopy_t0___lv = __lv;
__cs_pscopy_t0__n = _n;
      t0_pscopy(ps_thread_num);
      conscheck_ps();
      loadstate_ps();
      _lazyps_active[ps_thread_num] = 0;
      __CSEQ_atomic_end();
}
if(_lazyps_active[ps_thread_num] == 0){
  __CSEQ_atomic_begin();
  _lazyps_active[ps_thread_num] = 1;
}
rlx_read_ps(z1, __lv);
if (__lv == 1)
        {
__CSEQ_assert(0);
        }
        else
        {
if(nondet_bool()){
      if(_lazyps_active[ps_thread_num] == 0){
          __CSEQ_atomic_begin();
          _lazyps_active[ps_thread_num] = 1;
      }
      _lazyps_retAddr[ps_thread_num] = 1;
      savestate_ps();
__cs_pscopy_t0___lv = __lv;
__cs_pscopy_t0__n = _n;
      t0_pscopy(ps_thread_num);
      conscheck_ps();
      loadstate_ps();
      _lazyps_active[ps_thread_num] = 0;
      __CSEQ_atomic_end();
}
if(_lazyps_active[ps_thread_num] == 0){
  __CSEQ_atomic_begin();
  _lazyps_active[ps_thread_num] = 1;
}
rlx_read_ps(fib1, _n);
if(nondet_bool()){
      if(_lazyps_active[ps_thread_num] == 0){
          __CSEQ_atomic_begin();
          _lazyps_active[ps_thread_num] = 1;
      }
      _lazyps_retAddr[ps_thread_num] = 2;
      savestate_ps();
__cs_pscopy_t0___lv = __lv;
__cs_pscopy_t0__n = _n;
      t0_pscopy(ps_thread_num);
      conscheck_ps();
      loadstate_ps();
      _lazyps_active[ps_thread_num] = 0;
      __CSEQ_atomic_end();
}
if(_lazyps_active[ps_thread_num] == 0){
  __CSEQ_atomic_begin();
  _lazyps_active[ps_thread_num] = 1;
}
rlx_write_ps(var0, _n);
        }
if(_lazyps_active[ps_thread_num] == 1){
  conscheck_ps();
  _lazyps_active[ps_thread_num] = 0;
  __CSEQ_atomic_end();
}
__exit_t0:
        ;
__cs_exit(0);
}
}
void t0_pscopy(int _ps_t1)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
static int __lv;
__lv = __cs_pscopy_t0___lv;
static int _n;
_n = __cs_pscopy_t0__n;
int _int_update_helper_var;
if(_lazyps_retAddr[_ps_t1] < 0){
}
else if(_lazyps_retAddr[_ps_t1] == 0){
  goto t0_pscopy_pslabel_0;
}
else if(_lazyps_retAddr[_ps_t1] == 1){
  goto t0_pscopy_pslabel_1;
}
else if(_lazyps_retAddr[_ps_t1] == 2){
  goto t0_pscopy_pslabel_2;
}
{
static int __lv;
__lv = 0;
static int _n;
_n = __CSEQ_nondet_int();
t0_pscopy_pslabel_0: ;
if(nondet_bool()){
  goto __exit_t0;
}
rlx_read_ps(z1, __lv);
if (__lv == 1)
        {
__CSEQ_assert(0);
        }
        else
        {
t0_pscopy_pslabel_1: ;
if(nondet_bool()){
  goto __exit_t0;
}
rlx_read_ps(fib1, _n);
t0_pscopy_pslabel_2: ;
if(nondet_bool()){
  goto __exit_t0;
}
rlx_write_ps(var0, _n);
        }
__exit_t0:
        ;
return;
        ;
}
}
void *t1(void *__cs_unused)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
int _int_update_helper_var;
  __CSEQ_atomic_begin();
{
static int __lv;
__lv = __CSEQ_nondet_int();
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(var0, __lv);
__CSEQ_assume(__lv == 8);
rlx_write_ps(z1, 1);
      __CSEQ_atomic_end();
__exit_t1:
        ;
__cs_exit(0);
}
}
void t1_pscopy(int _ps_t1)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
static int __lv;
__lv = __cs_pscopy_t1___lv;
int _int_update_helper_var;
{
static int __lv;
__lv = __CSEQ_nondet_int();
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(var0, __lv);
__CSEQ_assume(__lv == 8);
rlx_write_ps(z1, 1);
      __CSEQ_atomic_end();
__exit_t1:
        ;
return;
        ;
}
}
void *t2(void *__cs_unused)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
int _int_update_helper_var;
  __CSEQ_atomic_begin();
{
static int _x;
_x = __CSEQ_nondet_int();
static int _y;
_y = __CSEQ_nondet_int();
static int _s;
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib1, _s);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib1, _s);
      __CSEQ_atomic_end();
__exit_t2:
        ;
__cs_exit(0);
}
}
void t2_pscopy(int _ps_t1)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
static int _x;
_x = __cs_pscopy_t2__x;
static int _y;
_y = __cs_pscopy_t2__y;
static int _s;
_s = __cs_pscopy_t2__s;
int _int_update_helper_var;
{
static int _x;
_x = __CSEQ_nondet_int();
static int _y;
_y = __CSEQ_nondet_int();
static int _s;
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib1, _s);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib1, _s);
      __CSEQ_atomic_end();
__exit_t2:
        ;
return;
        ;
}
}
void *t3(void *__cs_unused)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
int _int_update_helper_var;
  __CSEQ_atomic_begin();
{
static int _x;
_x = __CSEQ_nondet_int();
static int _y;
_y = __CSEQ_nondet_int();
static int _s;
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib2, _s);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib2, _s);
      __CSEQ_atomic_end();
__exit_t3:
        ;
__cs_exit(0);
}
}
void t3_pscopy(int _ps_t1)
{
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
static int _x;
_x = __cs_pscopy_t3__x;
static int _y;
_y = __cs_pscopy_t3__y;
static int _s;
_s = __cs_pscopy_t3__s;
int _int_update_helper_var;
{
static int _x;
_x = __CSEQ_nondet_int();
static int _y;
_y = __CSEQ_nondet_int();
static int _s;
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib2, _s);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib1, _x);
      __CSEQ_atomic_end();
  __CSEQ_atomic_begin();
rlx_read_ps(fib2, _y);
_s = _x + _y;
rlx_write_ps(fib2, _s);
      __CSEQ_atomic_end();
__exit_t3:
        ;
return;
        ;
}
}
int main()
{
unsigned int helper_temporary = 1;
_lazyps_unavail_var0[0] = 1;
_lazyps_upd_var0[0] = 1;
_lazyps_unavail_z1[0] = 1;
_lazyps_upd_z1[0] = 1;
_lazyps_unavail_casvar[0] = 1;
_lazyps_upd_casvar[0] = 1;
_lazyps_unavail_fib1[0] = 1;
_lazyps_upd_fib1[0] = 1;
_lazyps_unavail_fib2[0] = 1;
_lazyps_upd_fib2[0] = 1;
var0_view_l[0] = 1;
var0_view_u[0] = 1;
var0_liveChain[0] = 0;
var0_extView[0] = 1;
var0_blockPromise[0] = 0;
var0_view_v[0] = 1;
z1_view_l[0] = 1;
z1_view_u[0] = 1;
z1_liveChain[0] = 0;
z1_extView[0] = 1;
z1_blockPromise[0] = 0;
z1_view_v[0] = 1;
casvar_view_l[0] = 1;
casvar_view_u[0] = 1;
casvar_liveChain[0] = 0;
casvar_extView[0] = 1;
casvar_blockPromise[0] = 0;
casvar_view_v[0] = 1;
fib1_view_l[0] = 1;
fib1_view_u[0] = 1;
fib1_liveChain[0] = 0;
fib1_extView[0] = 1;
fib1_blockPromise[0] = 0;
fib1_view_v[0] = 1;
fib2_view_l[0] = 1;
fib2_view_u[0] = 1;
fib2_liveChain[0] = 0;
fib2_extView[0] = 1;
fib2_blockPromise[0] = 0;
fib2_view_v[0] = 1;
static unsigned int _ps_non_det_int_var;
static _Bool _ps_non_det_bool_var;
int _int_update_helper_var;
{
static __cs_t thr0;
        ;
static __cs_t thr1;
        ;
static __cs_t thr2;
        ;
static __cs_t thr3;
        ;
var0_view[ps_thread_num] = 0;
z1_view[ps_thread_num] = 0;
fib1_view[ps_thread_num] = 1;
fib2_view[ps_thread_num] = 1;
__cs_create(&thr2, 0, t2, 0);
__cs_create(&thr3, 0, t3, 0);
__cs_create(&thr0, 0, t0, 0);
__cs_create(&thr1, 0, t1, 0);
goto __exit_main;
__exit_main:
        ;
__cs_exit(0);
}
}
