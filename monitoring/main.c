#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#define SIZE 100

// Reem
//processes
//{
//    //int id;
//    //int compTime;
//    int arrival_time;
//    int cpuTime;
//    int totalCpu;
//    int IOnumber;
//    int IOduration;
//    char state;
//    char isIO;
//};

// Kareem
typedef struct process {
	char name[10];
	char state[15];
	int ID;
	//int burst_time;
	int arrival_time;
	int priority;
	int running_time;
	int completion_time;
	int flag_IO;
	int IO_time;
	int CPU_time;
	////////////////////
		int cpuTime;
		int totalCpu;
    char isIO;
	int waiting_time;
	int turnarround_time;
	int flag;
	int compTime;
}processes;
void rrFunc(processes** arrP, int num, int ts);
int Data(processes P[]);
int front = 0,rear = -1;
processes (**queArr)[SIZE];
 void enqueue(processes *p)
{
    if(rear == SIZE-1)
    {
        rear = -1;
    }
    rear++;
    queArr[rear] = p;

}
//--------------------------------------------------------------
 processes* dequeue()
{
    processes* temp = queArr[front];
    front++;
    if(front == SIZE)
    {
    front = 0;
    }
    return temp;
}

void sort(processes** arr, int num)
{
    int out, in;
    for(out=num-1; out>=1; out--)
    {
        for(in=0; in<out; in++)
        {
            if( arr[in]->arrival_time > arr[in+1]->arrival_time )
            {
                swap(&(arr[in]), &(arr[in]));
            }
        }
    }
}
void swap(processes** p1, processes** p2)
{
    processes * temp = p1;
    p1 = p2;
    p2 = temp;
}
//int main()
//{
//    printf("Hello world!\n");
//		rrFunc( arrP );
//    return 0;
//}
int main(){

	processes P[10];
	int ch,n;
	do{
		printf("\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n");
		printf("\n Options:");
		printf("\n 0. Enter process data.");
		printf("\n 1. FCFS");
		printf("\n 2. SJF");
		printf("\n 3. SJCF");
		printf("\n 4. MLFQ");
		printf("\n 5. Round Robin");
		printf("\n 6. Exit\n Select : ");
		scanf("%d",&ch);
		switch(ch){
			case 0:
				n=Data(P);
				break;
			case 1:
//				FCFS(P,n);
				break;
			case 2:

				break;
			case 3:
//				SJCF(P,n);
				break;
			case 4:

				break;
			case 5:
				int ts;
				printf("\nPlease, Enter time slice: ");
				scanf("%d",&ts);
				// TODO
				rrFunc( P, n , ts  );

				break;
			case 6:
			    exit(0);
		}
	}while(ch != 6);
	//getch();
	return 0;
}

void rrFunc(processes** arrP, int num, int ts)
{

    sort(arrP, num);

    int finP=0,currentT=arrP[0]->arrival_time;
    enqueue(arrP[0]);
		strcpy(arrP[0]->state, "D");
    while(finP < num)
    {
        processes* cp;
        if( (cp=dequeue()) != NULL)
        {
		strcpy(cp->state, "R");
            for(int j=0; j<ts; j++)
            {
                cp->compTime--;
                for(int k=0; k<num; k++)
                {
                    if(arrP[k]->arrival_time >= currentT && arrP[k]->state == "B")
                    {
                        enqueue(arrP[k]);
												strcpy(cp->state, "D");
                    }
                }
                if(cp->compTime !=0)
                {
                    int fd = open(mkfifo, O_WRONLY);
                    write(fd, &currentT, sizeof(int));
                    write(fd, &num, sizeof(int));
                    for(int i=0; i<num; i++)
                    {
                        write(fd, &arrP[i]->state, sizeof(char));
                    }
                    for(int i=0; i<num; i++)
                    {
                        write(fd, &arrP[i]->ID, sizeof(int));
                    }
                    close(fd);
                    currentT++;
                }
                else
                {
                    break;
                }
            }

						strcpy(cp->state, "D");

            if(cp->compTime !=0)
            {
                enqueue(cp);
            }
            else if(cp->isIO == 'N')
            {
                finP++;
						strcpy(cp->state, "F");
            }
            else if(cp->isIO == 'Y' && cp->flag_IO ==0)
            {
                finP++;
						strcpy(cp->state, "F");
            }

            if(cp->isIO == 'Y' && cp->flag_IO !=0 && cp->compTime==0)
            {
                cp->flag_IO--;

                cp->arrival_time = currentT + cp->IO_time;
						strcpy(cp->state, "B");
            }
        }
        else
        {
            currentT++;
            for(int k=0; k<num; k++)
                {
                    if(arrP[k]->arrival_time >= currentT && arrP[k]->state == "B")
                    {
                        enqueue(arrP[k]);
												strcpy(arrP[k]->state, "D");
                    }
                }
        }
    }
}

int Data(processes P[]){
	int i,n,f;
	printf("\n Enter total no. of processes (Max 10): ");
	scanf("%d",&n);
	for(i=0;i<n;i++){
		printf("\n PROCESS [%d]",i+1);
		printf(" Enter process name : ");
		scanf("%s",&P[i].name);
		P[i].ID = (i + 1);
		//printf(" Enter burst time : ");
		//scanf("%d",&P[i].burst_time);
		printf(" Enter arrival time : ");
		scanf("%d",&P[i].arrival_time);
		printf(" Enter priority : ");
		scanf("%d",&P[i].priority);
		printf(" Enter CPU time : ");
        scanf("%d",&P[i].CPU_time);
        printf(" Enter number of I/O request : ");
        scanf("%d",&P[i].flag_IO);
        printf(" Enter I/O time : ");
        scanf("%d",&P[i].IO_time);
        P[i].running_time = (P[i].CPU_time + (P[i].flag_IO * P[i].IO_time));
        strcpy(P[i].state, "Not Yet");
	}
	printf("\n PROC.\tPROC.ID.\tRunning.Time.\tArrival.Time.\tI/O.Requests.\tPRIORITY");
	for(i=0;i<n;i++)
		printf("\n %s\t%d\t\t%d\t\t%d\t\t%d\t\t%d",P[i].name,P[i].ID,P[i].running_time,P[i].arrival_time,P[i].flag_IO,P[i].priority);
	return n;
}
