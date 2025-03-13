#include <stdio.h>
#include <cmath.h>

int main() {
    bool b = true;
    if (b) {
        printf("true\n");
    } 
    if (true) {
        printf("true\n");
    } 
    if (!false)
    {
        printf("false\n");
    }
    return 0;
}
