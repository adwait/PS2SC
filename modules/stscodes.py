def _helper_names(x): 
    # creates temporaries for PS translation
    return "_lazyps_" + x


def getLocalVarPrefix(_currThread):
    if 'pscopy' in _currThread:
        return '__cs_local_' + _currThread + '_'
    return "__cs_local_" + '_'.join(_currThread.split('_')[:1]) + "_"

def get_read_stats(var_name, index_var, _iscopy, _canProm, _currThread,  parentthread, access):

    nondet_int_var = getLocalVarPrefix(_currThread) + '_ps_non_det_int_var'
    # parentthread = '__cs_param_%s__ps_t1' % (_currThread)
    # var_num = self.get_index_var(var_name[0], var_name[1])

    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)    
    pstimevar = '%s_ps_time%s[%s]' % (var_name[0], var_name[1], nondet_int_var)

    op = ''
    op += '  __CPROVER_assume(%s < %s);\n' % (_helper_names("numEE"), _helper_names("rounds"))
    if _iscopy:
        op += ' __CPROVER_assume(%s_liveChain%s[0] == 0);\n' % (var_name[0], var_name[1])

    op += nondet_int_var + ' = nondet_int();\n'
    op += ' __CPROVER_assume(%s < %s);\n' % (nondet_int_var, _helper_names("index_used"))
    op += ' __CPROVER_assume(_ps_var[%s] == %s);\n' % (nondet_int_var, index_var) 
    op += ' __CPROVER_assume((%s < %s) || ((%s == %s) && %s));\n' % (timevar, pstimevar, timevar, pstimevar, lvar)
    if access == 'ra':
        if _iscopy:
            # TODO
            op += 'acquire_message_ra_copy_ps(%s, %s);\n' % (parentthread, nondet_int_var)
        else:
            # TODO
            op += 'acquire_message_ra_ps(%s, %s);\n' % (parentthread, nondet_int_var)
    elif access == 'rlx':
        op += ' %s = %s;\n' % (timevar, pstimevar)
        op += ' %s = 1;\n' % (lvar)
    else:
        print('Illegal access type in get_read_stats')
        exit(0)
    op += ' %s = %s_values%s[%s];\n' % (valvar, var_name[0], var_name[1], nondet_int_var)
    if _canProm:
        op += ' %s_extView%s[0] = 1;\n' % (var_name[0], var_name[1])

    # need to <review>
    op += "%s = %s + 1;\n" % (_helper_names("numEE"), _helper_names("numEE"))

    return op

'''
def get_publish_message_stats(var_arr, flag, access):
    
    var_num = self.get_index_var(var_arr[0], var_arr[1])
    threan_num = ''
    if 'pscopy' in self.__currentFunction:  
        thread_num = '__cs_param_%s__ps_t1' % (self.__currentFunction)
    else:
        thread_num = 'ps_thread_num'
    # static pre inlined translation
    s = '\n'
    if access == 'rlx':
        s += '  __CPROVER_assume(%s < %s);\n' % (self._helper_names('index_used'), self._helper_names('rounds'))
        s += "  _ps_time[%s] = %s_view_t%s[%s];\n" % (self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
        s += "  _ps_flag[%s] = %s;\n" % (self._helper_names('index_used'), flag)
        s += "  _ps_var[%s] = %s;\n"%(self._helper_names('index_used'), var_num)
        s += "  %s_values%s[%s] = %s_view%s[%s];\n" % (var_arr[0], var_arr[1], self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
        s += "  %s = %s + 1;\n" % (self._helper_names("index_used"), self._helper_names("index_used"))
    elif access == 'ra':
        s += '  __CPROVER_assume(%s < %s);\n' % (self._helper_names('index_used'), self._helper_names('rounds'))
        s += "  _ps_time[%s] = %s_view_t%s[%s];\n" % (self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
        s += "  _ps_flag[%s] = %s;\n" % (self._helper_names('index_used'), flag)
        s += "  _ps_var[%s] = %s;\n"%(self._helper_names('index_used'), var_num)
        s += "  %s_values%s[%s] = %s_view%s[%s];\n" % (var_arr[0], var_arr[1], self._helper_names('index_used'), var_arr[0], var_arr[1], thread_num)
        s += "  %s = %s + 1;\n" % (self._helper_names("index_used"), self._helper_names("index_used"))
    else:
        print('Illegal access type in get_publish_message_stats')
        exit(0)
        # s += "}\n"
    return s
'''

