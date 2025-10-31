#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *input, *optab, *symtab, *intermediate;
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[20];
    int locctr = 0, start = 0, length = 0;
    int found;

    input = fopen("input.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "w");
    intermediate = fopen("intermediate.txt", "w");

    if (!input || !optab || !symtab || !intermediate) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(input, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        start = strtol(operand, NULL, 16);
        locctr = start;
        fprintf(intermediate, "    %s\t%s\t%s\n", label, opcode, operand);
        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    while (strcmp(opcode, "END") != 0) {
        fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);

        if (strcmp(label, "**") != 0)
            fprintf(symtab, "%s\t%04X\n", label, locctr);

        rewind(optab);
        found = 0;
        while (fscanf(optab, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                locctr += 3;
                found = 1;
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0)
                locctr += 3;
            else if (strcmp(opcode, "RESW") == 0)
                locctr += 3 * atoi(operand);
            else if (strcmp(opcode, "RESB") == 0)
                locctr += atoi(operand);
            else if (strcmp(opcode, "BYTE") == 0)
                locctr += 1;
        }

        fscanf(input, "%s %s %s", label, opcode, operand);
    }

    fprintf(intermediate, "%04X\t%s\t%s\t%s\n", locctr, label, opcode, operand);
    length = locctr - start;
    printf("\nProgram length = %X\n", length);

    fclose(input);
    fclose(optab);
    fclose(symtab);
    fclose(intermediate);

    printf("\nPass 1 completed.\n");
    return 0;
}
