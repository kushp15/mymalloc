#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mymalloc.h"

int main(int argc, char**argv){

    // Compling 5 task and running 50 times. 
    double time_spent[5][50] = {{0.0}};
    int count = 0;

    while(count!=50){

    /*
    - TASK-1
    malloc() and immediately free() a 1-byte chunk, 120 times. Recording the time took each time 
    running the task for 50 times. 
    */
    clock_t start = clock();
    for(int i=0;i<120;i++){
        char *p = malloc(1);
        free(p);
    }

    clock_t end = clock();
    time_spent[0][count] += (double)(end - start) / CLOCKS_PER_SEC;


    /*
    - TASK-2 
    Use malloc() to get 120 1-byte chunks, storing the pointers in an array, 
    then use free() to deallocate the chunks. 
    */
    start = clock(); 
    char *q[120];
    for(int i=0;i<120;i++){
        q[i] = malloc(1);
    }
    for(int i=0;i<120;i++){
        free(q[i]);
    }
    end = clock(); 
    time_spent[1][count] += (double)(end - start) / CLOCKS_PER_SEC;


    /*
    TASK-3 
    Randomly choose between
      •Allocating a 1-byte chunk and storing the pointer in an array
      •Deallocating one of the chunks in the array (if any)
    Repeat until you have called malloc() 120 times, then free all remaining allocated chunks.
    */
    start = clock();
    int mCount = 0;
    int i = 0;
    char *a[120];
    while(mCount!=120){
    srand(time(NULL));
    bool randBool = rand() & 1; 
        if(randBool){ 
            a[mCount] = malloc(1);
            i++;
            mCount++;
        }
        else {
            if(mCount>0)
            free(a[mCount]); 
        }
    }
    while(i > 0){ 
        free(a[i-1]);
        i--;
    }

    end = clock();

    time_spent[2][count] += (double)(end - start) / CLOCKS_PER_SEC;


	/*TASK-4
        1) Allocating 120 chunks at size 5.
        2) From 0 to 59, First free chunk and then again malloc() at size 5
        3) From 60 to 120, First free chunk and then again malloc() at size 8
        4) Free all memory 
    */ 
	start = clock();

    char *kush[120];
	for(int i = 0; i < 120; i++){
		kush[i] = malloc(5); 
	}
	for(int i = 0; i < 60; i++){
        if (i%2 == 0){
            free(kush[i]);
            kush[i] = malloc(10);
        }
	}
    for(int i =60; i<120; i++){
        if (i%2 == 0){
            free(kush[i]) ;
            kush[i] = malloc(8);
        }
    }
	for(int i=0; i< 120; i++){
        free(kush[i]);
    }
	end = clock();
	time_spent[3][count] += (double)(end - start) / CLOCKS_PER_SEC;


	//TASK-5 
    /*
        First, Allocating the chunks with the different sizes, free them separately. 
    */
	start = clock();
	
    char *adi[120];
	for(int i = 0; i < 120; i++){
        if((i%3 == 0) || (i%5 == 0))  
            adi[i] = malloc(2);
        else
            adi[i] = malloc(4);
	}
	for(int i = 0; i < 30; i++) {
		free(adi[i]);
	}
    for(int i = 30; i < 90; i++) {
		free(adi[i]);
	}
    for(int i = 90; i < 120; i++) {
		free(adi[i]);
	}
	end = clock();
	time_spent[4][count] += (double)(end - start) / CLOCKS_PER_SEC;


    count++; 
}
	
    // Output

	printf("\n  %-4s|  %-10s  |  %-10s  |  %-10s |  %-10s|  %-10s","No","Task-1","Task-2","Task-3","Task-4","Task-5");
	for(int j=0;j<50;j++){
		printf("\n  %-4d|  %-10.8f  |  %-10.8f  |  %-10.8f | %-10.8f | %-10.8f",j+1,time_spent[0][j],time_spent[1][j],time_spent[2][j], time_spent[3][j], time_spent[4][j]);
	}
    double sumTaskTime[5]={0.0};
    double averageTaskTime[5];
    for(int i=0;i<5;i++){
        for(int j=1;j<50;j++){
            sumTaskTime[i] +=  time_spent[i][j]; 
        }
        averageTaskTime[i] = sumTaskTime[i]/50; 
    }
    // Average for each task took
    printf("\n\n\nAverage time (seconds) took by each task: \n\n");
    for(int i=1; i<=5; i++){
        printf("Task %-2dtook avg time = %-10.10f s\n",i, averageTaskTime[i-1]);
    }
    printf("\n\nTotal MEMORY SIZE IS %d bytes\n", MEMORY_SIZE);
    return EXIT_SUCCESS;
}