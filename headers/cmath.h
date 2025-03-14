#ifndef  C_MATH
#define  C_MATH


#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
// #include <math.h>

#ifndef NULL
    #define NULL ((void *)0)
#endif

#ifndef true
    #define true 1
#endif

#ifndef false
    #define false 0
#endif

#ifndef INFINITY
    #define INFINITY (1.0/0.0)
#endif //INFINITY

#ifndef NAN
    #define NAN (0.0/0.0)
#endif //NAN

#ifndef FLT_MAX
    #define FLT_MAX 3.402823466e+38
#endif //FLT_MAX

#ifndef NUMARGS
    #define NUMARGS(...) (sizeof((float[]){__VA_ARGS__})/sizeof(int))
#endif

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned long long uint64_t;

#endif // C_MATH
