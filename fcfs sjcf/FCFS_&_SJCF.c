#include<stdio.h>
#include<stdlib.h>
#include<string.h>

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
	processes temp[10];
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
        temp[i].completion_time = temp[i - 1].completion_time + temp[i].running_time;
        temp[i].waiting_time = (temp[i - 1].running_time + temp[i - 1].arrival_time + temp[i-1].waiting_time) - temp[i].arrival_time;
        temp[i].turnarround_time = (temp[i].waiting_time + temp[i].running_time);
        sumw+=temp[i].waiting_time;
        sumt+=temp[i].turnarround_time;
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
    
	int i,t_total=0,tcurr,b[10],min_at,j,x,min_bt;
	int sumw=0,sumt=0;
	float avgwt=0.0,avgta=0.0;
	processes temp[10],t;

	for(i=0;i<n;i++){
		temp[i]=P[i];
		t_total+=P[i].running_time;
	}

	FCFS_sort(temp,n);

	for(i=0;i<n;i++)
		b[i] = temp[i].running_time;

	i=j=0;
	printf("\n GANTT CHART\n\n %d %s",i,temp[i].name);
	for(tcurr=0;tcurr<t_total;tcurr++){

		if(b[i] > 0 && temp[i].arrival_time <= tcurr)
			b[i]--;

		if(i!=j)
			printf(" %d %s",tcurr,temp[i].name);

		if(b[i]<=0 && temp[i].flag != 1){

			temp[i].flag = 1;
			temp[i].waiting_time = (tcurr+1) - temp[i].running_time - temp[i].arrival_time;
			temp[i].turnarround_time = (tcurr+1) - temp[i].arrival_time;
			sumw+=temp[i].waiting_time;
			sumt+=temp[i].turnarround_time;
		}
		j=i;	min_bt = 999;
		for(x=0;x<n;x++){

			if(temp[x].arrival_time <= (tcurr+1) && temp[x].flag != 1){

				if(min_bt != b[x] && min_bt > b[x]){
					min_bt = b[x];
					i=x;
				}
			}
		}

	}
	printf(" %d",tcurr);
	avgwt = (float)sumw/n;	avgta = (float)sumt/n;
	printf("\n\n Average waiting time = %0.2f\n Average turn-around = %0.2f.",avgwt,avgta);
}


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
				FCFS(P,n);
				break;
			case 2:

				break;
			case 3:
                SJCF(P,n);
				break;
			case 4:

				break;
			case 5:

				break;
			case 6:
			    exit(0);
		}
	}while(ch != 6);
	//getch();
	return 0;
}
