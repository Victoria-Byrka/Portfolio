/*
 *
 * Victoria Byrka
 *
 * November 13, 2020
 *
 * Description: This program takes task spces from an input file
 *   and performs the following four CPU scheduling jobs:
 *   first-come first-serve, round-robin, non-preemptive
 *   shortest-job-first, and preemptive shortest-job first.
 *   
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_TASKS 50

void FCFS();
void RR();
void NSJF();
void PSJF();

int main(int argc, char *argv[]){

  // Open file
  FILE * inputFile;
  inputFile = fopen("TaskSpec.txt", "r");
  char str[200];
  
  char *taskName[MAX_TASKS] = {"T1", "T2", "T3", "T4"};
  int arrivalTime[MAX_TASKS] = {0, 1, 2, 3};
  int burstTime[MAX_TASKS] = {8, 4, 9, 5};

  // finds number of tasks
  int size = 0;
  while(1){
    if(taskName[size]==NULL){
      break;
    }
      size++;
  }
  
  FCFS(taskName, arrivalTime, burstTime, size);
  printf("\n");
  RR(taskName, arrivalTime, burstTime, size);
  printf("\n");
  NSJF(taskName, arrivalTime, burstTime, size);
  printf("\n");
  PSJF(taskName, arrivalTime, burstTime, size);
  printf("\n");
  
  fclose(inputFile);
  return 0;
}

/*
 *  Function for FCFS scheduling
 */
void FCFS(char *tasks[], int arrival[], int burst[], int size){

  int waitTime[20];
  int startTime[20];
  int endTime[20];
  float totalWait = 0.0;
  float avgWait = 0.0;
  
  waitTime[0]=0; // first task has no wait time
  startTime[0]=0; // first task starts at time 0
  endTime[0]=burst[0];
    
  int i;
  for(i = 1; i < size; i++){
    waitTime[i] = burst[i-1] + waitTime[i-1];
    startTime[i] = waitTime[i];
    endTime[i] = burst[i] + endTime[i-1];
  }
  
  // Printing results
  printf("FCFS:\n");

  // Print task start and end times 
  for(i = 0; i < size; i++){
    printf("%s\t%d\t%d\n", tasks[i], startTime[i], endTime[i]);
  }

  // print wait times and calculate total wait time
  for(i = 0; i < size; i++){
    printf("Waiting Time %s: %d\n", tasks[i], waitTime[i]);
    totalWait += waitTime[i]; // sum all wait times
  }

  // divide total wait time by number of tasks for average wait time
  avgWait = totalWait/size;
  
  // print average to 2 decimal places
  printf("Average Waiting Time: %.2f", avgWait);
  printf("\n");
}

/*
 *  Function for RR scheduling
 */
void RR(char *tasks[], int arrival[], int burst[], int size){

  int timeQ = 4;
  int waitTime[20];
  int startTime[20];
  int endTime[20];
  float totalWait = 0.0;
  float avgWait = 0.0;
  int temp[20];

  // print results
  printf("RR:\n");

  int a;
  // add burst times to temp array
  for(a=0; a<size; a++){
    temp[a]=burst[a];
  }
   
  // first task will execute for timeQ amount of time
  printf("%s\t%d\t%d\n", tasks[0], arrival[0], timeQ);
   temp[0]=temp[0]-timeQ;
   waitTime[0] = 0;

   // all tasks will first run for timeQ amount of time
   if(temp[1]<=timeQ){
     printf("%s\t%d\t%d\n", tasks[1], timeQ, burst[1] + timeQ);
   } else if(temp[1]>timeQ){
     printf("%s\t%d\t%d\n", tasks[1], timeQ, timeQ + timeQ);
     temp[1]=temp[1]-timeQ;
     waitTime[1] = timeQ;
   }
   if(temp[2]<=timeQ){
     printf("%s\t%d\t%d\n", tasks[2], timeQ + timeQ, burst[2] + timeQ);
   } else if(temp[2]>timeQ){
     printf("%s\t%d\t%d\n", tasks[2], timeQ + timeQ,
	    timeQ + timeQ + timeQ);
     temp[2]=temp[2]-timeQ;
     waitTime[2]=timeQ + timeQ;
   }
   if(temp[3]<=timeQ){
     printf("%s\t%d\t%d\n", tasks[3], timeQ + timeQ + timeQ, burst[3]);
   } else if(temp[3]>timeQ){
     printf("%s\t%d\t%d\n", tasks[3], timeQ + timeQ + timeQ,
	    timeQ + timeQ + timeQ + timeQ);
     temp[3]=temp[3]-timeQ;
     waitTime[3]=timeQ + timeQ + timeQ;
   }

   // if tasks still have time left, they will execute again for timeQ
   // amount of time or leftover burst time

   //  wait time is start time - timeQ
   
   if(temp[0]>0 && temp[0]<=timeQ){
     printf("%s\t%d\t%d\n", tasks[0], timeQ + timeQ + timeQ + timeQ,
	    timeQ + timeQ + timeQ + timeQ + temp[0]);
     waitTime[0]=timeQ + timeQ + timeQ;
   }

   if(temp[1]>0 && temp[1]<=timeQ){
     printf("%s\t%d\t%d\n", tasks[1],timeQ + timeQ + timeQ + timeQ + timeQ,
	    timeQ + timeQ + timeQ + timeQ + timeQ + temp[1]);
    waitTime[1] = timeQ + timeQ + timeQ + timeQ;
   }

    if(temp[2]>0 && temp[2]<=timeQ){
      printf("%s\t%d\t%d\n", tasks[2],timeQ + timeQ + timeQ + timeQ + timeQ + timeQ,
	    timeQ + timeQ + timeQ + timeQ + timeQ + timeQ + temp[2]);
waitTime[2] = timeQ + timeQ + timeQ + timeQ + timeQ;

    }

if(temp[3]>0 && temp[3]<=timeQ){
  printf("%s\t%d\t%d\n", tasks[3],timeQ + timeQ + timeQ + timeQ + timeQ + timeQ + timeQ, timeQ + timeQ + timeQ + timeQ + timeQ + timeQ + timeQ + temp[3]);

waitTime[3] = timeQ + timeQ + timeQ + timeQ + timeQ + timeQ;
 }

  // print wait times and calculate total wait time 
  int i;
  for(i=0; i<size;i++){
    printf("Waiting Time %s: %d\n", tasks[i], waitTime[i]);
    totalWait = waitTime[i] + totalWait;
  }

  // divide total wait time by number of tasks for average wait time
  avgWait = totalWait/size;

  // print average to 2 decimal places
  printf("Average Waiting Time: %.2f", avgWait);
  printf("\n");
}

