// C program to implement one side of FIFO 
// This side reads first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd1; 

	   
	char * myfifo = "/tmp/myfifo";   // FIFO file path 

	
	mkfifo(myfifo, 0666);            // Creating the named file(FIFO) 
	                                 // mkfifo(<pathname>,<permission>) 

	char str1[80], str2[80]; 
	while (1) 
	{ 
		
		fd1 = open(myfifo,O_RDONLY);    
		read(fd1, str1, 80); 

		                         
		printf("User1: %s\n", str1);              // Printing the read string and close 
		close(fd1); 

		
		
		fd1 = open(myfifo,O_WRONLY);       //  opening in write mode and write string taken from user. 
		printf("\nEnter text to write\n");
		fgets(str2, 80, stdin); 
		write(fd1, str2, strlen(str2)+1); 
		close(fd1);                        
	} 
	return 0; 
} 

