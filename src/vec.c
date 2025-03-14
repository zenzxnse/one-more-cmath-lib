#include <vec.h> 
#include <math_core.h>

const vector_t VEC_UNDEFINED = {0, NULL};
const dvector_t DVEC_UNDEFINED = {0, NULL};

/**
 * @brief Allocate a vector of given size (uninitialized data).
 */
vector_t vector_alloc(unsigned int size)
{
    vector_t v;
    v.size = size;
    v.data = (float*)malloc(size * sizeof(float));
    return v;
}

/**
 * @brief Free the vector memory, setting v->data = NULL.
 */
void vector_free(vector_t *v)
{
    if (v->data) {
        free(v->data);
        v->data = NULL;
    }
    // v->size is left as-is or set to 0 if you prefer
}

/**
 * @brief Create a vector of given size, initializing all elements to 0.0f.
 */
vector_t vector_create(unsigned int size)
{
    vector_t v = vector_alloc(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = 0.0f;
    }
    return v;
}

/**
 * @brief Create a vector from an existing float array (copies data).
 */
vector_t vector_from_array(unsigned int size, const float *src)
{
    vector_t v = vector_alloc(size);
    memcpy(v.data, src, size * sizeof(float));
    return v;
}

/**
 * @brief Return a copy of vector v (deep copy).
 */
vector_t vector_copy(const vector_t v)
{
    vector_t c = vector_alloc(v.size);
    memcpy(c.data, v.data, v.size * sizeof(float));
    return c;
}

/**
 * @brief Create a vector of given size, initializing each element to `value`.
 */
vector_t vector_default(unsigned int size, float value)
{
    vector_t v = vector_alloc(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = value;
    }
    return v;
}

/**
 * @brief Check if two vectors are equal (element-wise ==).
 *        Returns false if sizes differ or any element differs.
 */
