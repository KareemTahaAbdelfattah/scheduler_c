#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <conio.h>
#include <unistd.h>
#define SIZE 100

typedef struct process{
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
	int waiting_time;
	int turnarround_time;
    int flag;
}processes;



typedef struct processes{
    //name hyb2a using counter
    int pid;
    int arrival_time;
    int arr[100];
    int burst_time;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int IO_time;
    int total_time;

}p;

/*
struct process1
{
    int id;
    int compTime;
    int AT;
    int cpuTime;
    int totalCpu;
    int IOnumber;
    int IOduration;
    char state;
    char isIO;
};

int front = 0,rear = -1;
int *(queArr)[SIZE];
void enqueue(struct process1 *p) // put item at rear of queue
{
    if(rear == SIZE-1)
    {// deal with wraparound
        rear = -1;
    }
    rear++;
    queArr[rear] = p; // increment rear and insert
}
//--------------------------------------------------------------
struct process1* dequeue() // take item from front of queue
{
    struct process1* temp = queArr[front];
    front++; // get value and incr front
    if(front == SIZE)
    {
    front = 0;
    }
    return temp;
}

void sort(struct process1** arr, int num)
{
    int out, in;
    for(out=num-1; out>=1; out--)
    {
        for(in=0; in<out; in++)
        {
            if( arr[in]->AT > arr[in+1]->AT )
            {
                swap(&(arr[in]), &(arr[in]));
            }
        }
    }
}
void swap(struct process1** p1, struct process1** p2)
{
    struct process1 * temp = p1;
    p1 = p2;
    p2 = temp;
}

void RoundRobin()
{
    int num,ts;
    printf("enter num of process: \n");
    scanf("%d",&num);
    printf("enter time slice: \n");
    scanf("%d",&ts);

    struct process1** arrP = malloc(num*sizeof(struct process1*));

    for(int i=0; i<num; i++)
    {
        arrP[i] = malloc(sizeof(struct process1));
    }
    for(int i=0; i<num; i++)
    {
        printf("process %d info:\n",i+1);
        printf("is I/O?: \n");
        scanf("\n%c", &arrP[i]->isIO);
        if(arrP[i]->isIO == 'Y')
        {
            printf("enter number of I/Os: \n");
            scanf("%d", &(arrP[i]->IOnumber));
            printf("enter I/O duration: \n");
            scanf("%d", &(arrP[i]->IOduration));
            printf("enter total cpu time: \n");
            scanf("%d", &(arrP[i]->totalCpu));
            int parts = arrP[i]->IOnumber +1;
            arrP[i]->cpuTime = arrP[i]->totalCpu /parts;
            arrP[i]->compTime = arrP[i]->cpuTime;
        }
        else
        {
            printf("completion time: \n");
            scanf("%d", &(arrP[i]->compTime));
            arrP[i]->isIO = 'N';
        }
        printf("Arrival time: \n");
        scanf("%d", &(arrP[i]->AT));
        arrP[i]->id = i+1;
        arrP[i]->state = 'B';
    }

    sort(arrP, num);

    int finP=0,currentT=arrP[0]->AT;
    enqueue(arrP[0]);
    arrP[0]->state = 'D';
    while(finP < num)
    {
        struct process1* cp;
        if( (cp=dequeue()) != NULL)
        {
            cp->state = 'R';
            for(int j=0; j<ts; j++)
            {
                cp->compTime--;
                for(int k=0; k<num; k++)
                {
                    if(arrP[k]->AT >= currentT && arrP[k]->state == 'B')
                    {
                        enqueue(arrP[k]);
                        arrP[k]->state = 'D';
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
                        write(fd, &arrP[i]->id, sizeof(int));
                    }
                    close(fd);
                    currentT++;
                }
                else
                {
                    break;
                }
            }

            cp->state ='D';

            if(cp->comTime !=0)
            {
                enqueue(cp);
            }
            else if(cp->isIO == 'N')
            {
                finP++;
                cp->state = 'F';
            }
            else if(cp->isIO == 'Y' && cp->IOnumber ==0)
            {
                finP++;
                cp->state = 'F';
            }

            if(cp->isIO == 'Y' && cp->IOnumber !=0 && cp->compTime==0)
            {
                cp->IOnumber--;
                cp->AT = currentT + cp->IOduration;
                cp->state = 'B';
            }
        }
        else
        {
            currentT++;
            for(int k=0; k<num; k++)
                {
                    if(arrP[k]->AT >= currentT && arrP[k]->state == 'B')
                    {
                        enqueue(arrP[k]);
                        arrP[k]->state = 'D';
                    }
                }
        }
    }
}*/

