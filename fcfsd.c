#include <stdio.h>
#include <stdlib.h>

void fifo(int requests[], int n, int head)
{
    int total = 0;
    int current = head;
    int alloted[n + 1];
    alloted[0] = head;
    for (int i = 0; i < n; i++)
    {
        total += abs(current - requests[i]);
        current = requests[i];
        alloted[i + 1] = requests[i];
    }

    printf("Head Movements: ");
    for (int i = 0; i < n + 1; i++)
    {
        printf("%d-->", alloted[i]);
    }
    printf("\nTotal head Movement = %d", total);
}

int main()
{
    int n, head;
    printf("Enter the number of requests: ");
    scanf("%d", &n);
    int requests[n];
    printf("Enter the requests: ");
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &requests[i]);
    }
    printf("Enter the disk head: ");
    scanf("%d", &head);
    fifo(requests, n, head);
    
    return 0;
}
