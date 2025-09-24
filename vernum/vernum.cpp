#include <stdio.h>
#include "/Users/adammikolas/5.Semestr/OSY/priprava/dva/test_zadani/priprava02/inc/checker.h"

int main(int argc, char* argv[])
{
    int debug = 0;
    if (argc == 2)
    {
        debug = 1;
    }
    
    if (check_numbers(debug)) {
        printf("Verifikace prosla :)\n");
        return 0;
    } else {
        printf("Verifikace nevysla :(\n");
        return 1;
    }
}