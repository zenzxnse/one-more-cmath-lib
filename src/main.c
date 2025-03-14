#include <math.h>        // for printf, M_PI, etc.
#include "vec.h"         
#include "math_core.h"   


int main(void)
{
    printf("=== Testing vector functions ===\n");

    // Create vectors
    vector_t v1 = vector_create(3);         // [0, 0, 0]
    vector_t v2 = vector_default(3, 2.0f);  // [2, 2, 2]
    float arr[3] = { 1.0f, 2.0f, 3.0f };
    vector_t v3 = vector_from_array(3, arr); // [1, 2, 3]

    // Print them
    print_vector("v1", v1);
    print_vector("v2", v2);
    print_vector("v3", v3);

    // element-wise ops
    vector_t v4 = vector_add(v2, v3);       // [2+1, 2+2, 2+3] = [3, 4, 5]
    print_vector("v2 + v3 = ", v4);
    vector_free(&v4);

    // In-place addition
    vector_add_inplace(&v1, v3);           // v1 = v1 + v3 => [1, 2, 3]
    print_vector("v1 after add_inplace(v3)", v1);

    vector_t v5 = vector_mul(v1, v2);      // [1*2, 2*2, 3*2] = [2, 4, 6]
    print_vector("v1 * v2 = ", v5);
    vector_free(&v5);

    // In-place scalar
    vector_scalar_add_inplace(&v1, 10.0f); // v1 = [1+10, 2+10, 3+10] => [11,12,13]
    print_vector("v1 after scalar_add_inplace(10)", v1);

    vector_t v6 = vector_sub(v1, v3);      // [11-1, 12-2, 13-3] => [10,10,10]
    print_vector("v1 - v3 = ", v6);
    vector_free(&v6);

    // Cross, dot, magnitude
    // cross of v3 and v2 => cross([1,2,3],[2,2,2])
    vector_t crossRes = vector_cross(v3, v2); 
    // cross([1,2,3],[2,2,2]) = [2*2 - 3*2, 3*2 - 1*2, 1*2 - 2*2] 
    //                        = [4 - 6, 6 - 2, 2 - 4] = [-2, 4, -2]
    print_vector("cross(v3,v2)", crossRes);
    vector_free(&crossRes);

    float dotVal = vector_dot(v3, v2); // 1*2 + 2*2 + 3*2 = 2+4+6=12
    printf("dot(v3, v2) = %f\n", dotVal);

    float magv3 = vector_magnitude(v3); // sqrt(1^2+2^2+3^2)= sqrt(14)=3.741657...
    printf("magnitude(v3) = %f\n", magv3);

    // Copy, pow
    vector_t vcopy = vector_copy(v3);   // same as v3
    vector_t vpow = vector_pow(vcopy, 2.0f); // element-wise v3^2 => [1,4,9]
    print_vector("v3^2 =", vpow);

    // cleanup
    vector_free(&vcopy);
    vector_free(&vpow);

    // integer exponent
    int base_i = 2, exp_i = 5;
    int pi = pow_i(base_i, exp_i);    // 2^5=32
    printf("pow_i(%d, %d) = %d\n", base_i, exp_i, pi);

    float pf1 = pow_fi(2.0f, 3);      // 2^3=8
    printf("pow_fi(2,3) = %f\n", pf1);

    // fast_sqrt, fast_pow
    float fs = fast_sqrt(9.0f);       // approximate sqrt(9)=3
    printf("fast_sqrt(9) = %f\n", fs);

    float fp = fast_powf(2.0f, 3.0f); // approximate 2^3=8
    printf("fast_powf(2,3) = %f\n", fp);

    // cbrt, hypot
    float cbrtVal = cbrt_f(27.0f);    // approximate cbrt(27)=3
    printf("cbrt_f(27) = %f\n", cbrtVal);

    float hVal = hypot_f(3.0f,4.0f);  // approximate sqrt(3^2+4^2)=5
    printf("hypot_f(3,4) = %f\n", hVal);

    vector_free(&v1);
    vector_free(&v2);
    vector_free(&v3);

    // Done
    printf("=== All tests completed ===\n");
    return 0;
}
