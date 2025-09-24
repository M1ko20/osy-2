#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void generate_hexa(int M, int N){
    for (int i = 0; i < N; i++) {
        int count = (rand() % M) + 1; 
        int sum = 0;
        
        for (int j = 0; j < count; j++) {
            int num = (rand() % 9999) + 10;
            printf("0x%x ", num);
            sum += num;
        }
        printf("0x%x\n", sum);
    }
}