bool vector_equals(const vector_t v1, const vector_t v2)
{
    if (v1.size != v2.size) return false;
    for (unsigned int i = 0; i < v1.size; i++) {
        if (v1.data[i] != v2.data[i]) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Add scalar to each element, returns a new vector.
 */
vector_t vector_scalar_add(const vector_t v, float scalar)
{
    vector_t r = vector_alloc(v.size);
    const float * __restrict src = v.data;
          float * __restrict dst = r.data;

    for (unsigned int i = 0; i < v.size; i++) {
        dst[i] = src[i] + scalar;
    }
    return r;
}

/**
 * @brief Add scalar to each element in place.
 */
void vector_scalar_add_inplace(vector_t *v, float scalar)
{
    float * __restrict dst = v->data;
    for (unsigned int i = 0; i < v->size; i++) {
        dst[i] += scalar;
    }
}

/**
 * @brief Subtract scalar from each element, returns a new vector.
 */
vector_t vector_scalar_sub(const vector_t v, float scalar)
{
    vector_t r = vector_alloc(v.size);
    const float * __restrict src = v.data;
          float * __restrict dst = r.data;
    for (unsigned int i = 0; i < v.size; i++) {
        dst[i] = src[i] - scalar;
    }
    return r;
}

/**
 * @brief Subtract scalar from each element in place.
 */
void vector_scalar_sub_inplace(vector_t *v, float scalar)
{
    float * __restrict dst = v->data;
    for (unsigned int i = 0; i < v->size; i++) {
        dst[i] -= scalar;
    }
}

/**
 * @brief Multiply each element by scalar, returns a new vector.
 */
vector_t vector_scalar_mul(const vector_t v, float scalar)
{
    vector_t r = vector_alloc(v.size);
    const float * __restrict src = v.data;
          float * __restrict dst = r.data;
    for (unsigned int i = 0; i < v.size; i++) {
        dst[i] = src[i] * scalar;
    }
    return r;
}

/**
 * @brief Multiply each element by scalar in place.
 */
void vector_scalar_mul_inplace(vector_t *v, float scalar)
{
    float * __restrict dst = v->data;
    for (unsigned int i = 0; i < v->size; i++) {
        dst[i] *= scalar;
    }
}

/**
 * @brief Divide each element by scalar, returns a new vector.
 */
vector_t vector_scalar_div(const vector_t v, float scalar)
{
    if (scalar == 0.0f) {
        return vector_default(v.size, INFINITY);
    }
    vector_t r = vector_alloc(v.size);
    const float * __restrict src = v.data;
          float * __restrict dst = r.data;
    for (unsigned int i = 0; i < v.size; i++) {
        dst[i] = src[i] / scalar;
    }
    return r;
}

/**
 * @brief Divide each element by scalar in place.
 */
void vector_scalar_div_inplace(vector_t *v, float scalar)
{
    if (scalar == 0.0f) {
        return;
    }
    float * __restrict dst = v->data;
    for (unsigned int i = 0; i < v->size; i++) {
        dst[i] /= scalar;
    }
}

/**
 * @brief Raise each element to a power, returns a new vector.
 */
vector_t vector_pow(const vector_t v, float power)
{
    vector_t r = vector_alloc(v.size);
    const float * __restrict src = v.data;
          float * __restrict dst = r.data;
    for (unsigned int i = 0; i < v.size; i++) {
        dst[i] = pow_fi(src[i], power);
    }
    return r;
}

/**
 * @brief In-place version of vector_pow
 */
void vector_pow_inplace(vector_t *v, float power)
{
    float * __restrict dst = v->data;
    for (unsigned int i = 0; i < v->size; i++) {
        dst[i] = pow_fi(dst[i], power);
    }
}

/**
 * @brief Element-wise addition of two vectors, returns new vector.
 */
vector_t vector_add(const vector_t v1, const vector_t v2)
{
    // For real production code, you might check size mismatch
    vector_t r = vector_alloc(v1.size);
    const float * __restrict src1 = v1.data;
    const float * __restrict src2 = v2.data;
          float * __restrict dst  = r.data;

    for (unsigned int i = 0; i < v1.size; i++) {
        dst[i] = src1[i] + src2[i];
    }
    return r;
}

/**
 * @brief In-place addition of v2 into v1.
 */
void vector_add_inplace(vector_t *v1, const vector_t v2)
{
    float * __restrict dst  = v1->data;
    const float * __restrict src2 = v2.data;
    // assume same size
    for (unsigned int i = 0; i < v1->size; i++) {
        dst[i] += src2[i];
    }
}

/**
 * @brief Element-wise subtraction of two vectors, returns new vector.
 */
vector_t vector_sub(const vector_t v1, const vector_t v2)
{
    vector_t r = vector_alloc(v1.size);
    const float * __restrict src1 = v1.data;
    const float * __restrict src2 = v2.data;
          float * __restrict dst  = r.data;

    for (unsigned int i = 0; i < v1.size; i++) {
        dst[i] = src1[i] - src2[i];
    }
    return r;
}

/**
 * @brief In-place subtraction of v2 from v1.
 */
void vector_sub_inplace(vector_t *v1, const vector_t v2)
{
    float * __restrict dst  = v1->data;
    const float * __restrict src2 = v2.data;
    for (unsigned int i = 0; i < v1->size; i++) {
        dst[i] -= src2[i];
    }
}

/**
 * @brief Element-wise multiply of two vectors, returns new vector.
 */
vector_t vector_mul(const vector_t v1, const vector_t v2)
{
    vector_t r = vector_alloc(v1.size);
    const float * __restrict src1 = v1.data;
    const float * __restrict src2 = v2.data;
          float * __restrict dst  = r.data;

    for (unsigned int i = 0; i < v1.size; i++) {
        dst[i] = src1[i] * src2[i];
    }
    return r;
}

/**
 * @brief In-place element-wise multiply.
 */
void vector_mul_inplace(vector_t *v1, const vector_t v2)
{
    float * __restrict dst  = v1->data;
    const float * __restrict src2 = v2.data;
    for (unsigned int i = 0; i < v1->size; i++) {
        dst[i] *= src2[i];
    }
}

/**
 * @brief Element-wise divide of v1 by v2, returns new vector.
 */
vector_t vector_div(const vector_t v1, const vector_t v2)
{
    vector_t r = vector_alloc(v1.size);
    const float * __restrict src1 = v1.data;
    const float * __restrict src2 = v2.data;
          float * __restrict dst  = r.data;
    for (unsigned int i = 0; i < v1.size; i++) {
        dst[i] = src1[i] / src2[i];
    }
    return r;
}

/**
 * @brief In-place element-wise divide.
 */
void vector_div_inplace(vector_t *v1, const vector_t v2)
{
    float * __restrict dst  = v1->data;
    const float * __restrict src2 = v2.data;
    for (unsigned int i = 0; i < v1->size; i++) {
        dst[i] /= src2[i];
    }
}

/**
 * @brief Dot product of two vectors.
 */
float vector_dot(const vector_t v1, const vector_t v2)
{
    float sum = 0.0f;
    const float * __restrict src1 = v1.data;
    const float * __restrict src2 = v2.data;
    for (unsigned int i = 0; i < v1.size; i++) {
        sum += src1[i] * src2[i];
    }
    return sum;
}

/**
 * @brief Cross product in 3D. Expects v1.size == 3 and v2.size == 3.
 */
vector_t vector_cross(const vector_t v1, const vector_t v2)
{
    // If size !=3 => out-of-bounds errors.
    vector_t r = vector_alloc(3);
    const float * __restrict a = v1.data;
    const float * __restrict b = v2.data;

    r.data[0] = a[1] * b[2] - a[2] * b[1];
    r.data[1] = a[2] * b[0] - a[0] * b[2];
    r.data[2] = a[0] * b[1] - a[1] * b[0];
    return r;
}

/** 
* @brief In future versions, we may want to add a vector_cross_R7 function
*/
vector_t vector_cross_R7(const vector_t v1, const vector_t v2)
{
    return VEC_UNDEFINED;    
}


/**
 * @brief Magnitude (Euclidean norm) of a vector.
 */
float vector_magnitude(const vector_t v)
{
    float sum = 0.0f;
    const float * __restrict src = v.data;
    for (unsigned int i = 0; i < v.size; i++) {
        sum += src[i] * src[i];
    }
    return sqrt_f(sum);
}

/**
 * @brief Print a vector to stdout.
 */
void print_vector(const char* label, vector_t v)
{
    printf("%s [", label);
    for (unsigned int i = 0; i < v.size; i++) {
        printf("%f", v.data[i]);
        if (i + 1 < v.size) printf(", ");
    }
    printf("]\n");
}


/****************************************************DVEC*****************************************************/

dvector_t allocate_d(unsigned int size) {
    dvector_t v = {size, (double *)malloc(size * sizeof(double))};
    return v;
}

void free_dvector(dvector_t *v) {
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
    }
}

dvector_t dvec_create(unsigned int size) {
    dvector_t v = allocate_d(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = 0.0;
    }
    return v;
}

dvector_t dvec_create_from_array(unsigned int size, double *data) {
    dvector_t v = allocate_d(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = data[i];
    }
    return v;
}

dvector_t dvec_copy(dvector_t v) {
    dvector_t copy = allocate_d(v.size);
    for (unsigned int i = 0; i < v.size; i++) {
        copy.data[i] = v.data[i];
    }
    return copy;
}

dvector_t dvec_default(unsigned int size, double value) {
    dvector_t v = allocate_d(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = value;
    }
    return v;
}
