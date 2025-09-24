#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void generate_integers(int M, int N)
{
    
    for (int i = 0; i < N; i++) {
        int count = (rand() % M) + 1;  
        int sum = 0;
        
        for (int j = 0; j < count; j++) {
            int num = (rand() % 9999) + 10;  
            printf("%d ", num);
            sum += num;
        }
        printf("%d\n", sum);
    }
}