/////////// MIT License ////////////
/// This is a scheduler simulator ///

typedef  enum state {
	running,
	yet,
	ready,
	blocked,
	finished
} State;

struct Process2
{
    int id;
    char *name;
		int q;
		int ETA;
		int time;
		State s;
		struct Process2 *next;
};
void init_process (struct Process2 *, char *name, int ETA );
void display();
void insert_process(char *name, int ETA);
void loopScheduler();
void printf_t(char*);
void printf_t_d(int i);
void p_splitter();
void p_splitter_line();
void prefix();
/// global variables ///
int id_counter = 0;
struct Process2 *head = NULL;
const int NQUEUES = 4;
int queueTime[3] = {5, 25, 55} ;

void loopScheduler(){
	display();
	int highestQ = 1;

	struct Process2 *current = head;
	while(current != NULL){
		if(current->s == finished){
			current = current->next;
			continue;

		}
		if(current->time <= queueTime[0]){
			current->q = 4;
			highestQ = current->q > highestQ? current->q : highestQ;
		}
		else if(current->time > queueTime[0] && current->time <= queueTime[1]){

			current->q = 3;

			highestQ = current->q > highestQ? current->q : highestQ;
		}
		else if( current->time > queueTime [1] && current->time <= queueTime[2]){

			current->q = 2;
			highestQ = current->q > highestQ? current->q : highestQ;

		}
		else if(current->time > queueTime[3]){
			current->q = 1;
			highestQ = current->q > highestQ? current->q : highestQ;
		}else {

		}
		if(current->s == running && current->s != yet ){ current->s = blocked; }
		current = current->next;
	}

	current = head;


	while(current != NULL){
		if(current->time >= current->ETA){
			current->q = NULL;
			current->s = finished;
		}

		if( current->q == highestQ ){
			current->time ++;
			current->s = running;
		break;
		}

		current = current->next;
	}
	sleep(1);
	loopScheduler();

}

void init_process (struct Process2 *new, char *name, int ETA){
	id_counter++;
	new->id = id_counter;
	new->next = NULL;
	new->name = name;
	new->ETA = ETA;
	new->q = NQUEUES;
	new->time = 0;
	new->s    = yet;
}

//insert link at the first location
void insert_process(char *name, int ETA) {
   //create a link
   struct Process2 *new = (struct Process2*) malloc(sizeof(struct Process2));

	 init_process(new, name, ETA );


   //point it to old first node
   new->next = head;

   //point first to new first node
   head = new;
}

void display(){
	struct Process2 *current = head;
        system("clear");
        prefix();
		printf_t("Name");
		printf_t("ID");
		printf_t("Queue");
		printf_t("State");
		printf_t("Time On CPU");
		printf_t("ETA");
		printf("\n");
		p_splitter_line();
	while(current != NULL){
		char *s;
		switch( current->s ){
			case running:
				s = "Running";
				break;
			case blocked:
				s = "Blocked";
				break;
			case ready:
				s = "Ready";
				break;
			case yet:
				s = "Yet to run";
				break;
			case finished:
				s = "Finished";
			//case running:
			//	s = "running";
			//	break;
			//case running:
			//	s = "running";
			//	break;
			//case running:
			//	s = "running";
			//	break;

		}
		prefix();
		printf_t(current->name);
		printf_t_d(current->id);
		printf_t_d(current->q);
		printf_t(s);
		printf_t_d(current->time);
		printf_t_d(current->ETA);
		printf("\n");
		p_splitter_line();
		current = current->next;
	}

}


void printf_t(char * str){
		printf("%14s%5s|",str, "" );
}
void printf_t_d(int i){
		printf("%10s%2.2d%7s|","",i, "");
}
void p_splitter(){
	for(int i = 0; i< 19; i++){
	printf("_");
	}
	printf("|");
}
void p_splitter_line(){
prefix();
	for(int i = 0; i< 6; i++){
		p_splitter();
	}
	printf("\n");
}

