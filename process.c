
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h>  //Header file for sleep(). man 3 sleep for details. 
#include <pthread.h> 
  
// A normal C function that is executed as a thread  
// when its name is specified in pthread_create() 
void *thread1(void *vargp)
{ 
    int i = 9;
    while(i--){
        printf("THREAD 1\n");
        sleep(1);
    }
    return NULL; 
} 
void *thread2(void *vargp)
{ 
    int i = 9;
    while(i--){
        printf("THREAD 2\n");
        sleep(1);
    }
    return NULL; 
} 
   
int main() 
{ 
    pthread_t thread_id1, thread_id2; 
    printf("Before Thread\n"); 
    pthread_create(&thread_id1, NULL, thread1, NULL); 
    pthread_create(&thread_id2, NULL, thread2, NULL); 
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);
    printf("After Thread\n"); 
    exit(0); 
}