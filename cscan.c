#include <stdio.h>
#include <stdlib.h>

void cscan(int requests[], int n, int head, char direction) {
    int total = 0, temp;

    // Simple sort
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (requests[i] > requests[j]) {
                temp = requests[i];
                requests[i] = requests[j];
                requests[j] = temp;
            }

    printf("Head Movements: %d", head);

    if (direction == 'r') {  // move right first
        for (int i = 0; i < n; i++) {
            if (requests[i] >= head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
        // Go to end
        total += abs(head - 199);
        head = 0;  // jump to beginning (circular)
        printf(" --> 199 --> 0");

        for (int i = 0; i < n; i++) { // service remaining left requests
            if (requests[i] < head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
    } else {  // move left first
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= head) {
                total += abs(head - requests[i]);
                head = requests[i];
                printf(" --> %d", head);
            }
        }
        // Go to beginning
        total += abs(head - 0);
        head = 199;  // jump to end (circular)
        printf(" --> 0 --> 199");

        for (int i = n - 1; i >= 0; i--) { // service remaining right requests
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

    cscan(requests, n, head, direction);
    return 0;
}
