#ifndef __CACHE_H__
#define __CACGE_H__

#include "common.h"

uint32_t L1cache_read(hwaddr_t, size_t);
void L1cache_write(hwaddr_t, size_t, uint32_t);
#endif
