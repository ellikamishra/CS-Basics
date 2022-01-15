//shared memory using to programs to read,write struct values.

#include <stdio.h> 
#include <sys/ipc.h> 
#include <sys/shm.h> 
// #include <cstdio> 


typedef struct user
{  char name[20];
   
   float value;
   
} user;
int main() 
{ 
	
	key_t key = ftok("shmfile",65); // ftok to generate unique key 
    int k;
    float val;
	
	int shmid = shmget(key,1024,0666|IPC_CREAT); // shmget returns an identifier in shmid 

	 
	user *u= (user*) shmat(shmid,(void*)0,0); // shmat to attach to shared memory

	
	printf("Data read in memory: %s %f\n",u->name,u->value); 
	//detach from shared memory 
	printf("\nEnter choice\n1.Withdraw\n2.Deposit\n3.Exit");
	scanf("%d",&k);
	switch(k)
	{
		case 1:
			printf("\nEnter value to withdraw");
			scanf("%f",&val);
			u->value=u->value-val;
			break;
		case 2:
			printf("\nEnter value to deposit");
			scanf("%f",&val);
			u->value=u->value+val;
		case 3:
			break;
		
	
	
	}
	printf("Data written in memory: %s %f\n",u->name,u->value); 
	shmdt(u); 
	
	// destroy the shared memory 
	shmctl(shmid,IPC_RMID,NULL); 
	
	return 0; 
} 

