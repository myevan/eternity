#pragma once

#include "Defines.h"

#include <string>
#include <memory>

#include <stdint.h>

#define EL_STRING_FOURCC_NUM(s) ((int)(((s[3])<<24) | ((s[2])<<16) | ((s[1])<<8) | (s[0])))

EL_NAMESPACE()

typedef int int_t;
typedef char char_t;
typedef uint8_t byte_t;
typedef int64_t msec_t;
typedef float sec_t;

typedef std::string str_t;

typedef union
{
    int num;
    char chars[4];
} fcc_t;

EL_NAMESPACE_END()

