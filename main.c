#include <stdio.h>
#include <stdlib.h>

typedef struct list {
  int ID_proc;
  int est_exec_time;
  int arr_time;
  int priority;
  struct list* next;
}list;

typedef struct Tuple {
  list* liste;
  list* proc;
}Tuple;

typedef struct map {
	int ID_proc;
	int time;
}map;

list* create_node(int ID_proc, int est_exec_time, int arr_time, int priority) {
  list* node = (list*)malloc(sizeof(list));
  node -> ID_proc = ID_proc;
  node -> est_exec_time = est_exec_time;
  node -> arr_time = arr_time;
  node -> priority = priority;
  node -> next = NULL;
	return node;
}

list* push(list* head, list* process){
  list* temp = head;
  if(temp == NULL){
    return process;
  }
  while(temp -> next != NULL){
    temp = temp -> next;
  }
  temp -> next = process;
  return head;
}

Tuple unshift(list* head){
	Tuple a;
	list* nxt = head -> next;
	a.liste = nxt;
	head -> next = NULL;
	a.proc = head;
  return a;
}

void round_robin(list* head, int nofprocess) {
	int quantum;
	int time = 0;
	printf("Quantum = ");
	scanf("%d", &quantum);
	float moy = 0;
	map times[nofprocess];
	int i = 0;
	while(head != NULL){
		if(head -> est_exec_time < quantum){

			printf("[%d - %d]: %d, remaining exec time: %d, ", time, time + (head -> est_exec_time), head -> ID_proc, 0);
			print(head);
			time += head -> est_exec_time;

			times[i].ID_proc = head->ID_proc;
			times[i].time = time;
			moy += time;
			i++;

			Tuple a = unshift(head);
			head = a.liste;
			free(a.proc);

		}else{
			printf("[%d - %d]: %d", time, time + quantum, head -> ID_proc);
			head -> est_exec_time -= quantum;
			printf(", remaining exec time: %d, ", head -> est_exec_time);
			print(head);

			times[i].ID_proc = head->ID_proc;

			time += quantum;
			Tuple a = unshift(head);
			head = a.liste;

			if(a.proc -> est_exec_time > 0) head = push(head, a.proc);
			else {
				moy += time;
				times[i].time = time;
				i++;
				free(a.proc);
			}
		}
	}
	printf("Respone time: ");
	for(int j = 0; j < nofprocess; j++){
		printf("%d -> %d   ", times[j].ID_proc, times[j].time);
	}
	printf("\nAverage response time: %f\n", moy / nofprocess);
}

void print(list* head) {
	list* temp = head;
	printf("process list: [ ");
	while(temp != NULL){
		printf("%d ", temp -> ID_proc);
		temp = temp -> next;
	}
	printf("]\n");
}

int main()
{
  int nofprocess;
  list* process_list = NULL;

  printf("Number of processes: ");
  scanf("%d", &nofprocess);
  for(int i = 0; i < nofprocess; i++){
    int pid, exectime, arrtime, priority;
    printf("Process id: ");
    scanf("%d", &pid);
    printf("Estimated execution time: ");
    scanf("%d", &exectime);

		list* newNode = create_node(pid, exectime, arrtime, priority);
		process_list = push(process_list, newNode);
  }

	round_robin(process_list, nofprocess);
	return 0;
}
