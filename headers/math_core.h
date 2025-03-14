#ifndef MATH_CORE_H
#define MATH_CORE_H
#include <cmath.h>

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

#ifndef LERP
    #define LERP(a, b, t) ((a) + (t) * ((b) - (a)))
#endif

#ifndef RAD2DEG
    #define RAD2DEG(r) ((r) * 180.0 / M_PI)
#endif

#ifndef DEG2RAD
    #define DEG2RAD(d) ((d) * M_PI / 180.0)
#endif

#define CLAMP_INPLACE(val, minval, maxval) do {   \
    if ((val) < (minval)) (val) = (minval);       \
    else if ((val) > (maxval)) (val) = (maxval);  \
} while(0)

//-------------------------
// 1) Integer exponent functions
//    (Exact for integer exponents.)
//-------------------------

/**
 * @brief pow_i: integer base^exp with exponentiation by squaring. 
 *        returns 0 if exp<0 (or you can handle differently).
 */
static inline int pow_i(int base, int exp)
{
    if (exp < 0) return 0;    // or handle differently
    if (exp == 0) return 1;
    if (exp == 1) return base;

    int result = 1;
    int current = base;
    int e = exp;
    while (e > 0) {
        if (e & 1) {
            result *= current;
        }
        current *= current;
        e >>= 1;
    }
    return result;
}

/**
 * @brief pow_fi: float base, integer exponent. 
 *        Negative exponent => 1 / (base^-exp). 
 *        If base=0 and exp<0 => return INFINITY (div by zero).
 */
static inline float pow_fi(float base, int exp)
{
    if (exp < 0) {
        if (base == 0.0f) return INFINITY; // or handle error
        int ePos = -exp;
        float result = 1.0f;
        while (ePos-- > 0) result *= base;
        return 1.0f / result;
    } else {
        float result = 1.0f;
        while (exp-- > 0) {
            result *= base;
        }
        return result;
    }
}

/**
 * @brief pow_di: double base, integer exponent. 
 */
static inline double pow_di(double base, int exp)
{
    if (exp < 0) {
        if (base == 0.0) return INFINITY;
        int ePos = -exp;
        double result = 1.0;
        while (ePos-- > 0) result *= base;
        return 1.0 / result;
    } else {
        double result = 1.0;
        while (exp-- > 0) result *= base;
        return result;
    }
}

//-------------------------
// 2) Fast Inverse Sqrt & Sqrt
//    Quake-like approximations
//-------------------------

/**
 * @brief fast_inv_sqrt: approximate 1/sqrt(x) for x>0.
 *        Single iteration Newton–Raphson.
 */
static inline float fast_inv_sqrt(float x)
{
    if (x <= 0.0f) return NAN; // domain error or handle differently

    float xhalf = 0.5f * x;
    int i = *(int *)&x;            // reinterpret float bits as int
    i = 0x5f3759df - (i >> 1);     // initial guess
    x = *(float *)&i;
    // One iteration
    x = x * (1.5f - xhalf * x * x);
    // optional second iteration for better accuracy:
    // x = x * (1.5f - xhalf * x * x);
    return x;
}

/**
 * @brief fast_inv_sqrtd: approximate 1/sqrt(x) double version
 */
static inline double fast_inv_sqrtd(double x)
{
    if (x <= 0.0) return NAN;

    double xhalf = 0.5 * x;
    long long i = *(long long *)&x;  
    i = 0x5fe6ec85e7de30daLL - (i >> 1);
    x = *(double *)&i;
    x = x * (1.5 - xhalf * x * x);
    // optional second iteration
    // x = x * (1.5 - xhalf * x * x);
    return x;
}

static inline float fast_sqrt(float x)
{
    if (x < 0.0f) return NAN;
    return x * fast_inv_sqrt(x);
}

static inline double fast_sqrtd(double x)
{
    if (x < 0.0) return NAN;
    return x * fast_inv_sqrtd(x);
}

//-------------------------
// 3) Fast log2 & exp2
//-------------------------

/**
 * @brief fast_log2f: approximate log2(x). x>0
 */
