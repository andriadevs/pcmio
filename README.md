# pcmio
### Single-header C/C++ library for using portable character map (.PCM) files. 

## Usage:
Put '#define PCMIO_IMPLEMENTATION' in one of the source files that include this library before the '#include "pcmio.h"' statement.

.PCM files are formatted into cells similarly to pixels or bits in a .PBM or .PPM file.

Each cell contains a u32 formatted character and a foreground and background color in RGBA32.

PCMFile instances can be created with pcmio_new() and modified/read with either the get/set functions or directly.

Use pcmio_write() to write PCMFile instances to file or pcmio_open() to read a .PCM file into a new PCMFile instance.

## Credits:
A. Hollingsworth (andriadevs)

## Changelog:
* n/a

## License:
See LICENSE or the end of file for pcmio.h
