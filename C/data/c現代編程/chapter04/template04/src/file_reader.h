#ifndef _FILE_READER_H_
#define _FILE_READER_H_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

int read_file(const char *pFname, int (*processor)(FILE *fp));

#ifdef __cplusplus
}
#endif

#endif
