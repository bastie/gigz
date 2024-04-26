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
