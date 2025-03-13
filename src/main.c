#include <stdio.h>
#include <vec.h>

int main() {
    vector_t v = vector(1.0, 2.0, 3.0);
    dvector_t dv = dvector(1.0, 2.0, 3.0);

    printf("v = [%f, %f, %f]\n", v.data[0], v.data[1], v.data[2]);
    printf("dv = [%f, %f, %f]\n", dv.data[0], dv.data[1], dv.data[2]);

    vector_t v_copy = vec_copy(v);
    dvector_t dv_copy = dvec_copy(dv);

    printf("v_copy = [%f, %f, %f]\n", v_copy.data[0], v_copy.data[1], v_copy.data[2]);
    printf("dv_copy = [%f, %f, %f]\n", dv_copy.data[0], dv_copy.data[1], dv_copy.data[2]);

    vector_t v2 = vec_create(3);
    dvector_t dv2 = dvec_create(3);

    printf("Default vector v2 = [%f, %f, %f]\n", v2.data[0], v2.data[1], v2.data[2]);
    printf("Default dvector dv2 = [%f, %f, %f]\n", dv2.data[0], dv2.data[1], dv2.data[2]);

    free_vector(&v);
    free_dvector(&dv);
    free_vector(&v_copy);
    free_dvector(&dv_copy);
}
