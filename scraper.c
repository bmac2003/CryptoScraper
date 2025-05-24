#include <stdio.h>

#include "scraper.h"

int main() {
    printf("Hello World!\n");
    struct test_structure test = {0, 0.0};
    printf("%d, %f\n", test.test_int, test.test_double);
    return 0;
}
