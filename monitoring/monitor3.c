#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
int main()
{
    int time,nump;
    while(1)
    {
        int fd =open(myfifo, O_RDONLY);
        read(fd, &time, sizeof(int));
        read(fd, &nump, sizeof(int));
        char*pState = malloc(nump * sizeof(char));
        int*pId = malloc(nump * sizeof(int));
        for(int i=0; i<nump; i++)
        {
            read(fd, &pState[i], sizeof(char));
        }
        for(int i=0; i<num; i++)
        {
            write(fd, &pId[i], sizeof(int));
        }
        close(fd);

        printf("At sec: %d", time);
        for(int i=0; i<nump; i++)
        {
            printf("process %d is: ", pId[i]+1)
            if(pState[i]=='R')
            {
                printf("Running\t");
            }
            else if(pState[i]=='D')
            {
                printf("Ready\t");
            }
            else if(pState[i]=='F')
            {
                printf("Finshed\t");
            }
            else if(pState[i]=='B')
            {
                printf("Blocked\t");
            }
        }
        prinf("\n\n");
    }
    return 0;
}
