//
//  myIO.h
//
//  Created by Sebastian Ritter on 28.04.24.
//

#ifndef myIO_h
#define myIO_h

#include <stdio.h>
size_t readn(int desc, unsigned char *buf, size_t len);
static unsigned put(int out, ...);
#endif /* myIO_h */
