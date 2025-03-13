#include <vec.h> 

const vector_t VEC_UNDEFINED = {0, NULL};
const dvector_t DVEC_UNDEFINED = {0, NULL};

vector_t allocate(unsigned int size) {
    vector_t v = {size, (float *)malloc(size * sizeof(float))};
    return v;
}

void free_vector(vector_t *v) {
    if (v->data != NULL) {
        free(v->data);
        v->data = NULL;
    }
}

vector_t vec_create(unsigned int size) {
    vector_t v = allocate(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = 0.0f;
    }
    return v;
}

vector_t vec_create_from_array(unsigned int size, float *data) {
    vector_t v = allocate(size);
    for (unsigned int i = 0; i < size; i++) {
        v.data[i] = data[i];
    }
    return v;
}

vector_t vec_copy(vector_t v) {
    vector_t copy = allocate(v.size);
    for (unsigned int i = 0; i < v.size; i++) {
        copy.data[i] = v.data[i];
    }
    return copy;
}

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