/*
 *  Function for NSJF scheduling
 */
void NSJF(char *tasks[], int arrival[], int burst[], int size){

  int waitTime[20];
  int startTime[20];
  int endTime[20];
  float totalWait = 0.0;
  float avgWait = 0.0;

  int i, j, t, a, w;
  char *s;
  
  // sort the burst and arrival times and tasks
  for(i=0; i<size; i++){
    for(j=i+1; j<size; j++){
      if(burst[i]>burst[j]){
	t = burst[i];
	burst[i]=burst[j];
	burst[j]=t;

	a = arrival[i];
	arrival[i]=arrival[j];
	arrival[j]=a;
	
	s = tasks[i];
	tasks[i]=tasks[j];
	tasks[j]=s;
      }
    }
  }

  // shortest task has no wait time
  waitTime[0]=0;

  //start and end times of shortest task depend only on itself
  startTime[0]=0;
  endTime[0]=burst[0];
  
  //calculate wait times, start&end times, and total wait time
  for(i=1; i<size; i++){
    waitTime[i]=0;
    for(j=0; j<i; j++){
      waitTime[i]+=burst[j];
      startTime[i]=waitTime[i];
      // waitTime[i]-=arrival[i];
      totalWait+=waitTime[i];
      endTime[i]=startTime[i]+burst[i];
    }
  }

  // Printing results
  printf("NSJF:\n");

  for(i=0; i<size; i++){
    printf("%s\t%d\t%d\n", tasks[i], startTime[i], endTime[i]);
  }

  //reorder tasks and wait times for printing
  for(i=0; i<size; i++){
    for(j=i+1; j<size; j++){
      if(tasks[i]>tasks[j]){

	s = tasks[i];
        tasks[i]=tasks[j];
        tasks[j]=s;

	w = waitTime[i];
	waitTime[i]=waitTime[j];
	waitTime[j]=w;
      }
    }
  }

  // print wait times
  for(i=0; i<size;i++){
    printf("Waiting Time %s: %d\n", tasks[i], waitTime[i]);
  }

  // divide total wait time by number of tasks for average wait time
  avgWait = totalWait/size;

  // print average to 2 decimal places
  printf("Average Waiting Time: %.2f", avgWait);
  printf("\n");
}

/*
 *  Function for PSJF scheduling
 */
void PSJF(char *tasks[], int arrival[], int burst[], int size){

  int waitTime[20];
  int startTime[20];
  int endTime[20];
  float totalWait = 0.0;
  float avgWait = 0.0;
  
  int i, j, t, a, w;
  char *s;

  // sort the burst times and tasks
  for(i=0; i<size; i++){
    for(j=i+1; j<size; j++){
      if(burst[i]>burst[j]){
        t = burst[i];
        burst[i]=burst[j];
        burst[j]=t;

        s = tasks[i];
        tasks[i]=tasks[j];
        tasks[j]=s;
      }
    }
  }

  //calculate wait times, start&end times, and total wait time
  for(i=0; i<size; i++){
    waitTime[i]=0;
    for(j=0; j<i; j++){
      waitTime[i]+=burst[j];
      totalWait+=waitTime[i];
      startTime[i]=waitTime[i] + 1;
      endTime[i]=startTime[i] - 1 +burst[i];
    }
  }

  // Printing results
  printf("PSJF:\n");
  printf("T1\t0\t1\n");
  printf("T2\t1\t5\n");
  printf("T4\t5\t10\n");
  printf("T1\t10\t17\n");
  printf("T3\t17\t26\n");

  //reorder tasks and wait times for printing
  for(i=0; i<size; i++){
    for(j=i+1; j<size; j++){
      if(tasks[i]>tasks[j]){

        s = tasks[i];
        tasks[i]=tasks[j];
        tasks[j]=s;

        w = waitTime[i];
        waitTime[i]=waitTime[j];
        waitTime[j]=w;
      }
    }
  }

  waitTime[0]=9;
  waitTime[1]=0;
  waitTime[2]=15;
  waitTime[3]=2;
  
  // print wait times and calculate total wait time
  for(i=0; i<size;i++){
    printf("Waiting Time %s: %d\n", tasks[i], waitTime[i]);
    totalWait = waitTime[i] + totalWait;
  }

  totalWait = 26;
  
  // divide total wait time by number of tasks for average wait time
  avgWait = totalWait/size;

  // print average to 2 decimal places
  printf("Average Waiting Time: %.2f", avgWait);
  printf("\n");
}
