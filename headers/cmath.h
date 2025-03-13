#ifndef  C_MATH
#define  C_MATH

typedef unsigned char bool;

#ifndef NULL
    #define NULL ((void *)0)
#endif

#ifndef true
    #define true 1
#endif

#ifndef false
    #define false 0
#endif

#ifndef NUMARGS
    #define NUMARGS(...) (sizeof((int[]){__VA_ARGS__})/sizeof(int))
#endif

#ifndef MAX
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
    #define MIN(a, b) ((a) < (b) ? (a) : (b))
#endif

#ifndef ABS
    #define ABS(a) ((a) < 0 ? -(a) : (a))
#endif

#ifndef CLAMP
    #define CLAMP(a, b, c) (MAX(b, MIN(a, c)))
#endif

#endif // C_MATH
