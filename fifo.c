#include <stdio.h>
#include <stdlib.h>

int frames[3], rear = 0, pagefaults = 0;

void initialize() {
    for(int i=0; i<3; i++) frames[i] = -1;
}

void display() {
    for(int i=0; i<3; i++)
        printf(frames[i]!=-1 ? "%d " : "-- ");
    printf("\n");
}

void fifo(int pages[], int n) {
    int found;
    for(int i=0; i<n; i++) {
        found = 0;
        for(int j=0; j<3; j++)
            if(frames[j] == pages[i]) { found = 1; break; }

        if(!found) {
            frames[rear] = pages[i];
            rear = (rear+1)%3;
            pagefaults++;
        }
        display();
    }
    printf("Number of page faults: %d\n", pagefaults);
}

int main() {
    int n;
    printf("Enter number of pages: "); scanf("%d",&n);
    int pages[n];
    printf("Enter page sequence: ");
    for(int i=0;i<n;i++) scanf("%d",&pages[i]);
    initialize();
    fifo(pages,n);
    return 0;
}
