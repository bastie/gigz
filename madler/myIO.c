//
//  myIO.c
//
//  Created by Sebastian Ritter on 28.04.24.
//

#include "myIO.h"
#include "unistd.h"
#include "try.h"
#include "errno.h"
#include "myCLI.h"


// Read up to len bytes into buf, repeating read() calls as needed.
size_t readn(int desc, unsigned char *buf, size_t len) {
  ssize_t ret;
  size_t got;
  
  got = 0;
  while (len) {
    ret = read(desc, buf, len);
    if (ret == 0) {
      break;
    }
    else if (ret < 0) {
      throw(errno, "read error on %s (%s)", g.inputFilename, strerror(errno));
    }
    buf += ret;
    len -= (size_t)ret;
    got += (size_t)ret;
  }
  return got;
}


