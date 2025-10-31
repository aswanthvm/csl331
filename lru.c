#include <stdio.h>
#include <stdlib.h>

int frames[3], time[3], pagefaults = 0;

void initialize() {
    for(int i=0;i<3;i++) { frames[i]=-1; time[i]=0; }
}

void display() {
    for(int i=0;i<3;i++)
        printf(frames[i]!=-1 ? "%d " : "-- ");
    printf("\n");
}

int findLRU() {
    int min = time[0], pos = 0;
    for(int i=1;i<3;i++)
        if(time[i]<min){ min=time[i]; pos=i; }
    return pos;
}

void lru(int pages[], int n) {
    int currenttime=0, found;
    for(int i=0;i<n;i++) {
        found=0;
        for(int j=0;j<3;j++) {
            if(frames[j]==pages[i]) {
                found=1;
                time[j]=currenttime;
                break;
            }
        }
        if(!found) {
            int rep = -1;
            for(int j=0;j<3;j++)
                if(frames[j]==-1){ rep=j; break; }
            if(rep==-1) rep=findLRU();
            frames[rep]=pages[i];
            time[rep]=currenttime;
            pagefaults++;
        }
        currenttime++;
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
    lru(pages,n);
    return 0;
}
