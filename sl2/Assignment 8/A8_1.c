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
	 
	key_t key = ftok("shmfile",65);   // ftok to generate unique key
    user *u;
	
	int shmid = shmget(key,1024,0666|IPC_CREAT); // shmget returns an identifier in shmid 

	
	u = (user*) shmat(shmid,(void*)0,0);   // shmat to attach to shared memory 

	printf("Write Data : "); 
	printf("Enter user info\nName:\n");
	scanf("%s",u->name);
	printf("Enter savings\n");
	scanf("%f",&u->value);

	printf("Data written in memory: %s %f\n",u->name,u->value); 
	
	
	shmdt(u);   //detach from shared memory 
	
	return 0; 
} 