static inline float fast_log2f(float x)
{
    if (x <= 0.0f) return -INFINITY; // or NAN
    union {
        float f;
        uint32_t i;
    } vx = { x };

    // exponent + mantissa approximation
    // (float)vx.i * 1.1920928955078125e-7f = i * (1 / 8388608.0f)
    float y = (float)vx.i * 1.1920928955078125e-7f;
    return y - 126.94269504f;
}

/**
 * @brief fast_log2d: approximate log2(x) for double
 */
static inline double fast_log2d(double x)
{
    if (x <= 0.0) return -INFINITY;
    union {
        double f;
        uint64_t i;
    } vx = { x };

    double y = (double)vx.i * 5.42101086242752217e-20; // 1/(2^64)
    return y - 1023.0;
}

/**
 * @brief fast_exp2f: approximate 2^p. 
 *        Clamps p to [0,255].
 */
static inline float fast_exp2f(float p)
{
    float t = p + 126.94269504f;
    CLAMP_INPLACE(t, 0.0f, 255.0f);
    union {
        uint32_t i;
        float f;
    } vt;
    vt.i = (uint32_t)(t * 8388608.0f); // 1<<23
    return vt.f;
}

/**
 * @brief fast_exp2d: approximate 2^p for double. 
 *        Clamps p to [0, 2047].
 */
static inline double fast_exp2d(double p)
{
    double t = p + 1023.0;
    if (t < 0.0) t = 0.0;
    else if (t > 2047.0) t = 2047.0;

    union {
        uint64_t i;
        double f;
    } vt;
    vt.i = (uint64_t)(t * 4503599627370496.0); // 1<<52
    return vt.f;
}

//-------------------------
// 4) Fast approximate x^y
//-------------------------

static inline float fast_powf(float x, float y)
{
    // domain checks
    if (x < 0.0f) {
        // negative base => return NAN if y not integer
        // or handle sign if you'd like
        return NAN;
    }
    if (x == 0.0f) {
        // 0^positive => 0, 0^0 => 1, 0^negative => Infinity
        if (y > 0.0f) return 0.0f;
        else if (y == 0.0f) return 1.0f;
        else return INFINITY;
    }
    return fast_exp2f(y * fast_log2f(x));
}

static inline double fast_powd(double x, double y)
{
    if (x < 0.0) {
        return NAN;
    }
    if (x == 0.0) {
        if (y > 0.0) return 0.0;
        else if (y == 0.0) return 1.0;
        else return INFINITY;
    }
    return fast_exp2d(y * fast_log2d(x));
}

//-------------------------
// 5) sqrt, cbrt, hypot using fast methods
//-------------------------

/**
 * @brief sqrt_f: alias for fast_sqrt (approx).
 *        Use standard sqrtf if you want a more accurate result.
 */
static inline float sqrt_f(float x) {
    return fast_sqrt(x);
}

/**
 * @brief sqrt_d: alias for fast_sqrtd
 */
static inline double sqrt_d(double x) {
    return fast_sqrtd(x);
}

/**
 * @brief cbrt_f: approximate cube root of x>0 using fast_powf
 *        For negative x, we can do sign handling if desired.
 */
static inline float cbrt_f(float x)
{
    if (x < 0.0f) {
        // cbrt of negative => -cbrt(|x|)
        return -fast_powf(-x, 1.0f / 3.0f);
    }
    return fast_powf(x, 1.0f / 3.0f);
}

/**
 * @brief cbrt_d: approximate cube root in double
 */
static inline double cbrt_d(double x)
{
    if (x < 0.0) {
        return -fast_powd(-x, 1.0 / 3.0);
    }
    return fast_powd(x, 1.0 / 3.0);
}

/**
 * @brief hypot_f: approximate sqrt(x^2 + y^2) using fast_sqrt
 *        For large x,y, you might want more stable approach (like standard hypotf).
 */
static inline float hypot_f(float x, float y)
{
    return fast_sqrt(x * x + y * y);
}

static inline double hypot_d(double x, double y)
{
    return fast_sqrtd(x * x + y * y);
}


#endif //MATH_CORE_H
