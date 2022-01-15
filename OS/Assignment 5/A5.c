#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define R 5
#define W 5

pthread_mutex_t wrt,mutex;   //mutex declarations
int rc=0,key=0;

void *writefun(void *ptr)        //writer function,only 1 writer can write at once
{
    int k=(int*)ptr;
    do{ 
        sleep(1);
        pthread_mutex_lock(&wrt);key++;       //lock on mutex for writer function
        printf("\nWriter %d is writing the value : %d",k,key);
        pthread_mutex_unlock(&wrt);
  
  }while(true);
 pthread_exit(0);
}
void *readfun(void *ptr)        //reader function,multiple readers can read when no writing thread
{

    int k=(int*)ptr;

    do
    {
        sleep(1);                  
        pthread_mutex_lock(&mutex);                  //lock mutex for resource of reader
        rc++; 
        if(rc==1) {pthread_mutex_lock(&wrt);}       //if rc==1 put lock on writer

        pthread_mutex_unlock(&mutex);              //unlock mutex

        printf("\nReader %d is reading the value : %d",k,key);
        pthread_mutex_lock(&mutex);   //lock mutex 
        rc--;                        //decrement reader count 

        if(rc==0) {pthread_mutex_unlock(&wrt);}   //if rc==0 unlock write
        pthread_mutex_unlock(&mutex);            //unlock mutex
    //sleep(1);
    }while(true);
    pthread_exit(0);
}





int main()
{
        pthread_t reader[R],writer[W];    //reader writer thread array.
        int i;

        pthread_mutex_init(&wrt,NULL);    //initialize mutex
        pthread_mutex_init(&mutex,NULL);

        for(i=0;i<R;i++){pthread_create(&reader[i],NULL,readfun,(void *)i);}
        for(i=0;i<W;i++){pthread_create(&writer[i],NULL,writefun,(void *)i);}    //thread creation and join

        for(i=0;i<R;i++){pthread_join(reader[i],NULL);}
        for(i=0;i<W;i++){pthread_join(writer[i],NULL);}


        pthread_mutex_destroy(&wrt);    //destroying threads
        pthread_mutex_destroy(&mutex);
        return(0);


}


