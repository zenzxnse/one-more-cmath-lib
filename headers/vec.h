#ifndef VEC_H
#define VEC_H
#include <cmath.h>
#include <math_core.h>

/**
 * @brief A structure representing a mathematical vector of floating-point numbers
 * 
 * This structure contains an array of float values and its size. It can be used
 * to perform various vector operations and mathematical calculations.
 * 
 * @members
 *   size - The number of elements in the vector
 *   data - Pointer to the array containing the vector elements
**/
typedef struct {
    size_t size;
    float *data;  
} vector_t;

/*
 * @brief double precision vector
*/
typedef struct 
{
    unsigned int size;
    double *data;
} dvector_t;


extern const vector_t VEC_UNDEFINED;
extern const dvector_t DVEC_UNDEFINED;

vector_t vector_alloc(unsigned int size); // Allocate memory for a vector
void vector_free(vector_t *v); // Free memory allocated for a vector
vector_t vector_create(unsigned int size); // Create a new vector
vector_t vector_from_array(unsigned int size, const float *src); // Create a new vector from an array
vector_t vector_copy(vector_t v); // Create a copy of a vector
vector_t vector_default(unsigned int size, float value); // Create a new vector with a default value
bool vector_equals(vector_t v1, vector_t v2); // Check if two vectors are equal
vector_t vector_scalar_add(vector_t v, float scalar); // Add a scalar to a vector
void vector_scalar_add_inplace(vector_t *v, float scalar); // Add a scalar to a vector in place
vector_t vector_scalar_sub(vector_t v, float scalar); // Subtract a scalar from a vector
void vector_scalar_sub_inplace(vector_t *v, float scalar); // Subtract a scalar from a vector in place
vector_t vector_scalar_mul(vector_t v, float scalar); // Multiply a vector by a scalar
void vector_scalar_mul_inplace(vector_t *v, float scalar); // Multiply a vector by a scalar in place
vector_t vector_scalar_div(vector_t v, float scalar); // Divide a vector by a scalar
void vector_scalar_div_inplace(vector_t *v, float scalar); // Divide a vector by a scalar in place
vector_t vector_pow(vector_t v, float power); // Raise a vector to a power
void vector_pow_inplace(vector_t *v, float power); // Raise a vector to a power in place
vector_t vector_add(vector_t v1, vector_t v2); // Add two vectors
void vector_add_inplace(vector_t *v1, vector_t v2); // Add two vectors in place
vector_t vector_sub(vector_t v1, vector_t v2); // Subtract one vector from another
void vector_sub_inplace(vector_t *v1, vector_t v2); // Subtract one vector from another in place
vector_t vector_mul(vector_t v1, vector_t v2); // Multiply two vectors
void vector_mul_inplace(vector_t *v1, vector_t v2); // Multiply two vectors in place
vector_t vector_div(vector_t v1, vector_t v2); // Divide one vector by another
void vector_div_inplace(vector_t *v1, vector_t v2); // Divide one vector by another in place
float vector_dot(vector_t v1, vector_t v2); // Calculate the dot product of two vectors
vector_t vector_cross(vector_t v1, vector_t v2); // Calculate the cross product of two vectors
float vector_magnitude(vector_t v); // Calculate the magnitude of a vector
void print_vector(const char *label, vector_t v); // Print a vector to stdout


