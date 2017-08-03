#pragma once
#ifndef CATOOL_VERSION
#define CATOOL_VERSION

//#define CATOOL_ENABLE_WARNING
#define CATOOL_ENABLE_ERROR

#define CATOOL_ENABLE_CMATH
//#define CATOOL_ENABLE_BUILTIN_MATH

//#define CATOOL_ENABLE_SSE
//#define CATOOL_ENABLE_AVX

#define CATOOL_CACHE_SIZE 64
#define CATOOL_CACHE_BLOCK_SIZE 64

#define CATOOL_CORE_NUM 4
#define CATOOL_CORE_DIV_D0 2
#define CATOOL_CORE_DIV_D1 2

#define CATOOL_VERSION_MAX 1
#define CATOOL_VERSION_MIN 0
#define CATOOL_CURRENT_VERSION "0.2.1"

namespace catool
{
}

#endif // CATOOL_VERSION