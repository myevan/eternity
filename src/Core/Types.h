#pragma once

#include "Defines.h"

#include <string>

#include <stdint.h>

EL_NAMESPACE()

typedef int int_t;
typedef char char_t;
typedef uint8_t byte_t;
typedef int64_t msec_t;
typedef float sec_t;
typedef int handle_t;

typedef std::string str_t;

typedef union 
{
    int32_t num; 
    char_t  chars[4]; 
} fourcc_t;

EL_NAMESPACE_END()