'''
def get_read_psfree(_currThread, var_name, register_var):

    parentthread = 'ps_thread_num'
    _iscopy = 'pscopy' in _currThread
    if _iscopy:
        parentthread = '__cs_param_%s__ps_t1' % (_currThread)
    
    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)
    
    nondet_int_var = getLocalVarPrefix() + '_ps_non_det_int_var'


    op = 'if(nondet_bool()){\n'
    op += get_read_stats(var_name, _iscopy, _currThread, parentthread) 
    op += '}\n'
    op += 'else{\n'
    op += '  __CPROVER_assume(%s_view_v%s[%s]);\n' % (var_name[0], var_name[1], parentthread)
    op += '}\n'
    op += '%s = %s_view_v%s[%s];\n' % (register_var, var_name[0], var_name[1], parentthread)
    
    return op
'''

def get_read(_currThread, var_name, index_var, register_var, access, _canProm):

    parentthread = 'ps_thread_num'
    _iscopy = 'pscopy' in _currThread
    if _iscopy:
        parentthread = '__cs_param_%s__ps_t1' % (_currThread)
    
    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)
    
    nondet_int_var = getLocalVarPrefix(_currThread) + '_ps_non_det_int_var'

    op = 'if(nondet_bool()){\n'
    op += get_read_stats(var_name, index_var, _iscopy, _canProm, _currThread, parentthread, access) 
    op += '}\n'
    op += 'else{\n'
    op += '  __CPROVER_assume(%s_view_v%s[%s]);\n' % (var_name[0], var_name[1], parentthread)
    op += '}\n'
    op += '%s = %s;\n' % (register_var, valvar)
    
    return op

def get_write_psfree(_currThread, var_name, index_var, register_var, access):
    
    parentthread = 'ps_thread_num'
    
    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)

    nondet_int_var = getLocalVarPrefix(_currThread) + '_ps_non_det_int_var'    
    pstimevar = '%s_ps_time%s[%s]' % (var_name[0], var_name[1], nondet_int_var)

    op = ''
    op += '%s = %s;\n' %(valvar, register_var)
    op += '%s_view_v%s[%s] = 1;\n' % (var_name[0], var_name[1], parentthread)
    op += 'if(nondet_bool()){\n'
    op += '    %s_view_l%s[ps_thread_num] = 1;\n' % (var_name[0], var_name[1])
    op += '    %s = nondet_uint();\n' % (nondet_int_var)
    op += '    __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
    op += '    __CPROVER_assume(%s > %s_view_t%s[ps_thread_num]);\n' % (nondet_int_var, var_name[0], var_name[1])
    op += '    %s = %s;\n' % (timevar, nondet_int_var)
    op += '    __CPROVER_assume(!%s_%s[%s]);\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
    op += '      %s_%s[%s] = 1;\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
    op += '      %s_%s[%s] = 1;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
    # <review>
    # op += '    if(%s_liveChain%s[0] == 0){\n' % (var_name[0], var_name[1])
    # defer to global scope function
    op += '     if(nondet_bool()){\n'
    op += '         __CPROVER_assume(%s < %s);\n' % (_helper_names('index_used'), _helper_names('rounds'))
    if access == 'rlx':
        op += "         %s_ps_time%s[%s] = %s_view_t%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
        op += "         %s_ps_timeL%s[%s] = %s_view_l%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
    elif access == 'ra':
        op += '         publish_stats_ra_ps(ps_thread_num);\n'
    else:
        print("Illegal access type in get_write_psfree")
    # op += '           publish_stats_rlx(ps_thread_num);\n'
    op += "         _ps_var[%s] = %s;\n"%(_helper_names('index_used'), index_var)
    op += "         %s_values%s[%s] = %s_view%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
    op += "         %s = %s + 1;\n" % (_helper_names("index_used"), _helper_names("index_used"))
    op += '     }\n'
    op += '}\n'
    op += 'else{\n'
    op += '  %s = 0;\n' % (lvar)
    op += '}\n'
    # op += '%s_view_u%s[ps_thread_num] = %s;\n' % (var_name[0], var_name[1], lvar)
    
    return op


