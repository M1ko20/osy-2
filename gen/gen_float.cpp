#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void generate_float(int M, int N)
{    
    for (int i = 0; i < N; i++) {
        int count = (rand() % M) + 1; 
        float sum = 0;
        
        for (int j = 0; j < count; j++) {
            float num = (rand() % 9999) + 10;  
            printf("%.2f ", num);
            sum += num;
        }
        printf("%.2f\n", sum);
    }
}