#ifndef __SAI_HANDLER_MUTEX_H
#define __SAI_HANDLER_MUTEX_H

#include "cmsis_os2.h"

osStatus_t Init_SAI_Mutex (void);
osStatus_t SAI_Mutex_Aquire(uint32_t timeout);
osStatus_t SAI_Mutex_Release();

#endif
