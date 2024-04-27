//
//  myCLI.h
//  madler
//
//  Created by Sebastian Ritter on 20.04.24.
//

#ifndef myCLI_h
#define myCLI_h

#include <stdio.h>
#include <stdlib.h>
#include "zopfli/src/zopfli/zopfli.h"
#include "yarn.h"

#include <time.h>       // ctime(), time(), time_t, mktime()

// Input buffer size, and augmentation for re-inserting a central header.
#define BUF 32768
#define CEN 42
#define EXT (BUF + CEN)     // provide enough room to unget a header

typedef uintmax_t length_t;
typedef uint32_t crc_t;


// Globals (modified by main thread only when it's the only thread).
static struct {
  int ret;                // pigz return code
  char *prog;             // name by which pigz was invoked
  int ind;                // input file descriptor
  int outd;               // output file descriptor
  char *inf;              // input file name (allocated)
  size_t inz;             // input file name allocated size
  char *outf;             // output file name (allocated)
  int verbosity;          // 0 = quiet, 1 = normal, 2 = verbose, 3 = trace
  int headis;             // 1 to store name, 2 to store date, 3 both
  int pipeout;            // write output to stdout even if file
  int keep;               // true to prevent deletion of input file
  int force;              // true to overwrite, compress links, cat
  int sync;               // true to flush output file
  int form;               // gzip = 0, zlib = 1, zip = 2 or 3
  int magic1;             // first byte of possible header when decoding
  int recurse;            // true to dive down into directory structure
  char *sufx;             // suffix to use (".gz" or user supplied)
  char *name;             // name for gzip or zip header
  char *alias;            // name for zip header when input is stdin
  char *comment;          // comment for gzip or zip header.
  time_t mtime;           // time stamp from input file for gzip header
  int list;               // true to list files instead of compress
  int first;              // true if we need to print listing header
  int decode;             // 0 to compress, 1 to decompress, 2 to test
  int level;              // compression level
  int strategy;           // compression strategy
  ZopfliOptions zopts;    // zopfli compression options
  int rsync;              // true for rsync blocking
  int maxNumbersOfThreads;// maximum number of compression threads (>= 1)
  int setdict;            // true to initialize dictionary in each thread
  size_t block;           // uncompressed input size per thread (>= 32K)
  crc_t shift;            // pre-calculated CRC-32 shift for length block
  
  // saved gzip/zip header data for decompression, testing, and listing
  time_t stamp;           // time stamp from gzip header
  char *hname;            // name from header (allocated)
  char *hcomm;            // comment from header (allocated)
  unsigned long zip_crc;  // local header crc
  length_t zip_clen;      // local header compressed length
  length_t zip_ulen;      // local header uncompressed length
  int zip64;              // true if has zip64 extended information
  
  // globals for decompression and listing buffered reading
  unsigned char in_buf[EXT];  // input buffer
  unsigned char *in_next; // next unused byte in buffer
  size_t in_left;         // number of unused bytes in buffer
  int in_eof;             // true if reached end of file on input
  int in_short;           // true if last read didn't fill buffer
  length_t in_tot;        // total bytes read from input
  length_t out_tot;       // total bytes written to output
  unsigned long out_check;    // check value of output
  
  // globals for decompression parallel reading
  unsigned char in_buf2[EXT]; // second buffer for parallel reads
  size_t in_len;          // data waiting in next buffer
  int in_which;           // -1: start, 0: in_buf2, 1: in_buf
  lock *load_state;       // value = 0 to wait, 1 to read a buffer
  thread *load_thread;    // load_read() thread for joining
} g;


enum Verbosity {
  QUIET = 0,
  NORMAL = 1,
  VERBOSE = 2,
  TRACE = 3
};

void displayHelpOnCommandLine(enum Verbosity value);

static char *helptext[] = {
  "Usage: gigz [options] [files ...]",
  "  will compress files in place, adding the suffix '.gz'. If no files are",
  "  specified, stdin will be compressed to stdout. gigz does what gzip does,",
  "  but spreads the work over multiple processors and cores when compressing.",
  "",
  "Options:",
  "  -0 to -9, -11        Compression level (level 11, zopfli, is much slower)",
  "  --fast, --best       Compression levels 1 and 9 respectively",
  "  -A, --alias xxx      Use xxx as the name for any --zip entry from stdin",
  "  -b, --blocksize mmm  Set compression block size to mmmK (default 128K)",
  "  -c, --stdout         Write all processed output to stdout (won't delete)",
  "  -C, --comment ccc    Put comment ccc in the gzip or zip header",
  "  -d, --decompress     Decompress the compressed input",
  "  -f, --force          Force overwrite, compress .gz, links, and to terminal",
  "  -F  --first          Do iterations first, before block split for -11",
  "  -h, --help           Display a help screen and quit",
  "  -H, --huffman        Use only Huffman coding for compression",
  "  -i, --independent    Compress blocks independently for damage recovery",
  "  -I, --iterations n   Number of iterations for -11 optimization",
  "  -J, --maxsplits n    Maximum number of split blocks for -11",
  "  -k, --keep           Do not delete original file after processing",
  "  -K, --zip            Compress to PKWare zip (.zip) single entry format",
  "  -l, --list           List the contents of the compressed input",
  "  -L, --license        Display the gigz license and quit",
  "  -m, --no-time        Do not store or restore mod time",
  "  -M, --time           Store or restore mod time",
  "  -n, --no-name        Do not store or restore file name or mod time",
  "  -N, --name           Store or restore file name and mod time",
  "  -O  --oneblock       Do not split into smaller blocks for -11",
  "  -p, --processes n    Allow up to n compression threads (default is the",
  "                       number of online processors, or 8 if unknown)",
  "  -q, --quiet          Print no messages, even on error",
  "  -r, --recursive      Process the contents of all subdirectories",
  "  -R, --rsyncable      Input-determined block locations for rsync",
  "  -S, --suffix .sss    Use suffix .sss instead of .gz (for compression)",
  "  -t, --test           Test the integrity of the compressed input",
  "  -U, --rle            Use run-length encoding for compression",
  "  -v, --verbose        Provide more verbose output",
  "  -V  --version        Show the version of gigz",
  "  -Y  --synchronous    Force output file write to permanent storage",
  "  -z, --zlib           Compress to zlib (.zz) instead of gzip format",
  "  --                   All arguments after \"--\" are treated as files"
};

#endif /* myCLI_h */
