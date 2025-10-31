#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *fp;
    int i, j, staddr, len, reloc_addr;
    char line[100], name[10], addr_str[10], len_str[10];
    char mod_addr_str[10], mod_len_str[10];
    int mod_addr, mod_len, modified_val;

    printf("Enter the relocating (starting) address (in Hex): ");
    scanf("%x", &reloc_addr); 

    fp = fopen("reloc_input.txt", "r");
    if (fp == NULL) {
        printf("Error: Cannot open input file.\n");
        exit(1);
    }

    fscanf(fp, "%s", line);
    if (line[0] == 'H') {
        strncpy(name, line + 2, 6); 
        name[6] = '\0';
        printf("Loading Program: %s\n", name);
        printf("Loading from address: %06X\n\n", reloc_addr);
    } else {
        printf("Invalid Header Record.\n");
        exit(1);
    }

    while (fscanf(fp, "%s", line) != EOF) {
        
        if (line[0] == 'T') {
            strncpy(addr_str, line + 2, 6);
            addr_str[6] = '\0';
            staddr = (int)strtol(addr_str, NULL, 16);

            int relocated_staddr = staddr + reloc_addr;

            printf("T Record: Loading at %06X\n", relocated_staddr);
        }
        else if (line[0] == 'M') {
            strncpy(mod_addr_str, line + 2, 6);
            mod_addr_str[6] = '\0';
            mod_addr = (int)strtol(mod_addr_str, NULL, 16);

            strncpy(mod_len_str, line + 9, 2);
            mod_len_str[2] = '\0';
            mod_len = (int)strtol(mod_len_str, NULL, 16);

            int relocated_mod_addr = mod_addr + reloc_addr;

            printf("M Record: Modifying address %06X (for %d half-bytes)\n", 
                   relocated_mod_addr, mod_len);
        }
        else if (line[0] == 'E') {
            printf("\n--- End of Loading ---\n");
            break;
        }
    }

    fclose(fp);
}