// TODO:
vector_t vec_normalize(vector_t v); // Normalize a vector
vector_t vec_abs(vector_t v); // Calculate the absolute value of a vector
float vec_distance(vector_t v1, vector_t v2); // Calculate the distance between two vectors
float vec_angle(vector_t v1, vector_t v2); // Calculate the angle between two vectors
vector_t vec_map(vector_t v, float (*func)(float)); // Apply a function to each element of a vector
void vec_map_to(vector_t *v, float (*func)(float)); // Apply a function to each element of a vector in place
vector_t vec_map2(vector_t v1, vector_t v2, float (*func)(float, float)); // Apply a function to corresponding elements of two vectors
void vec_map2_to(vector_t *v1, vector_t v2, float (*func)(float, float)); // Apply a function to corresponding elements of two vectors in place
vector_t vec_map_scalar(vector_t v, float scalar, float (*func)(float, float)); // Apply a function to each element of a vector and a scalar
void vec_map_scalar_to(vector_t *v, float scalar, float (*func)(float, float)); // Apply a function to each element of a vector and a scalar in place
vector_t vec_map3(vector_t v1, vector_t v2, vector_t v3, float (*func)(float, float, float)); // Apply a function to corresponding elements of three vectors
void vec_map3_to(vector_t *v1, vector_t v2, vector_t v3, float (*func)(float, float, float)); // Apply a function to corresponding elements of three vectors in place
vector_t vec_map4(vector_t v1, vector_t v2, vector_t v3, vector_t v4, float (*func)(float, float, float, float)); // Apply a function to corresponding elements of four vectors
void vec_map4_to(vector_t *v1, vector_t v2, vector_t v3, vector_t v4, float (*func)(float, float, float, float)); // Apply a function to corresponding elements of four vectors in place
vector_t vec_map5(vector_t v1, vector_t v2, vector_t v3, vector_t v4, vector_t v5, float (*func)(float, float, float, float, float)); // Apply a function to corresponding elements of five vectors
void vec_map5_to(vector_t *v1, vector_t v2, vector_t v3, vector_t v4, vector_t v5, float (*func)(float, float, float, float, float)); // Apply a function to corresponding elements of five vectors in place
vector_t orthogonalize(vector_t v1, vector_t v2); // Orthogonalize two vectors
vector_t project(vector_t v1, vector_t v2); // Project one vector onto another
vector_t reflect(vector_t v, vector_t normal); // Reflect a vector off a surface
vector_t refract(vector_t v, vector_t normal, float eta); // Refract a vector through a surface
vector_t vec_rotate(vector_t v, float angle, vector_t axis); // Rotate a vector around an axis
vector_t vec_rotate_x(vector_t v, float angle); // Rotate a vector around the x-axis
vector_t vec_rotate_y(vector_t v, float angle); // Rotate a vector around the y-axis
vector_t vec_rotate_z(vector_t v, float angle); // Rotate a vector around the z-axis
vector_t vec_rotate_axis(vector_t v, float angle, float x, float y, float z); // Rotate a vector around an arbitrary axis
vector_t vec_rotate_euler(vector_t v, float pitch, float yaw, float roll); // Rotate a vector using Euler angles
vector_t vec_rotate_quaternion(vector_t v, float x, float y, float z, float w); // Rotate a vector using a quaternion
vector_t vec_rotate_matrix(vector_t v, float *matrix); // Rotate a vector using a rotation matrix
vector_t vec_transform(vector_t v, float *matrix); // Transform a vector using a transformation matrix
vector_t vec_transform_normal(vector_t v, float *matrix); // Transform a vector as a normal using a transformation matrix
vector_t vec_transform_direction(vector_t v, float *matrix); // Transform a vector as a direction using a transformation matrix
vector_t vec_transform_position(vector_t v, float *matrix); // Transform a vector as a position using a transformation matrix
vector_t vec_transform_affine(vector_t v, float *matrix); // Transform a vector using an affine transformation matrix
vector_t vec_transform_affine_normal(vector_t v, float *matrix); // Transform a vector as a normal using an affine transformation matrix
vector_t vec_transform_affine_direction(vector_t v, float *matrix); // Transform a vector as a direction using an affine transformation matrix
vector_t vec_transform_affine_position(vector_t v, float *matrix); // Transform a vector as a position using an affine transformation matrix
vector_t vec_transform_inverse(vector_t v, float *matrix); // Transform a vector using the inverse of a transformation matrix
vector_t vec_transform_inverse_normal(vector_t v, float *matrix); // Transform a vector as a normal using the inverse of a transformation matrix
vector_t vec_transform_inverse_direction(vector_t v, float *matrix); // Transform a vector as a direction using the inverse of a transformation matrix
vector_t vec_transform_inverse_position(vector_t v, float *matrix); // Transform a vector as a position using the inverse of a transformation matrix
vector_t vec_transform_inverse_affine(vector_t v, float *matrix); // Transform a vector using the inverse of an affine transformation matrix
vector_t vec_transform_inverse_affine_normal(vector_t v, float *matrix); // Transform a vector as a normal using the inverse of an affine transformation matrix
vector_t vec_transform_inverse_affine_direction(vector_t v, float *matrix); // Transform a vector as a direction using the inverse of an affine transformation matrix
vector_t vec_transform_inverse_affine_position(vector_t v, float *matrix); // Transform a vector as a position using the inverse of an affine transformation matrix
vector_t vec_magnitude_squared(vector_t v); // Calculate the squared magnitude of a vector
vector_t vec_normalize_safe(vector_t v); // Normalize a vector safely
vector_t vec_abs_safe(vector_t v); // Calculate the absolute value of a vector safely
vector_t vec_map_safe(vector_t v, float (*func)(float)); // Apply a function to each element of a vector safely
vector_t vec_map2_safe(vector_t v1, vector_t v2, float (*func)(float, float)); // Apply a function to corresponding elements of two vectors safely
vector_t vec_map_scalar_safe(vector_t v, float scalar, float (*func)(float, float)); // Apply a function to each element of a vector and a scalar safely
vector_t vec_map3_safe(vector_t v1, vector_t v2, vector_t v3, float (*func)(float, float, float)); // Apply a function to corresponding elements of three vectors safely
vector_t vec_map4_safe(vector_t v1, vector_t v2, vector_t v3, vector_t v4, float (*func)(float, float, float, float)); // Apply a function to corresponding elements of four vectors safely
vector_t vec_map5_safe(vector_t v1, vector_t v2, vector_t v3, vector_t v4, vector_t v5, float (*func)(float, float, float, float, float)); // Apply a function to corresponding elements of five vectors safely
vector_t vec_rotate_safe(vector_t v, float angle, vector_t axis); // Rotate a vector around an axis safely
vector_t vec_rotate_x_safe(vector_t v, float angle); // Rotate a vector around the x-axis safely
vector_t vec_rotate_y_safe(vector_t v, float angle); // Rotate a vector around the y-axis safely
vector_t vec_rotate_z_safe(vector_t v, float angle); // Rotate a vector around the z-axis safely
vector_t vec_rotate_axis_safe(vector_t v, float angle, float x, float y, float z); // Rotate a vector around an arbitrary axis safely
vector_t vec_rotate_euler_safe(vector_t v, float pitch, float yaw, float roll); // Rotate a vector using Euler angles safely
vector_t vec_rotate_quaternion_safe(vector_t v, float x, float y, float z, float w); // Rotate a vector using a quaternion safely
vector_t vec_rotate_matrix_safe(vector_t v, float *matrix); // Rotate a vector using a rotation matrix safely
vector_t vec_transform_safe(vector_t v, float *matrix); // Transform a vector using a transformation matrix safely
vector_t vec_transform_normal_safe(vector_t v, float *matrix); // Transform a vector as a normal using a transformation matrix safely
vector_t vec_transform_direction_safe(vector_t v, float *matrix); // Transform a vector as a direction using a transformation matrix safely
vector_t vec_transform_position_safe(vector_t v, float *matrix); // Transform a vector as a position using a transformation matrix safely
vector_t vec_transform_affine_safe(vector_t v, float *matrix); // Transform a vector using an affine transformation matrix safely
vector_t vec_transform_affine_normal_safe(vector_t v, float *matrix); // Transform a vector as a normal using an affine transformation matrix safely
vector_t vec_transform_affine_direction_safe(vector_t v, float *matrix); // Transform a vector as a direction using an affine transformation matrix safely
vector_t vec_transform_affine_position_safe(vector_t v, float *matrix); // Transform a vector as a position using an affine transformation matrix safely
vector_t vec_transform_inverse_safe(vector_t v, float *matrix); // Transform a vector using the inverse of a transformation matrix safely
vector_t vec_transform_inverse_normal_safe(vector_t v, float *matrix); // Transform a vector as a normal using the inverse of a transformation matrix safely
vector_t vec_transform_inverse_direction_safe(vector_t v, float *matrix); // Transform a vector as a direction using the inverse of a transformation matrix safely
vector_t vec_transform_inverse_position_safe(vector_t v, float *matrix); // Transform a vector as a position using the inverse of a transformation matrix safely
vector_t vec_transform_inverse_affine_safe(vector_t v, float *matrix); // Transform a vector using the inverse of an affine transformation matrix safely
vector_t vec_transform_inverse_affine_normal_safe(vector_t v, float *matrix); // Transform a vector as a normal using the inverse of an affine transformation matrix safely
vector_t vec_transform_inverse_affine_direction_safe(vector_t v, float *matrix); // Transform a vector as a direction using the inverse of an affine transformation matrix safely
vector_t vec_transform_inverse_affine_position_safe(vector_t v, float *matrix); // Transform a vector as a position using the inverse of an affine transformation matrix safely



dvector_t allocate_d(unsigned int size); // Allocate memory for a double precision vector
void free_dvector(dvector_t *v); // Free memory allocated for a double precision vector
dvector_t dvec_create(unsigned int size); // Create a new double precision vector
dvector_t dvec_create_from_array(unsigned int size, double *data); // Create a new double precision vector from an array || macro exists
dvector_t dvec_copy(dvector_t v); // Create a copy of a double precision vector
dvector_t dvec_default(unsigned int size, double value); // Create a new double precision vector with a default value


#ifndef vector
    #define vector(...) vec_create_from_array(NUMARGS(__VA_ARGS__), (float[]){__VA_ARGS__})
#endif 

#ifndef dvector
    #define dvector(...) dvec_create_from_array(NUMARGS(__VA_ARGS__), (double[]){__VA_ARGS__})
#endif


#endif 