def get_write_psfull(_currThread, var_name, index_var, register_var, access):
    parentthread = 'ps_thread_num'
    nondet_int_var = getLocalVarPrefix(_currThread) + '_ps_non_det_int_var'

    _iscopy = 'pscopy' in _currThread
    if _iscopy:
        parentthread = '__cs_param_%s__ps_t1' % (_currThread)
    
    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)
    pstimevar = '%s_ps_time%s[%s]' % (var_name[0], var_name[1], nondet_int_var)

    
    op = ''
    op += '%s = %s;\n' % (valvar, register_var)
    op += '%s_view_v%s[%s] = 1;\n' % (var_name[0], var_name[1], parentthread)
    op += 'if(nondet_int()){\n'
    op += '  %s = 0;\n' % (lvar)
    if _iscopy:
        if access == 'rlx':
            op += ' if(%s_liveChain%s[0] == 0){\n' % (var_name[0], var_name[1])
            op += '     %s = nondet_uint();\n' % (nondet_int_var)
            op += '     __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
            op += '     __CPROVER_assume(%s >= %s);\n' % (nondet_int_var, timevar)          
            op += '     %s = %s;\n' % (timevar, nondet_int_var)         
            # <review> : add leading?
            op += '     if(nondet_bool()){\n'
            op += '         %s_liveChain%s[0] = 1;\n' % (var_name[0], var_name[1])
            op += '     }\n'
            op += '     else{\n'
            op += '         if(%s_ps_reserve%s[%s] != %s){\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
            op += '             __CPROVER_assume(%s_%s[%s]);\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
            op += '             __CPROVER_assume(%s < %s);\n' % (_helper_names("numEE"), _helper_names("rounds"))
            op += '             %s = %s + 1;\n' % (_helper_names('numEE'), _helper_names('numEE'))
            op += '             %s_ps_reserve%s[%s] = %s;\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
            op += '             %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
            op += '         }\n'
            op += '         %s_%s[%s] = 1;\n' % (_helper_names("usedReservation"), var_name[2], nondet_int_var)
            op += '     }\n'
            op += ' }\n'
        if access == 'ra':
            op += ' %s_blockPromise%s[0] = 1;\n' % (var_name[0], var_name[1])
            op += ' __CPROVER_assume(%s_liveChain%s[0] == 0);\n' % (var_name[0], var_name[1])
            op += ' %s = nondet_uint();\n' % (nondet_int_var)
            op += ' __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
            op += ' __CPROVER_assume(%s >= %s);\n' % (nondet_int_var, timevar)          
            op += ' %s = %s;\n' % (timevar, nondet_int_var)

            op += ' if(%s_ps_reserve%s[%s] != %s){\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
            op += '     __CPROVER_assume(%s_%s[%s]);\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
            op += '     __CPROVER_assume(%s < %s);\n' % (_helper_names("numEE"), _helper_names("rounds"))
            op += '     %s = %s + 1;\n' % (_helper_names('numEE'), _helper_names('numEE'))
            op += '     %s_ps_reserve%s[%s] = %s;\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
            op += '     %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
            op += ' }\n'
            op += ' %s_%s[%s] = 1;\n' % (_helper_names("usedReservation"), var_name[2], nondet_int_var)
            # <review> add leading
    op += '}\n'

    if not _iscopy or access == 'rlx': 
            
        if access == 'ra':
            op += 'else{\n'
        else:
            op += 'else if(nondet_bool()){\n'       
        op += '    %s_view_l%s[%s] = 1;\n' % (var_name[0], var_name[1],parentthread)
        if _iscopy:
            op += ' if(%s_liveChain%s[0] == 1){\n' % (var_name[0], var_name[1])
            op += '     %s = %s + 1;\n' % (nondet_int_var, timevar)
            op += ' }\n'
            op += ' else{\n'
            op += '     %s = nondet_uint();\n' % (nondet_int_var)
            op += ' }\n'
        else:
            op += ' %s = nondet_uint();\n' % (nondet_int_var)
        op += '    __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
        op += '    __CPROVER_assume(%s > %s);\n' % (nondet_int_var, timevar)
        op += '    %s = %s;\n' % (timevar, nondet_int_var)
        op += '    __CPROVER_assume(!%s_%s[%s]);\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
        op += '      %s_%s[%s] = 1;\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
        op += '      %s_%s[%s] = 1;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
        if not _iscopy:
            op += '    if(nondet_bool()){\n'
        # defer to global scope function
        op += '         __CPROVER_assume(%s < %s);\n' % (_helper_names('index_used'), _helper_names('rounds'))
        if access == 'rlx':
            if _iscopy:
                op += ' __CPROVER_assume(!%s_blockPromise%s[0]);\n' % (var_name[0],  var_name[1])
                op += ' %s_liveChain%s[0] = 0;\n' % (var_name[0], var_name[1])
                op += '  __CPROVER_assume(%s < %s);\n' % (_helper_names("numEE"), _helper_names("rounds"))
                op += ' %s = %s + 1;\n' % (_helper_names('numEE'), _helper_names('numEE'))
                op += ' _ps_flag[%s] = 255;\n' % (nondet_int_var)
            else:
                op += ' _ps_flag[%s] = 0;\n' % (nondet_int_var)
            op += "         %s_ps_time%s[%s] = %s_view_t%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
            op += "         %s_ps_timeL%s[%s] = %s_view_l%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
        elif access == 'ra':
            op += '         publish_stats_ra_ps(ps_thread_num);\n'
        else:
            print("Illegal access type in get_write_psfull")
        # op += '           publish_stats_rlx(ps_thread_num);\n'
        op += "         _ps_var[%s] = %s;\n"%(_helper_names('index_used'), index_var)
        op += "         %s_values%s[%s] = %s_view%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
        op += "         %s = %s + 1;\n" % (_helper_names("index_used"), _helper_names("index_used"))
        if not _iscopy:
            op += "    }\n"
        op += '}\n'  

        if access == 'rlx':
            op += 'else{\n'
            if _iscopy:
                op += ' __CPROVER_assume(!%s_blockPromise%s[0]);\n' % (var_name[0],  var_name[1])
            op += ' %s_view_l%s[%s] = 1;\n' % (var_name[0], var_name[1],parentthread)
            op += ' %s = nondet_int();\n' % (nondet_int_var)
            op += ' __CPROVER_assume(%s < %s);\n' % (nondet_int_var, _helper_names("index_used"))
            op += ' __CPROVER_assume(_ps_var[%s] == %s);\n' % (nondet_int_var, index_var) 
            op += ' __CPROVER_assume(%s < %s);\n' % (timevar, pstimevar)
            op += ' __CPROVER_assume(_ps_flag[%s] == %s);\n' % (nondet_int_var, parentthread)
            op += ' __CPROVER_assume(%s_values%s[%s] == %s);\n' % (var_name[0], var_name[1], nondet_int_var, valvar)
            if _iscopy:
                op += ' _ps_flag[%s] = 255;\n' % (nondet_int_var)
                op += ' __CPROVER_assume((%s == %s + 1) || !%s_liveChain%s[0]);\n' % (pstimevar, timevar, var_name[0], var_name[1])
                op += ' %s_liveChain%s[0] = 0;\n' % (var_name[0], var_name[1])
            else:
                op += ' _ps_flag[%s] = 0;\n' % (nondet_int_var)

            op += '%s = %s;\n' % (timevar, pstimevar)
            op += '}\n'
    if _iscopy:
        op += ' %s_extView%s[0] = 0;\n' % (var_name[0], var_name[1])
    else:
        op += ' %s_extView%s[0] = 1;\n' % (var_name[0], var_name[1])
    # op += '%s_view_u%s[ps_thread_num] = 1;\n' % (var_name[0], var_name[1], lvar)

    return op

