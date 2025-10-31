#include <stdio.h>
#include <stdlib.h>

void scan(int requests[], int n, int head, char direction) {
    int total = 0;
    int temp;
    
    // Simple sort
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (requests[i] > requests[j]) {
                temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }

    printf("Head Movements: %d", head);

    if (direction == 'r') {  // moving right first
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
        total += abs(head - 199);  // go to end
        head = 199;
        printf(" --> %d", head);
        for (int i = 0; i < n; i++) { // come back to left requests
            if (requests[i] < head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
    } else {  // moving left first
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
        total += abs(head - 0);  // go to beginning
        head = 0;
        printf(" --> %d", head);
        for (int i = n - 1; i >= 0; i--) { // come back to right requests
            if (requests[i] > head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main() {
    int n, head;
    char direction;
    printf("Enter number of requests: ");
    scanf("%d", &n);

    int requests[n];
    printf("Enter requests: ");
    for (int i = 0; i < n; i++) scanf("%d", &requests[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter direction (l for left, r for right): ");
    scanf(" %c", &direction);

    scan(requests, n, head, direction);
    return 0;
}
