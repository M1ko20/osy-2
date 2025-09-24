
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "../inc/checker.h"

int check_numbers(int debug) {
    char input_row[10000];
    int row_index = 1;
    
    while (fgets(input_row, sizeof(input_row), stdin)) {        
        char *current_part = strtok(input_row, " ");
        float total_amount = 0.0;
        int item_counter = 0;
        
        while (current_part != NULL) {
            char *next_part = strtok(NULL, " ");

            if (strncmp(current_part, "0x", 2) == 0 || strncmp(current_part, "0b", 2) == 0) {
                fprintf(stderr, "Chyba:  nepovedl se radek %d\n", row_index);
                return 0;
            }
            
            float number_value = atof(current_part);
            
            if (next_part == NULL) {
                if (debug) {
                    printf("Moje suma = %.2f, Suma ze vstupu = %.2f\n", total_amount, number_value);
                }
                if (fabs(total_amount - number_value) > 0.01) {
                    if (debug) {
                        fprintf(stderr, "Chyba cekal jsem sumu: %.2f, dostal jsem: %.2f\n", number_value, total_amount);
                    }
                    return 0;
                }
                break;
            } else {
                total_amount += number_value;
                item_counter++;
            }
            
            current_part = next_part;
        }
        
        row_index++;
    }
    
    return 1;
}