/////////// MIT License ////////////
/// This is a scheduler simulator ///
#include <stdlib.h>
#include <stdio.h>

typedef  enum state {
	running,
	yet,
	ready,
	blocked,
	finished
} State;

struct Process
{
    int id;
    char *name; 
		int q;
		int ETA;
		int time;
		State s;
		struct Process *next;
};
void init_process (struct Process *, char *name, int ETA );
void display();
void insert_process(char *name, int ETA);
void loopScheduler();
void printf_t(char*);
void printf_t_d(int i);
void p_splitter();
void p_splitter_line();
void prefix();
sleep();
/// global variables ///
int id_counter = 0;
struct Process *head = NULL;
const int NQUEUES = 4;
int queueTime[3] = {5, 25, 55} ;

int main()
{
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
}
void loopScheduler(){
	display();
	int highestQ = 1;

	struct Process *current = head;
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

void init_process (struct Process *new, char *name, int ETA){
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
   struct Process *new = (struct Process*) malloc(sizeof(struct Process));

	 init_process(new, name, ETA );
	
	
   //point it to old first node
   new->next = head;
	
   //point first to new first node
   head = new;
}

void display(){
	struct Process *current = head;
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
