/*
 *
 * Victoria Byrka
 *
 * October 23, 2020
 *
 * Description: This program takes integers from a file, sorts them
 *              using threads, merges the threads, then outputs the 
 *              sorted array to a new file.
 *
 */

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 500

int globalArray[MAX_SIZE];
int globalResult[MAX_SIZE];

// Structure to pass data to threads
typedef struct{
  int starting_index;
  int ending_index;
}parameters;

void *sorter(void *params);
void *merger(void *params); 

// MAIN
int main(int argc, const char *argv[]){

  // Read input from file and add to an array using fgets
  FILE * inputFile;
  inputFile = fopen("IntegerList.txt", "r");
  char str[2000];
  fgets(str, 2000, inputFile);

  // Split the input into individual string tokens
  int count = 0;
  char *token;
  char *array[500];
  token = strtok(str, ","); 

  array[count] = token; // Add first token

  // While token is not NULL get next token and add to array
  while(token!=NULL){
    token = strtok(NULL, ",");
    count++;
    array[count] = token; // Add token to array
  }

  int i;
  int numOfInts = count + 1;
    
  // Convert each string token into an integer using atoi
  for(i = 0; i < count; i++){
    globalArray[i] = atoi(array[i]); // Add int to global array
  }

  // Starting, Middle, and Ending index numbers
  int n1 = 0;
  int n2 = numOfInts - 1;
  int mid = numOfInts/2;
  
  // Sorting thread 1 for first half of array
  parameters *sort1 = (parameters *)malloc(sizeof(parameters));
  sort1->starting_index = n1;
  sort1->ending_index = mid-1;
    
  // Sorting thread 2 for second half of array
  parameters *sort2 = (parameters *)malloc(sizeof(parameters));
  sort2->starting_index = mid;
  sort2->ending_index = n2;

  // Create thread 1
  pthread_t tid1;
  pthread_create(&tid1, NULL, sorter, sort1);

  // Create thread 2
  pthread_t tid2;
  pthread_create(&tid2, NULL, sorter, sort2);

  // Wait for threads to exit
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  
  // Thread 3 for merging 1 & 2
  parameters *merge1 = (parameters *)malloc(sizeof(parameters));
  merge1->starting_index = 0;
  merge1->ending_index = n2 - 2;

  // Create thread 3
  pthread_t tid3;
  pthread_create(&tid3, NULL, merger, merge1);

  // Wait
  pthread_join(tid3, NULL);

  // Open file to write to
  FILE *output;
  output = fopen("SortedIntegerList.txt", "w");

  int j;

  // Print sorted array with commas
  for(j=0; j<count; j++){
    fprintf(output, "%d", globalResult[j]);
    if(j != count - 1){
      fprintf(output, ",");
    }
  }

  fprintf(output, "\n");
  
  // Close writing to output file
  fclose(output);
  
  // Release allocated memory
  free(sort1);
  free(sort2);
  free(merge1);
  
  return 0;    
}

/* Function to sort the integers in ascending order
 * using BubbleSort. Information from:
 * https://www.geeksforgeeks.org/bubble-sort/
 */
void *sorter(void *params){

  // Set parameters for start and end of array
  int low = ((parameters *)params)->starting_index;
  int high = ((parameters *)params)->ending_index;
  
  int i, j, temp;

  // Iterate through array
  for(i = low; i < high; i++){
    // Iterate through thread
    for(j = low; j < high - i; j++){
      // If the current int is larger than the next int
      // we switch the numbers around
      if(globalArray[j] > globalArray[j + 1]){
	// Swap elements using a temporary holder
	temp = globalArray[j];
	globalArray[j] = globalArray[j+1];
	globalArray[j+1] = temp; 
      }
    }
  }

  int a;
  // Add sorted array to global result arra
  for(a = low; a < high + 1; a++){
    globalResult[a] = globalArray[a];
  }
  
  pthread_exit(0);
}

// Function to merge two  arrays together
void *merger(void *params){
  
  // Set parameters for start and end of array
  int low = ((parameters *)params)->starting_index;
  int high = ((parameters *)params)->ending_index + 1;

  int i, j, temp;

  // Iterate through array
  for(i = low; i < high; i++){
    // Iterate through thread
    for(j = low; j < high - i; j++){
      // If the current int is larger than the next int
      // we switch the numbers around
      if(globalResult[j] > globalResult[j+1]){
	// Swap elements using a temporary holder
        temp = globalResult[j]; 
        globalResult[j] = globalResult[j+1];
        globalResult[j+1] = temp; 
      }
    }
  }
  
  pthread_exit(0);
}
