#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>
#define P 5
#define N 1
sem_t chopstick[P];                          //declare chopstick semaphores equal to no. of philosphers

void Philosopher(void *ptr)
{
        int i;
        i=(int*)ptr;
        do{
                printf("\nPhilosopher %d is thinking ....",i);
                sem_wait(&chopstick[i]);                                         //wait signal to ith chopstick semaphore as philospher thinks
                printf("\nPhilosopher %d picked up the left chopstick ....",i);
                sem_wait(&chopstick[(i+1)%P]);//P=5;
                printf("\nPhilosopher %d picked up the right chopstick ....",(i+1)%P);   //philospher picks left and rigth with lock to i+1/P chopstick
                printf("\nPhilosopher %d start eating ....",i);//sleep(rand()%i);
                sem_post(&chopstick[i]);
                printf("\nPhilosopher %d put down left chopstick ....",i);               //releasing the chopsticks with post
                sem_post(&chopstick[(i+1)%P]);
                printf("\nPhilosopher %d put down right chopstick ....",(i+1)%P);
                printf("\nPhilosopher %d finished eating and starts thinking again....",i);
                pthread_exit(0);
        }while(true);


}

int main(){

        pthread_t thread[P];int i;       //thread array declaration

        for(i=0;i<P;i++)
        {sem_init(&chopstick[i],0,1);}    //initialsing all semaphores

        for(i=0;i<P;i++){pthread_create(&thread[i],NULL,Philosopher,(void *)i);} //creation of thread and joining
        for(i=0;i<P;i++){pthread_join(thread[i],NULL);}

        for(i=0;i<P;i++){sem_destroy(&chopstick[i]);}        //destrying semaphores
        return 0;
}
