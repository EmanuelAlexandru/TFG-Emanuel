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

extern "C" unsigned int mi_fetch_and_add(unsigned int *x, int add);
extern "C" void mi_mutex_lock(int *x);
extern "C" void mi_mutex_unlock(int *x);

mutex::mutex()
{ 
}
mutex::~mutex()
{
}

void mutex::lock()
{
    mi_mutex_lock(&mi_mutex);
}

void mutex::unlock()
{
    mi_mutex_unlock(&mi_mutex);
}

void mutex::setMutexType(char &c)
{
    type = c;
}