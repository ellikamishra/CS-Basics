#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
#define MAX 20

int binarysearch(int arr[], int l, int r, int x) 
{ 
    while (l <= r) { 
        int m = l + (r - l) / 2; 
  
       
        if (arr[m] == x) 
            return m; 
  
        
        if (arr[m] < x) 
            l = m + 1; 
  
        
        else
            r = m - 1; 
    } 
  
    
    return -1; 
} 




int main(int argc,char* argv[],char* env[])
{
    int a[MAX]={0};
    int n,r,i;
    if(argc!=0)
    {
    for( i=1;i<argc;i++)
    {
        printf("%d",atoi(argv[i]));
        a[i]=atoi(argv[i]);
    }
    printf("\nEnter no. to search:");
    scanf("%d",&n);

    r=binarysearch(a,0,argc-1,n);

    if(r!=-1)
    {
        printf("\nElement found at %d",r);
    }

    else{
        
        printf("\nElement not existing");}
    }

    else
    {
        printf("\nInvalid args");
    }
    return 0;

}



