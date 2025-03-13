#ifndef VEC_H
#define VEC_H
#include <cmath.h>

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
    unsigned int size;
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


const vector_t VEC_UNDEFINED = {0, NULL};
const dvector_t DVEC_UNDEFINED = {0, NULL};

vector_t allocate(unsigned int size); // Allocate memory for a vector
void free_vector(vector_t *v); // Free memory allocated for a vector
vector_t vec_create(unsigned int size); // Create a new vector
vector_t vec_create_from_array(unsigned int size, float *data); // Create a new vector from an array
vector_t vec_copy(vector_t v); // Create a copy of a vector
vector_t make_default_vector(); // Create a default vector

dvector_t allocate_d(unsigned int size); // Allocate memory for a double precision vector
void free_dvector(dvector_t *v); // Free memory allocated for a double precision vector
dvector_t dvec_create(unsigned int size); // Create a new double precision vector
dvector_t dvec_create_from_array(unsigned int size, double *data); // Create a new double precision vector from an array || macro exists
dvector_t dvec_copy(dvector_t v); // Create a copy of a double precision vector
dvector_t make_default_dvector(); // Create a default double precision vector


#ifndef vector
    #define vector(...) vec_create_from_array(NUMARGS(__VA_ARGS__), (float[]){__VA_ARGS__})
#endif 

#ifndef dvector
    #define dvector(...) dvec_create_from_array(NUMARGS(__VA_ARGS__), (double[]){__VA_ARGS__})
#endif


#endif 
