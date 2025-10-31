#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE *intermediate, *optab, *symtab, *output;
    char label[20], opcode[20], operand[20];
    char code[20], mnemonic[20];
    char symLabel[20];
    int symAddr;
    int locctr, startAddr = 0, length = 0, objAddr;
    char objectCode[20];
    int found;

    intermediate = fopen("intermediate.txt", "r");
    optab = fopen("optab.txt", "r");
    symtab = fopen("symtab.txt", "r");
    output = fopen("objectcode.txt", "w");

    if (!intermediate || !optab || !symtab || !output) {
        printf("Error opening files.\n");
        return 1;
    }

    fscanf(intermediate, "%s %s %s", label, opcode, operand);
    if (strcmp(opcode, "START") == 0) {
        startAddr = strtol(operand, NULL, 16);
        fprintf(output, "H^%s^%06X^\n", label, startAddr);
        fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    }

    fprintf(output, "T^");

    while (strcmp(opcode, "END") != 0) {
        rewind(optab);
        found = 0;
        while (fscanf(optab, "%s %s", code, mnemonic) != EOF) {
            if (strcmp(opcode, code) == 0) {
                rewind(symtab);
                while (fscanf(symtab, "%s %X", symLabel, &symAddr) != EOF) {
                    if (strcmp(operand, symLabel) == 0) {
                        sprintf(objectCode, "%s%04X", mnemonic, symAddr);
                        fprintf(output, "%s ", objectCode);
                        found = 1;
                        break;
                    }
                }
                break;
            }
        }

        if (!found) {
            if (strcmp(opcode, "WORD") == 0) {
                int value = atoi(operand);
                sprintf(objectCode, "%06X", value);
                fprintf(output, "%s ", objectCode);
            } else if (strcmp(opcode, "BYTE") == 0) {
                if (operand[0] == 'C') {
                    int i;
                    for (i = 2; i < strlen(operand) - 1; i++)
                        fprintf(output, "%X", operand[i]);
                    fprintf(output, " ");
                }
            } else if (strcmp(opcode, "RESW") == 0 || strcmp(opcode, "RESB") == 0) {
                fprintf(output, "\n");
            }
        }

        fscanf(intermediate, "%X %s %s %s", &locctr, label, opcode, operand);
    }

    fprintf(output, "\nE^%06X\n", startAddr);

    fclose(intermediate);
    fclose(optab);
    fclose(symtab);
    fclose(output);

    printf("\nPass 2 completed. Object code generated in 'objectcode.txt'\n");
    return 0;
}
