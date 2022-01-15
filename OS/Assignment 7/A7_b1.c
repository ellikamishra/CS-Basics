// C program to implement one side of FIFO 
// This side writes first, then reads 
#include <stdio.h> 
#include <string.h> 
#include <fcntl.h> 
#include <sys/stat.h> 
#include <sys/types.h> 
#include <unistd.h> 

int main() 
{ 
	int fd; 

	
	char * myfifo = "/tmp/myfifo";  // FIFO file path 

	
	mkfifo(myfifo, 0666);                  // Creating the named file(FIFO) ,mkfifo(<pathname>, <permission>) 

	char arr1[80], arr2[80]; 
	while (1) 
	{ 
		
		fd = open(myfifo, O_WRONLY);      // Open FIFO for write only 

		printf("\nEnter text to write\n");
		fgets(arr2, 80, stdin);          // Take an input arr2ing from user. 
		

		
		write(fd, arr2, strlen(arr2)+1);    // Write the input arr2ing on FIFO and close it 
		close(fd); 

		
		fd = open(myfifo, O_RDONLY);     // Open FIFO for Read only 

		
		read(fd, arr1, sizeof(arr1));    // Read from FIFO 

		
		printf("User2: %s\n", arr1);    // Print the read message 
		close(fd); 
	} 
	return 0; 
} 

