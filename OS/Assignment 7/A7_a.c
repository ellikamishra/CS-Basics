#include<stdio.h>
#include<unistd.h>
#include<string.h>
#define MSIZE 200



int main()
{
        FILE *f;
        char m1[MSIZE];              //m1 to first write data in
        char inbuf[MSIZE];           //inbuf to store read data
        char fname[MSIZE];
        //memset(inbuf,‘\0’,
        int p[2],pid,nbytes;        //p for file descriptor,pid for forking,nbytesd to store read/write byte count
        printf("Enter the file:\n");
        scanf("%s",fname);         //writing to file
        //scanf("%[^\t]s", m1);
        f=fopen(fname,"r");

        if(pipe(p)<0)              //error in pipe creation
        {   printf("Error\n");

        }

        pid=fork();               //fork to create child process
        if(pid==-1)
        {   printf("\nError");
        
        }


        if(pid==0){                        //reading in child process from file
            printf("\nChild called");
            nbytes=read(p[0], inbuf, MSIZE);
            printf("read %d words\n",nbytes);
            printf("% s\n", inbuf); 
        }    

        else{                                        //writing in parent process to file
            printf("\nParent called");
            fscanf(f, "%[^\t]s", m1);
            nbytes=write(p[1],m1,MSIZE);
            fclose(f);
            printf("written %d words\n",nbytes);
        }



        return 0;

}

