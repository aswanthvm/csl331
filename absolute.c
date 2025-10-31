#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void main() {
    FILE *fp, *fo;
    int i, j, staddr1;
    char name[10], line[50], name1[10], staddr[10];

    printf("Enter Program Name: ");
    scanf("%s", name);

    fp = fopen("input.txt", "r");
    fo = fopen("output.txt", "w");

    fscanf(fp, "%s", line);

    for (i = 2, j = 0; j < 6; i++, j++) {
        name1[j] = line[i];
    }
    name1[j] = '\0';

    printf("Name from input file: %s\n", name1);

    if (strcmp(name, name1) == 0) {
        
        while (fscanf(fp, "%s", line) != EOF) {

            if (line[0] == 'T') {
                
                for (i = 2, j = 0; j < 6; i++, j++) {
                    staddr[j] = line[i];
                }
                staddr[j] = '\0';
                staddr1 = atoi(staddr); 

                i = 12; 

                while (line[i] != '$') {
                    if (line[i] != '^') {
                        printf("%06X\t%c%c\n", staddr1, line[i], line[i + 1]);
                        fprintf(fo, "%06X\t%c%c\n", staddr1, line[i], line[i + 1]);
                        staddr1++; 
                        i += 2;    
                    } else {
                        i++; 
                    }
                }
            }
            else if (line[0] == 'E') {
                fclose(fo);
                exit(0); 
            }
        }
    } else {
        printf("Error: Program names do not match.\n");
    }

    fclose(fp);
    fclose(fo);
}