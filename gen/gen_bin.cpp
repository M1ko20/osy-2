#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

void print_binary(int n) {
    printf("0b");
    if (n == 0) {
        printf("0");
        return;
    }
    
    char binary[33];
    int i = 0;
    while (n > 0) {
        binary[i++] = (n % 2) + '0';
        n /= 2;
    }
    
    for (int j = i - 1; j >= 0; j--) {
        printf("%c", binary[j]);
    }
}

void generate_bin(int M, int N) {
    for (int i = 0; i < N; i++) {
        int count = (rand() % M) + 1; 
        int sum = 0;
        printf(" ");
        for (int j = 0; j < count; j++) {
            int num = (rand() % 9990) + 10;
            print_binary(num);
            printf(" ");
            sum += num;
        }
        print_binary(sum);
        printf("\n");
    }
}