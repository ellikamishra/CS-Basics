#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<pthread.h>#include<stdlib.h>
#include<unistd.h>
#include<ctype.h>
//#include <cstdlib>
#define MAX 20
// Print an array
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
    printf("%d ", arr[i]);
    printf("\n");
}
void swap(int *a, int *b)
{
    int t;
    t=*a; *a=*b; *b=t;
}
void bubbleSort(int arr[], int n)
{
    int i, j;
    for (i = 0; i < n-1; i++)
    for (j = 0; j < n-i-1; j++)
    if (arr[j] > arr[j+1])
    swap(&arr[j], &arr[j+1]);
}

int main()
{
    int process_id, size, array[30], i, choice, search, temp[20];
    char str[30];
    char *arg[30];
    printf("\n\tENTER SIZE OF ARRAY : ");
    scanf("%d", &size);
    printf("\n\tENTER ARRAY ELEMENTS : ");
    for(i=0; i<size; i++)
    scanf("%d", &array[i]);
    printf("\n\tENTER ELEMENT TO BE SEARCHED : ");
    scanf("%d", &search);
//bubbleSort(array, size);

    process_id = fork();
    printf("\n\tFORK DONE");
    switch(process_id) {
    case -1 : printf("\n\tERROR!");
    break;
    case 0 : 
        printf("\n\n\t===========CHILD BLOCK=============");
        printf("\n\tCHILD ID : %d", getpid());
        printf("\n\tPARENT ID : %d", getppid());

        printf("\n\tBUBBLE SORT");
        bubbleSort(array, size);
            

        printf("\n\tSORTED ARRAY(CHILD) : ");
        printArray(array, size);
        for(i=0; i<size; i++){
        temp[i] = array[i];
        temp[i] = search;}
        for(i=0; i<size+1; i++) {
            sprintf(str, "%d", temp[i]);
            arg[i] = malloc(sizeof(str));
            strcpy(arg[i], str);
        }
        arg[i]=NULL;
        execve("./b",size,arg);
        break;
    default : 
        printf("\n\n\t===========PARENT BLOCK=============");
        printf("\n\tPARENT ID : %d", getpid());

        bubbleSort(array, size);

    }
    printf("\n\tSORTED ARRAY(PARENT) : ");
    printArray(array, size);


    return 0;
}