#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define max 10


sem_t full,empty;    //semaphore declaration full
pthread_mutex_t mutex;  //thread mutex 
int count =0,a[5];     //buffer size set to 5,initial count 0


void *producer(void *arg)      //producer function
{
  int n=(int*)arg;

  while(true)
{
    sem_wait(&empty);             //wait for buffer to get empty
    pthread_mutex_lock(&mutex);   //lock the mutex thread to resources are used in a mutual exclusive manner.
    if(count>=5) printf("\nFull");

    else{
    
    a[count]=rand()%100;
    printf("\nProducer %d produced item : %d",n,a[count]);count++;
    printf("\nBuffer elements:\t");
    for(int i=0;i<count;i++) printf("%d\t",a[i]);
    printf("\n");
    
    }
    
    pthread_mutex_unlock(&mutex);  //release lock om mutex 
    
    sem_post(&full);  //release semaphore 
    //sleep(1);
  }

  pthread_exit(0);

}


void *consumer(void *arg)
{
int n=(int*)arg;

  while(true)
  {
      sem_wait(&full);  //wait until buffer is filled with some value
      pthread_mutex_lock(&mutex); //lock mutex to ensure mutual exclusive resource use 
      
      if(count<=0)printf("\nBuffer is empty...");
      else{
      count--;
      printf("\nConsumer%d consumed item : %d",n,a[count]);}
      printf("\nBuffer elements:\t");
      for(int i=0;i<count;i++) printf("%d\t",a[i]);
      printf("\n");
      pthread_mutex_unlock(&mutex);  //release lock om mutex
      
      sem_post(&empty);  //release semaphore
      sleep(rand()%2);   //sleep added to include randomness 
      }

    pthread_exit(0);
}



int main()
{

    int p,c;
    pthread_t pth[max],cth[max];

    pthread_mutex_init(&mutex,NULL);  //initialising semaphore and mutex
    sem_init(&full,0,0);
    sem_init(&empty,0,5);

    printf("\nenter the num. of producers and consumers: ");
    scanf("%d%d",&p,&c);

    for(int i=0;i<p;i++) pthread_create(&pth[i],NULL,producer,(void *)i);
    for(int i=0;i<c;i++) pthread_create(&cth[i],NULL,consumer,(void *)i);

    for(int i=0;i<p;i++) pthread_join(&pth[i],NULL);
    for(int i=0;i<c;i++) pthread_join(&cth[i],NULL);


    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);
    return(0);
}
/*Consumer3 consumed item : 83ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 5 6

Producer 0 produced item : 83
Buffer elements:	83	

Producer 1 produced item : 77
Buffer elements:	83	77	

Producer 2 produced item : 93
Buffer elements:	83	77	93	

Producer 3 produced item : 86
Buffer elements:	83	77	93	86	

Producer 4 produced item : 49
Buffer elements:	83	77	93	86	49	

Consumer1 consumed item : 49
Buffer elements:	83	77	93	86	

Consumer0 consumed item : 86
Buffer elements:	83	77	93	

Consumer3 consumed item : 93
Buffer elements:	83	77	

Consumer4 consumed item : 77
Buffer elements:	83	

Producer 3 produced item : 63
Buffer elements:	83	63	

Consumer2 consumed item : 63
Buffer elements:	83	

Consumer5 consumed item : 83
Buffer elements:	

Producer 4 produced item : 72
Buffer elements:	72	

Consumer2 consumed item : 72
Buffer elements:	

Producer 4 produced item : 68
Buffer elements:	68	

Producer 0 produced item : 29
Buffer elements:	68	29	

Consumer1 consumed item : 29
Buffer elements:	68	

Consumer3 consumed item : 68
Buffer elements:	

Producer 3 produced item : 23
Buffer elements:	23	

Consumer5 consumed item : 23
Buffer elements:	
^C
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 2 3

Producer 0 produced item : 83
Buffer elements:	83	

Producer 1 produced item : 77
Buffer elements:	83	77	

Consumer0 consumed item : 77
Buffer elements:	83	

CConsumer1 consumed item : 83
Buffer elements:	
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 1 2
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 1 1

Producer 0 produced item : 83
Buffer elements:	83	
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 1 1

Producer 0 produced item : 83
Buffer elements:	83	

Consumer0 consumed item : 83
Buffer elements:	

Producer 0 produced item : 15
Buffer elements:	15	

Consumer0 consumed item : 15
Buffer elements:	

Producer 0 produced item : 86
Buffer elements:	86	

Producer 0 produced item : 49
Buffer elements:	86	49	

Producer 0 produced item : 62
Buffer elements:	86	49	62	

Consumer0 consumed item : 62
Buffer elements:	86	49	

Consumer0 consumed item : 49
Buffer elements:	86	

Producer 0 produced item : 63
Buffer elements:	86	63	

Producer 0 produced item : 40
Buffer elements:	86	63	40	

Consumer0 consumed item : 40
Buffer elements:	86	63	

Consumer0 consumed item : 63
Buffer elements:	86	

Consumer0 consumed item : 86
Buffer elements:	

Producer 0 produced item : 68
Buffer elements:	68	

Consumer0 consumed item : 68
Buffer elements:	

Producer 0 produced item : 82
Buffer elements:	82	

Consumer0 consumed item : 82
Buffer elements:	
^C
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 2 3

Producer 0 produced item : 83
Buffer elements:	83	

Producer 1 produced item : 77
Buffer elements:	83	77	

Consumer0 consumed item : 77
Buffer elements:	83	

Consumer1 consumed item : 83
Buffer elements:	

Producer 0 produced item : 86
Buffer elements:	86	

Consumer2 consumed item : 86
Buffer elements:	

Producer 0 produced item : 21
Buffer elements:	21	

Consumer0 consumed item : 21
Buffer elements:	

Producer 1 produced item : 90
Buffer elements:	90	

Consumer1 consumed item : 90
Buffer elements:	

Producer 0 produced item : 26
Buffer elements:	26	

Consumer2 consumed item : 26
Buffer elements:	

Producer 0 produced item : 72
Buffer elements:	72	

Producer 0 produced item : 11
Buffer elements:	72	11	

Producer 0 produced item : 67
Buffer elements:	72	11	67	
^C
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 4 5

Producer 0 produced item : 83
Buffer elements:	83	

Producer 3 produced item : 77
Buffer elements:	83	77	

Producer 1 produced item : 93
Buffer elements:	83	77	93	

Producer 2 produced item : 86
Buffer elements:	83	77	93	86	

Consumer1 consumed item : 86
Buffer elements:	83	77	93	

Consumer0 consumed item : 93
Consumer0 consumed item : 93
Buffer elements:	83	77	
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ ./a.out

enter the num. of producers and consumers: 1 1

Producer 0 produced item : 83
Buffer elements:	83	

Consumer0 consumed item : 83
Buffer elements:	

Producer 0 produced item : 15
Buffer elements:	15	

Consumer0 consumed item : 15
Buffer elements:	

Producer 0 produced item : 86
Buffer elements:	86	

Producer 0 produced item : 49
Buffer elements:	86	49	

Producer 0 produced item : 62
Buffer elements:	86	49	62	

Consumer0 consumed item : 62
Buffer elements:	86	49	
^C
ellika@ellika-HP-Laptop-15s-du1xxx:~/sl2/Sl2$ 
*/
