#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "checker.h"

int check_numbers() {
    char input_buffer[10000];
    int current_row = 1;
    
    while (fgets(input_buffer, sizeof(input_buffer), stdin)) {
        char *current_word = strtok(input_buffer, " ");
        int accumulated_total = 0;
        int processed_items = 0;
        
        while (current_word != NULL) {
            char *following_word = strtok(NULL, " ");
            
            if (strstr(current_word, ".") || strncmp(current_word, "0x", 2) == 0 || strncmp(current_word, "0b", 2) == 0) {
                fprintf(stderr, "Chyba, nepovedl se radek %d\n", current_row);
                return 0;
            }
            
            int parsed_value = atoi(current_word);
            
            if (following_word == NULL) {
                printf("Moje suma = %d, Suma ze vstupu = %d\n", current_row, accumulated_total, parsed_value);
                if (accumulated_total != parsed_value) {
                    fprintf(stderr, "Chyba: Cekal jsem sumu: %d, dostal jsem: %d\n", current_row, parsed_value, accumulated_total);
                    return 0;
                } 
                break;
            } else {
        
                accumulated_total += parsed_value;
                processed_items++;
            }

            current_word = following_word;
        }

        current_row++;
    }
    
    return 1;
}