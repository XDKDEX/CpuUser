#include <stdio.h>
#include <windows.h>
#include <fileapi.h>

__int64 _CompareFileTime(FILETIME time1, FILETIME time2){
    __int64 a = time1.dwHighDateTime << 32 | time1.dwLowDateTime;
    __int64 b = time2.dwHighDateTime << 32 | time2.dwLowDateTime;
    return (a - b);
}

int main(){
    //获取上一次的数据:空闲.核心.用户时间
    FILETIME pre_idle_time;
    FILETIME pre_kernel_time;
    FILETIME pre_user_time;
    //获取空闲.核心.用户时间
    FILETIME idle_time;
    FILETIME kernel_time;
    FILETIME user_time;
    GetSystemTimes(&pre_idle_time, &pre_kernel_time, &pre_user_time);
    Sleep(1000);
    GetSystemTimes(&idle_time, &kernel_time, &user_time);
    __int64 idle = _CompareFileTime(idle_time, pre_idle_time);
    __int64 kernel = _CompareFileTime(kernel_time, pre_kernel_time);
    __int64 user = _CompareFileTime(user_time, pre_user_time);
    // printf("%d\n%d\n%d\n",idle,kernel,user); -debug
    printf("%f", ((kernel + user - idle) / (1.0 * (kernel + user))));
    return main();
}
