//
//  mySystem.h
//
//  Created by Sebastian Ritter on 19.04.24.
//

#ifndef mySystem_h
#define mySystem_h


#define _DARWIN_C_SOURCE
#include <sys/sysctl.h> //

int getMaxNumbersOfThreads(void);
unsigned long time2dos(time_t t);

#endif /* mySystem_h */
