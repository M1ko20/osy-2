#include <stdio.h>
#include "checker.h"

int main()
{
    if (check_numbers()) {
        printf("Verifikace prosla :)\n");
        return 0;
    } else {
        printf("Verifikace nevysla :(\n");
        return 1;
    }
}