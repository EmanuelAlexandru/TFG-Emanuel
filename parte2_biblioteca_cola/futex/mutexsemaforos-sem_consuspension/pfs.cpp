#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <linux/futex.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <limits.h>
#include <stdint.h>
#include <inttypes.h>
#include <iostream>
#include "pfs.hpp"

mutex::mutex()
{
        interlock = 0;
 
}
mutex::~mutex()
{
}

void mutex::lock()
{
    if (print == 1) {
        fprintf(stderr, "%c\t", type);
        print = 0;
    }
    switch (type){
    case 's':
    {
    while (__atomic_test_and_set ( &interlock, __ATOMIC_SEQ_CST));  
    }
        break;

    case 'n':
    {
    while (__atomic_test_and_set ( &interlock, __ATOMIC_SEQ_CST)){
             syscall(__NR_futex, &interlock, FUTEX_WAIT, 1, NULL, 0, 0);
    }
    }
        break;

    case 'K':
    {
    int c = 0;

    __atomic_compare_exchange_n( &interlock, &c, 1, 0, __ATOMIC_SEQ_CST, __ATOMIC_SEQ_CST);

    if (c == 0) return; 

    if (c != 2) { 
        c = __atomic_exchange_n( &interlock, 2, __ATOMIC_SEQ_CST);
    }

    while (c != 0) { 
            if ( -1 == syscall(__NR_futex, &interlock, FUTEX_WAIT, 2, NULL, 0, 0)){
            }
            c = __atomic_exchange_n( &interlock, 2, __ATOMIC_SEQ_CST);
    }
    }
        break;
    default:
        {
            break;
        }
    }
    
}

void mutex::unlock()
{
    switch (type){
      case's':
    interlock = 0;
        break;
    case 'n':
    interlock = 0;
    
    syscall(__NR_futex, &interlock, FUTEX_WAKE, 1, NULL, 0, 0);

        break;
    case 'K':
  
    if (__atomic_fetch_sub( &interlock, 1, __ATOMIC_SEQ_CST) != 1) {

        interlock = 0;
    
        syscall(__NR_futex, (int *) &interlock, FUTEX_WAKE, 1, NULL, 0, 0);
    }

        break;
    default:
    break;


    }

}

void mutex::setMutexType(char &c)
{
    type = c;
}