def get_cas_psfree(_currThread, var_name, index_var, register_var1, register_var2, access):
    parentthread = 'ps_thread_num'
    _iscopy = 'pscopy' in _currThread
    if _iscopy:
        parentthread = '__cs_param_%s__ps_t1' % (_currThread)
    
    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)
    
    nondet_int_var = getLocalVarPrefix(_currThread) + '_ps_non_det_int_var'
    pstimevar = '%s_ps_time%s[%s]' % (var_name[0], var_name[1], nondet_int_var)

    # read part
    op = 'if(nondet_bool()){\n'
    op += get_read_stats(var_name, index_var, _iscopy, False, _currThread, parentthread, access) 
    op += '}\n'
    op += 'else{\n'
    op += '  __CPROVER_assume(%s_view_v%s[%s]);\n' % (var_name[0], var_name[1], parentthread)
    op += '}\n'
    op += '__CPROVER_assume(%s == %s);\n' % (register_var1, valvar)
    
    # update part
    op += 'if(%s){\n' % lvar
    op += ' __CPROVER_assume(%s_%s[%s]);\n' % (_helper_names('upd'), var_name[2], timevar)
    op += ' %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], timevar)
    op += '}\n'
    op += '%s = %s;\n' % (valvar, register_var2);

    # write part
    op += '%s_view_v%s[%s] = 1;\n' % (var_name[0], var_name[1], parentthread)
    op += 'if(nondet_bool()){\n'
    op += '    %s_view_l%s[ps_thread_num] = 1;\n' % (var_name[0], var_name[1])
    op += '    %s = %s + 1;\n' % (nondet_int_var,  timevar)
    op += '    __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
    # op += '    __CPROVER_assume(%s > %s_view_t%s[ps_thread_num]);\n' % (nondet_int_var, var_name[0], var_name[1])
    op += '    %s = %s;\n' % (timevar, nondet_int_var)
    op += '    __CPROVER_assume(!%s_%s[%s]);\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
    op += '      %s_%s[%s] = 1;\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
    op += '      %s_%s[%s] = 1;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
    # <review>
    # op += '    if(%s_liveChain%s[0] == 0){\n' % (var_name[0], var_name[1])
    # defer to global scope function
    op += ' if(nondet_bool()){\n'
    op += '     __CPROVER_assume(%s < %s);\n' % (_helper_names('index_used'), _helper_names('rounds'))
    if access == 'rlx':
        op += "         %s_ps_time%s[%s] = %s_view_t%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
        op += "         %s_ps_timeL%s[%s] = %s_view_l%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
    # elif access == 'ra':
    #     op += '         publish_stats_ra_ps(ps_thread_num);\n'
    else:
        print("Illegal access type in get_cas_psfree")
    # op += '           publish_stats_rlx(ps_thread_num);\n'
    op += "         _ps_var[%s] = %s;\n" % (_helper_names('index_used'), index_var)
    op += "         %s_values%s[%s] = %s;\n" % (var_name[0], var_name[1], _helper_names('index_used'), valvar)
    op += "         %s = %s + 1;\n" % (_helper_names("index_used"), _helper_names("index_used"))
    op += ' }\n'
    op += '}\n'
    op += 'else{\n'
    op += ' %s = 0;\n' % (lvar)
    op += '}\n'
    
    return op
    # op += '%s_view_u%s[ps_thread_num] = 1;\n' % (var_name[0], var_name[1], lvar)
                
