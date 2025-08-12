#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

#include <string>

#define ASSERT(_e, ...) if (!(_e)) {fprintf(stderr, __VA_ARGS__);}
#define QSSERT(_e, ...) if (!(_e)) {fprintf(stderr, __VA_ARGS__); exit(1);}

// unsafe (it __does_not__ check if view is longer than prefix)
static int starts_with(const std::string &text, const std::string &prefix) {
    return text.compare(0, prefix.size(), prefix) == 0;
}

#endif // !__COMMON_H__