void prefix(){

	for(int i = 0; i< 6; i++){
		printf(" ");
	}
	printf("|");
}


void FCFS_sort(processes temp[],int n) // sort about what is the process arrived before others
{
	processes t;
	int i,j;
	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if(temp[j].arrival_time > temp[j+1].arrival_time){
				t = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = t;
			}
		}
	}

	for(i=1;i<n;i++){
		for(j=0;j<n-i;j++){
			if((temp[j].arrival_time == temp[j+1].arrival_time) && (temp[j].priority < temp[j+1].priority)){
				t = temp[j];
				temp[j] = temp[j+1];
				temp[j+1] = t;
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

// FCFS Algorithm
void FCFS(processes P[],int n){
	processes temp[n];
	int sumw=0,sumt=0;
	int x = 0;
	float avgwt=0.0,avgta=0.0;
	int i,j;
	for(i=0;i<n;i++) temp[i]=P[i];

	FCFS_sort(temp,n);

    printf("\n\n PROC.\tPROC.ID.\tRunning.Time.\tArrival.Time.\tI/O.Requests.\tPRIORITY");
    for(i=0;i<n;i++) printf("\n %s\t%d\t\t%d\t\t%d\t\t%d\t\t%d",temp[i].name,temp[i].ID,temp[i].running_time,temp[i].arrival_time,temp[i].flag_IO,temp[i].priority);

    sumw = temp[0].waiting_time = 0;
    temp[0].completion_time = temp[0].arrival_time + temp[0].running_time;
    sumt = temp[0].turnarround_time = temp[0].running_time;

    for(i=1;i<n;i++){
        if(temp[i].arrival_time > temp[i].completion_time){
            temp[i].completion_time = temp[i].arrival_time + temp[i].running_time;
            temp[i].waiting_time = 0;
            temp[i].turnarround_time = temp[i].completion_time - temp[i].arrival_time;
            sumw+=temp[i].waiting_time;
            sumt+=temp[i].turnarround_time;
        }
        else{
            temp[i].completion_time = temp[i - 1].completion_time + temp[i].running_time;
            temp[i].waiting_time = (temp[i - 1].running_time + temp[i - 1].arrival_time + temp[i-1].waiting_time) - temp[i].arrival_time;
            temp[i].turnarround_time = (temp[i].waiting_time + temp[i].running_time);
            sumw+=temp[i].waiting_time;
            sumt+=temp[i].turnarround_time;
        }
    }


    for(int i = 0; i <= temp[n - 1].completion_time; i++){
        for(int j = 0; j < n; j++){
            if((temp[j].arrival_time + temp[j].waiting_time) <= i && (temp[j].completion_time - 1) >= i){
                if(temp[j].CPU_time > (i - (temp[j].arrival_time + temp[j].waiting_time))) strcpy(temp[j].state, "Running");
                else strcpy(temp[j].state, "Blocked");
            }
            else if(temp[j].arrival_time <= i && (temp[j].arrival_time + temp[j].waiting_time) > i) strcpy(temp[j].state, "Ready");
            else if(temp[j].completion_time <= i) strcpy(temp[j].state, "Finished");
            printf("\nTime%d- Process [%s] Id [%d] is --> %s.",i,temp[j].name,temp[j].ID,temp[j].state);
            sleep(1);
        }
    }



    avgwt = (float)sumw/n;
    avgta = (float)sumt/n;
    printf("\n\n PROC.\tR.T.\tA.T.\tW.T\tT.A.T.\t.C.T");
    for(i=0;i<n;i++) printf("\n %s\t%d\t%d\t%d\t%d\t%d",temp[i].name,temp[i].running_time,temp[i].arrival_time,temp[i].waiting_time,temp[i].turnarround_time,temp[i].completion_time);

    printf("\n\n GANTT CHART\n ");
    for(i=0;i<n;i++) printf("   %s   ",temp[i].name);
    printf("\n ");

    printf("0\t");
    for(i=1;i<=n;i++){
        x+=temp[i-1].running_time;
        printf("%d      ",x);
    }
    printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}


//Shortest Job First - Pre-emptive
void SJCF(processes P[],int n){
	int i,t_total=0,tcurr,b[n],j,x,min_rt;
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
	processes temp[n];
	for(i=0;i<n;i++){
		temp[i]=P[i];
		t_total+=P[i].running_time;
	}
	temp[0].completion_time = temp[0].running_time + temp[0].arrival_time;
	FCFS_sort(temp,n);

	for(i=0;i<n;i++) b[i] = temp[i].running_time;

	i=j=0;

	printf("\n GANTT CHART\n\n %d %s",i+1,temp[i].name);

	for(tcurr=0;tcurr<t_total;tcurr++){

		if(b[i] > 0 && temp[i].arrival_time <= tcurr) b[i]--;

		if(i!=j) printf(" %d %s",tcurr,temp[i].name);

		if(b[i]<=0 && temp[i].flag != 1){
			temp[i].flag = 1;
			temp[i].waiting_time = (tcurr+1) - temp[i].running_time - temp[i].arrival_time;
			temp[i].turnarround_time = (tcurr+1) - temp[i].arrival_time;
			sumw+=temp[i].waiting_time;
			sumt+=temp[i].turnarround_time;
		}
		j=i;
		min_rt = 1000000000;
		for(x=0;x<n;x++){
			if(temp[x].arrival_time <= (tcurr+1) && temp[x].flag != 1){
				if(min_rt != b[x] && min_rt > b[x]){
					min_rt = b[x];
					i=x;
				}
			}
		}
	}
	printf(" %d",tcurr);
	avgwt = (float)sumw/n;	avgta = (float)sumt/n;
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}



void SJF_cpu(){
    int num_processes;
    int j,i;
    printf("please enter the number of processes\n");
    scanf("%d",&num_processes);
    p *process_array; // process is pointer to structure p
    process_array = malloc(sizeof(p)* num_processes);
    if (process_array == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    memset(process_array, 0, sizeof(*process_array));
    int *completed_arr;
    completed_arr =(int*) malloc(sizeof(int)*num_processes);
    if (completed_arr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    memset(completed_arr, 0, sizeof (int)*num_processes);


for(i=0;i<num_processes;i++){
    printf("please enter process %d arrival time\n",i+1);
    scanf("%d",&process_array[i].arrival_time);
    printf("please enter process %d burst time\n",i+1);
    scanf("%d",&process_array[i].burst_time);

    process_array[i].pid=i+1; // p1 =1 p2= 2 so on
}

int current_time =0 ;
int completed = 0;


while(completed != num_processes) {
        int idx = -1;
        int mn =2147483647;
        for(i = 0; i < num_processes; i++) {
            if(process_array[i].arrival_time <= current_time && completed_arr[i] == 0) {
                if(process_array[i].burst_time < mn) {
                    mn = process_array[i].burst_time;
                    idx = i; //index of minimum burst time
                }
                //if both processes have the same burst time we need to compare arrival time
                if(process_array[i].burst_time == mn) {
                    if(process_array[i].arrival_time < process_array[idx].arrival_time) {
                        mn = process_array[i].burst_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {

            process_array[idx].start_time = current_time;
            process_array[idx].completion_time = process_array[idx].start_time + process_array[idx].burst_time;
            process_array[idx].turnaround_time = process_array[idx].completion_time - process_array[idx].arrival_time;
            process_array[idx].waiting_time = process_array[idx].turnaround_time - process_array[idx].burst_time;
            completed_arr[idx] = 1;
            completed++; // indicate that a process is completed
            current_time = process_array[idx].completion_time;

        }
        else {
            current_time++;
        }

    }



int count = 1;
for(i=0;i<num_processes;i++){
    printf("process %d\tpid = %d\tburst time =%d\t start time=%d\tcompletion time=%d\tturn around=%d\t waiting time=%d\n",
    count,process_array[i].pid,process_array[i].burst_time,
    process_array[i].start_time,process_array[i].completion_time,process_array[i].turnaround_time,process_array[i].waiting_time);
    count++;
}
printf("\n");
int m;
for(i=0;i<num_processes;i++){
    int z =process_array[i].arrival_time;
    for(j=z;j<=process_array[i].waiting_time+z;j++){
        process_array[i].arr[j]=1;//ready
    }
    for(m=process_array[i].start_time;m<=process_array[i].completion_time;m++){
        process_array[i].arr[m]=2;// 2 running
    }
}

for(i=0;i<num_processes;i++){
    int count_time =0;
    for(j=0;j<=process_array[i].completion_time;j++){

        if(process_array[i].arr[j]==1){
         printf("Time=%i\tp%d is ready\n",count_time,process_array[i].pid);

        }
        if(process_array[i].arr[j]==2){
        printf("Time=%i\tp%d is running\n",count_time,process_array[i].pid);

        }
        if(process_array[i].arr[j]==0){
           printf("Time=%i\tp%d not yet\n",count_time,process_array[i].pid);
        }
    count_time++;

    }
    printf("\n");
}

    int temp;
    int temp2;
    int temp3;

    for(i=0;i<num_processes-1;i++){
        for(j=0;j<num_processes-1;j++){
            if(process_array[j].start_time>process_array[j+1].start_time){
                temp=process_array[j].start_time;
                process_array[j].start_time=process_array[j+1].start_time;
                process_array[j+1].start_time=temp;

                temp2 = process_array[j].pid;
                process_array[j].pid =process_array[j+1].pid;
                process_array[j+1].pid =temp2;

                temp3 = process_array[j].burst_time;
                process_array[j].burst_time=process_array[j+1].burst_time;
                process_array[j+1].burst_time=temp3;


            }

        }

    }
    printf("\n");
    /*for(i=0;i<num_processes;i++){
        printf("p%d\t",process_array[i].pid);

    }
    printf("\n");
    for(i=0;i<num_processes;i++){

        printf("%d\t",process_array[i].start_time);
    }
    printf("\n");

   for(i=0;i<num_processes;i++){

        printf("%d\t",process_array[i].burst_time);
    }*/

printf("\n");
    for(i=0;i<num_processes;i++){

            for(j=process_array[0].start_time;j<process_array[i].burst_time;j++){
                printf("-");
            }
            printf(" ");
            printf("|");

    }
    printf("\n");

    int k=0;
    int z;
        for(i=0;i<num_processes;i++){

            for(j=process_array[0].start_time;j<process_array[i].burst_time;j++){
                if(k==0){
                  printf("p%d",process_array[i].pid);
                  k++;
                }
            }
            for(z=process_array[0].start_time;z<process_array[i].burst_time-1;z++){
                printf(" ");

            }
        printf("|");
    k=0;
    }
    printf("\n");
    for(i=0;i<num_processes;i++){
            for(j=process_array[0].start_time;j<process_array[i].burst_time;j++){
                printf("-");
            }
            printf(" ");
            printf("|");

    }




free(completed_arr);
free(process_array);

}

void SJF_IO(){
    int IO_request;
    int num_processes;
    int total_IO_time=0;
    int time;
    int j;
    printf("please enter the number of processes\n");
    scanf("%d",&num_processes);

    p *process_array; // process is pointer to structure p

    process_array = malloc(sizeof(p)* num_processes);
    if (process_array == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    memset(process_array, 0, sizeof(*process_array));
    int *completed_arr;
    completed_arr =(int*) malloc(sizeof(int)*num_processes);
    if (completed_arr == NULL) {
        printf("Memory not allocated.\n");
        exit(0);
    }
    memset(completed_arr, 0, sizeof (int)*num_processes);

int i;

for(i=0;i<num_processes;i++){

    printf("please enter process %d arrival time\n",i+1);
    scanf("%d",&process_array[i].arrival_time);
    printf("please enter process %d burst time\n",i+1);
    scanf("%d",&process_array[i].burst_time);
    printf("please enter process %d number of I/O request\n",i+1);
    scanf("%d",&IO_request);
    for(j=0;j<IO_request;j++){
        printf("enter request no %d time\n",j+1);
        scanf("%d",&time);
        total_IO_time+=time;
        process_array[i].IO_time = total_IO_time*IO_request;
        process_array[i].total_time=total_IO_time*IO_request+process_array[i].burst_time;
    }
   printf("%d\n",process_array[i].total_time);
    process_array[i].pid=i+1; // p1 =1 p2= 2 so on
}

int current_time =0 ;
int completed = 0;

while(completed != num_processes) {
        int idx = -1;
        int mn =2147483647;
        for(i = 0; i < num_processes; i++) {
            if(process_array[i].arrival_time <= current_time && completed_arr[i] == 0) {
                if(process_array[i].total_time< mn) {
                    mn = process_array[i].total_time;
                    idx = i; //index of minimum burst time
                }
                //if both processes have the same burst time we need to compare arrival time
                if(process_array[i].total_time == mn) {
                    if(process_array[i].arrival_time < process_array[idx].arrival_time) {
                        mn = process_array[i].total_time;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {

            process_array[idx].start_time = current_time;
            process_array[idx].completion_time = process_array[idx].start_time + process_array[idx].total_time;
            process_array[idx].turnaround_time = process_array[idx].completion_time - process_array[idx].arrival_time;
            process_array[idx].waiting_time = process_array[idx].start_time - process_array[idx].arrival_time;
            completed_arr[idx] = 1;
            completed++; // indicate that a process is completed
            current_time = process_array[idx].completion_time;

        }
        else {
            current_time++;
        }

    }


int count = 1;
for(i=0;i<num_processes;i++){
    printf("process %d\tpid = %d\tburst time =%d\t start time=%d\tcompletion time=%d\tturn around=%d\n",
    count,process_array[i].pid,process_array[i].burst_time,
    process_array[i].start_time,process_array[i].completion_time,process_array[i].turnaround_time);
    count++;
}
printf("\n");
int m;
int z;
for(i=0;i<num_processes;i++){
    int z =process_array[i].arrival_time;
    for(j=z;j<=process_array[i].start_time;j++){
       process_array[i].arr[j]=1;//ready
    }
    for(m=process_array[i].start_time;m<=process_array[i].burst_time+process_array[i].start_time;m++){
        process_array[i].arr[m]=2;// 2 running
    }
    int x = process_array[i].completion_time;
    for(z=process_array[i].burst_time+process_array[i].start_time+1;z<=x;z++){
        process_array[i].arr[z] = 4; //4 blocked
    }
}

for(i=0;i<num_processes;i++){
    int count_time =0;
    for(j=0;j<=process_array[i].completion_time;j++){

        if(process_array[i].arr[j]==1){
         printf("Time=%i\tp%d is ready\n",count_time,process_array[i].pid);

        }
        if(process_array[i].arr[j]==2){
        printf("Time=%i\tp%d is running\n",count_time,process_array[i].pid);

        }
        if(process_array[i].arr[j]==0){
           printf("Time=%i\tp%d not yet\n",count_time,process_array[i].pid);
        }
        if(process_array[i].arr[j]==4){
           printf("Time=%i\tp%d blocked\n",count_time,process_array[i].pid);
        }
        if(process_array[i].arr[j]==3){
           printf("Time=%i\tp%d finished\n",count_time,process_array[i].pid);
        }
    count_time++;

    }
    printf("\n");
}




free(completed_arr);
free(process_array);


}

int main(){

	processes P[10];
	int ch,n;
	do{
		printf("\n\n SIMULATION OF CPU SCHEDULING ALGORITHMS\n");
		printf("\n Options:");
		printf("\n 0. Enter process data for (FCFS & SJCF) other fun take it's data with itself");
		printf("\n 1. FCFS");
		printf("\n 2. SJF CPU");
		printf("\n 3. SJF IO");
		printf("\n 4. SJCF");
		printf("\n 5. MLFQ");
		printf("\n 6. Round Robin");
		printf("\n 7. Exit\n Select : ");
		scanf("%d",&ch);
		switch(ch){
			case 0:
				n=Data(P);
				break;
			case 1:
				FCFS(P,n);
				break;
			case 2:
                SJF_cpu();
				break;
			case 3:
                SJF_IO();
				break;
            case 4:
                SJCF(P,n);
				break;
			case 5:
                insert_process("first", 10);
                insert_process("second", 12);
                insert_process("third", 2);
                insert_process("Kareem", 40);
                insert_process("Mahmoud", 20);
                insert_process("Hamdy", 4);
                insert_process("Muhammed", 1);
                insert_process("Ammar", 35);
                while(1){
                    loopScheduler();
                }
				break;
			case 6:
                //RoundRobin();
				break;
			case 7:
			    exit(0);
		}
	}while(ch != 6);
	//getch();
	return 0;
}
