#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define R 5
#define W 5


sem_t wrt,mutex;
int rc=0,key=0;

void *writefun(void *ptr)
{
    int k=(int*)ptr;
    do{ 
        sleep(rand()%3);
        sem_wait(&wrt);key++;  
        printf("\nWriter %d is writing the value : %d",k,key);
        sem_post(&wrt);
        
    }while(true);
    pthread_exit(0);
}
    void *readfun(void *ptr)
    {

    int k=(int*)ptr;

    do{
        sleep(rand()%4);
        sem_wait(&mutex);
        rc++;
        if(rc==1) {sem_wait(&wrt);}

        sem_post(&mutex);

        printf("\nReader %d is reading the value : %d",k,key);
        sem_wait(&mutex);
        rc--;

        if(rc==0) {sem_post(&wrt);}
        sem_post(&mutex);
        //sleep(1);
    }while(true);
    pthread_exit(0);
}





int main()
{
    pthread_t reader[R],writer[W];
    int i;

    sem_init(&wrt,1,1);
    sem_init(&mutex,1,1);
    for(i=0;i<R;i++){pthread_create(&reader[i],NULL,readfun,(void *)i);}
    for(i=0;i<W;i++){pthread_create(&writer[i],NULL,writefun,(void *)i);}
    for(i=0;i<R;i++){pthread_join(reader[i],NULL);}
    for(i=0;i<W;i++){pthread_join(writer[i],NULL);}


    sem_destroy(&wrt);
    sem_destroy(&mutex);
    return(0);


}