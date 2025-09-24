#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "generator.h"

int main(int argc, char *argv[])
{
    int M = atoi(argv[1]);
    int N = atoi(argv[2]);
       
    char format_type = 'i'; 
    if (argc == 4) {
        if (strcmp(argv[3], "-f") == 0) {
            format_type = 'f';
        } else if (strcmp(argv[3], "-h") == 0) {
            format_type = 'h';
        } else if (strcmp(argv[3], "-b") == 0) {
            format_type = 'b';
        } else {
            fprintf(stderr, "Error: Unknown option '%s'\n", argv[3]);
            return 1;
        }
    }

    switch (format_type) {
        case 'f':
            generate_float(M, N);
            break;
        case 'h':
            generate_hexa(M, N);
            break;
        case 'b':
            generate_bin(M, N);
            break;
        default:
            generate_integers(M, N);
            break;
    }
    
    return 0;
}