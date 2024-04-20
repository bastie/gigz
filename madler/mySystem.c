//
//  mySystem.c
//
//  Created by Sebastian Ritter on 19.04.24.
//

#include "mySystem.h"

// Try to determine the number of processors.
int getMaxNumbersOfThreads(void) {
  int processorCount = 1;
  int64_t ret = 0;
  size_t size = sizeof(ret);
  
  if (sysctlbyname("hw.logicalcpu_max", &ret, &size, NULL, 0) == -1) {
#  ifdef _SC_NPROCESSORS_ONLN
    processorCount = (int)sysconf(_SC_NPROCESSORS_ONLN);
#  else
#    ifdef _SC_NPROC_ONLN
    processorCount = (int)sysconf(_SC_NPROC_ONLN);
#    endif
#  endif
  }
  else {
    processorCount = (int) ret;
  }
  
  return processorCount;
}
