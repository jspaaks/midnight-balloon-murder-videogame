#include <criterion/criterion.h>
#include "mbm/subtraction.h"

Test(subtraction, one){
    int actual = subtract(2, 3);
    int expected = -1;
    cr_assert(actual == expected);
}

Test(subtraction, two){
    int actual = subtract(2, -3);
    int expected = 5;
    cr_assert(actual == expected);
}
