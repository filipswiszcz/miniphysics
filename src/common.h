#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

#define ASSERT(_e, ...) if (!(_e)) {fprintf(stderr, __VA_ARGS__);}
#define QSSERT(_e, ...) if (!(_e)) {fprintf(stderr, __VA_ARGS__); exit(1);}

#endif // !__COMMON_H__
