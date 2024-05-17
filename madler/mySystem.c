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




// Convert Unix time to MS-DOS date and time, assuming the current timezone.
// (You got a better idea?)
unsigned long time2dos(time_t t) {
  struct tm *tm;
  unsigned long dos;
  
  if (t == 0)
    t = time(NULL);
  tm = localtime(&t);
  if (tm->tm_year < 80 || tm->tm_year > 207)
    return 0;
  dos = (unsigned long)(tm->tm_year - 80) << 25;
  dos += (unsigned long)(tm->tm_mon + 1) << 21;
  dos += (unsigned long)tm->tm_mday << 16;
  dos += (unsigned long)tm->tm_hour << 11;
  dos += (unsigned long)tm->tm_min << 5;
  dos += (unsigned long)(tm->tm_sec + 1) >> 1;    // round to even seconds
  return dos;
}