def get_cas_psfull(_currThread, var_name, index_var, register_var1, register_var2, access):
    parentthread = 'ps_thread_num'
    _iscopy = 'pscopy' in _currThread
    if _iscopy:
        parentthread = '__cs_param_%s__ps_t1' % (_currThread)
    
    timevar = '%s_view_t%s[%s]' % (var_name[0], var_name[1], parentthread)
    lvar = '%s_view_l%s[%s]' % (var_name[0], var_name[1], parentthread)
    valvar = '%s_view%s[%s]' % (var_name[0], var_name[1], parentthread)
    
    nondet_int_var = getLocalVarPrefix(_currThread) + '_ps_non_det_int_var'
    pstimevar = '%s_ps_time%s[%s]' % (var_name[0], var_name[1], nondet_int_var)

    # read part
    op = 'if(nondet_bool()){\n'
    op += get_read_stats(var_name, index_var, _iscopy, True, _currThread, parentthread, access) 
    op += '}\n'
    op += 'else{\n'
    op += '  __CPROVER_assume(%s_view_v%s[%s]);\n' % (var_name[0], var_name[1], parentthread)
    op += '}\n'
    op += '__CPROVER_assume(%s == %s);\n' % (register_var1, valvar)
    
    # update part
    op += '%s = %s;\n' % (valvar, register_var2);

    # write part
    op += '%s_view_v%s[%s] = 1;\n' % (var_name[0], var_name[1], parentthread)
    op += 'if(nondet_int()){\n'
    if _iscopy:
        if access == 'rlx':
            op += ' if(%s_liveChain%s[0] == 0){\n' % (var_name[0], var_name[1])
            op += '     %s = %s;\n' % (nondet_int_var, timevar)
            # op += '     __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
            # op += '     __CPROVER_assume(%s >= %s);\n' % (nondet_int_var, timevar)          
            # op += '     %s = %s;\n' % (timevar, nondet_int_var)         
            # <review> : add leading?
            op += '     if(nondet_bool()){\n'
            op += '         __CPROVER_assume(%s_extView%s[0] == 0);\n' % (var_name[0], var_name[1])
            # op += '         %s_liveChain%s[0] = 1;\n' % (var_name[0], var_name[1])
            op += '         if(%s){\n' % lvar
            op += '             __CPROVER_assume(%s_%s[%s]);\n' % (_helper_names('upd'), var_name[2], timevar)
            op += '             %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], timevar)
            op += '         }\n'
            op += '     }\n'
            op += '     else{\n'
            op += '         __CPROVER_assume(%s);\n' % (lvar)
            op += '         if(%s_ps_reserve%s[%s] != %s){\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
            op += '             __CPROVER_assume(%s_%s[%s]);\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
            op += '             __CPROVER_assume(%s < %s);\n' % (_helper_names("numEE"), _helper_names("rounds"))
            op += '             __CPROVER_assume(%s_ps_reserve%s[%s] == 0);\n' % (var_name[0], var_name[1], nondet_int_var)
            op += '             %s = %s + 1;\n' % (_helper_names('numEE'), _helper_names('numEE'))
            op += '             %s_ps_reserve%s[%s] = %s;\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
            op += '             %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
            op += '         }\n'
            op += '         %s_%s[%s] = 1;\n' % (_helper_names("usedReservation"), var_name[2], nondet_int_var)
            op += '     }\n'
            op += ' }\n'
        # if access == 'ra':
        #     op += ' %s_blockPromise%s[0] = 1;\n' % (var_name[0], var_name[1])
        #     op += ' __CPROVER_assume(%s_liveChain%s[0] == 0);\n' % (var_name[0], var_name[1])
        #     op += ' %s = nondet_uint();\n' % (nondet_int_var)
        #     op += ' __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
        #     op += ' __CPROVER_assume(%s >= %s);\n' % (nondet_int_var, timevar)          
        #     op += ' %s = %s;\n' % (timevar, nondet_int_var)

        #     op += ' __CPROVER_assume(%s_%s[%s] || %s_ps_reserve%s[%s] == %s){\n' % (_helper_names('upd'), var_name[2], nondet_int_var, var_name[0], var_name[1], nondet_int_var, parentthread)
        #     op += ' %s_ps_reserve%s[%s] = %s;\n' % (var_name[0], var_name[1], nondet_int_var, parentthread)
        #     op += ' %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
        #     op += ' %s_%s[%s] = 1;\n' % (_helper_names("usedReservation"), var_name[2], nondet_int_var)
            # <review> add leading
    op += '  %s = 0;\n' % (lvar)
    op += '}\n'

    if not _iscopy or access == 'rlx': 
            
        if access == 'ra':
            op += 'else{\n'
        else:
            op += 'else if(nondet_bool()){\n'       
        op += '     if(%s){\n' % lvar
        op += '         __CPROVER_assume(%s_%s[%s]);\n' % (_helper_names('upd'), var_name[2], timevar)
        op += '         %s_%s[%s] = 0;\n' % (_helper_names('upd'), var_name[2], timevar)
        op += '     }\n'
        op += '     %s_view_l%s[%s] = 1;\n' % (var_name[0], var_name[1],parentthread)
        # if _iscopy:
            # op += ' if(%s_liveChain%s[0] == 1){\n' % (var_name[0], var_name[1])
        op += '     %s = %s + 1;\n' % (nondet_int_var, timevar)
            # op += ' }\n'
            # op += ' else{\n'
            # op += '     %s = nondet_uint();\n' % (nondet_int_var)
            # op += ' }\n'
        # else:
        #     op += ' %s = nondet_uint();\n' % (nondet_int_var)
        op += '    __CPROVER_assume(%s <= %s);\n' % (nondet_int_var, _helper_names('rounds'))
        # op += '    __CPROVER_assume(%s > %s);\n' % (nondet_int_var, timevar)
        op += '    %s = %s;\n' % (timevar, nondet_int_var)
        op += '    __CPROVER_assume(!%s_%s[%s]);\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
        op += '      %s_%s[%s] = 1;\n' % (_helper_names('unavail'), var_name[2], nondet_int_var)
        op += '      %s_%s[%s] = 1;\n' % (_helper_names('upd'), var_name[2], nondet_int_var)
        if not _iscopy:
            op += '    if(nondet_bool()){\n'
        # defer to global scope function
        op += '         __CPROVER_assume(%s < %s);\n' % (_helper_names('index_used'), _helper_names('rounds'))
        if access == 'rlx':
            if _iscopy:
                op += ' __CPROVER_assume(!%s_blockPromise%s[0]);\n' % (var_name[0],  var_name[1])
                op += ' %s_liveChain%s[0] = 0;\n' % (var_name[0], var_name[1])
                op += '  __CPROVER_assume(%s < %s);\n' % (_helper_names("numEE"), _helper_names("rounds"))
                op += ' %s = %s + 1;\n' % (_helper_names('numEE'), _helper_names('numEE'))
                op += ' _ps_flag[%s] = 255;\n' % (nondet_int_var)
            else:
                op += ' _ps_flag[%s] = 0;\n' % (nondet_int_var)
            op += "         %s_ps_time%s[%s] = %s_view_t%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
            op += "         %s_ps_timeL%s[%s] = %s_view_l%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
        # elif access == 'ra':
        #     op += '         publish_stats_ra_ps(ps_thread_num);\n'
        else:
            print("Illegal access type in get_cas_psfull")
        # op += '           publish_stats_rlx(ps_thread_num);\n'
        op += "         _ps_var[%s] = %s;\n"%(_helper_names('index_used'), index_var)
        op += "         %s_values%s[%s] = %s_view%s[%s];\n" % (var_name[0], var_name[1], _helper_names('index_used'), var_name[0], var_name[1], parentthread)
        op += "         %s = %s + 1;\n" % (_helper_names("index_used"), _helper_names("index_used"))
        if not _iscopy:
            op += "    }\n"
        op += '}\n'  

        if access == 'rlx':
            op += 'else{\n'
            if _iscopy:
                op += ' __CPROVER_assume(!%s_blockPromise%s[0]);\n' % (var_name[0],  var_name[1])
            op += ' %s_view_l%s[%s] = 1;\n' % (var_name[0], var_name[1],parentthread)
            op += ' %s = nondet_int();\n' % (nondet_int_var)
            op += ' __CPROVER_assume(%s < %s);\n' % (nondet_int_var, _helper_names("index_used"))
            op += ' __CPROVER_assume(_ps_var[%s] == %s);\n' % (nondet_int_var, index_var) 
            op += ' __CPROVER_assume(%s < %s);\n' % (timevar, pstimevar)
            op += ' __CPROVER_assume(_ps_flag[%s] == %s);\n' % (nondet_int_var, parentthread)
            op += ' __CPROVER_assume(%s_values%s[%s] == %s);\n' % (var_name[0], var_name[1], nondet_int_var, valvar)
            if _iscopy:
                op += ' _ps_flag[%s] = 255;\n' % (nondet_int_var)
                op += ' __CPROVER_assume((%s == %s + 1) || !%s_liveChain%s[0]);\n' % (pstimevar, timevar, var_name[0], var_name[1])
                op += ' %s_liveChain%s[0] = 0;\n' % (var_name[0], var_name[1])
            else:
                op += ' _ps_flag[%s] = 0;\n' % (nondet_int_var)

            op += '%s = %s;\n' % (timevar, pstimevar)
            op += '}\n'
    if _iscopy:
        op += ' %s_extView%s[0] = 0;\n' % (var_name[0], var_name[1])
    else:
        op += ' %s_extView%s[0] = 1;\n' % (var_name[0], var_name[1])
    # op += '%s_view_u%s[ps_thread_num] = %s;\n' % (var_name[0], var_name[1], lvar)

    return op