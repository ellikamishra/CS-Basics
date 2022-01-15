#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define max 5


void merging(int low, int mid, int high, int a[max], int b[max])                     //Merge sort algorithm
{
    int l1, l2, i;

    for (l1 = low, l2 = mid + 1, i = low; l1 <= mid && l2 <= high; i++)
    {
        if (a[l1] <= a[l2])
            b[i] = a[l1++];
        else
            b[i] = a[l2++];
    }

    while (l1 <= mid)
        b[i++] = a[l1++];

    while (l2 <= high)
        b[i++] = a[l2++];

    for (i = low; i <= high; i++)
        a[i] = b[i];
}

void merge_sort(int low, int high, int a[max], int b[max])       
{
    int mid;

    if (low < high)
    {
        mid = (low + high) / 2;
        merge_sort(low, mid, a, b);
        merge_sort(mid + 1, high, a, b);
        merging(low, mid, high, a, b);
    }
    else
    {
        return;
    }
}


void quick_sort(int a[max], int first, int last)             //Quick sort algorithm
{
    int i, j, pivot, temp;

    if (first < last)
    {
        pivot = first;
        i = first;
        j = last;

        while (i < j)
        {
            while (a[i] <= a[pivot] && i < last)
                i++;
            while (a[j] > a[pivot])
                j--;
            if (i < j)
            {
                temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }

        temp = a[pivot];
        a[pivot] = a[j];
        a[j] = temp;
        quick_sort(a, first, j - 1);
        quick_sort(a, j + 1, last);
    }
}

int main()
{
    pid_t pid;
    int a[5], b[5], i, temp, j;
    int option;

    
    printf("Enter any 5 numbers:\n");                         //Accepting input of unsorted numbers:
    for (i = 0; i < 5; i++)
        scanf("%d", &a[i]);

    printf("\n");

    
    printf("Choose:\n");
    printf("1.Orphan\t2.Zombie\n");                             //Orphan and Zombie menu
    scanf("%d", &option);

    printf("Fork program starting...\n\n");
    pid = fork();                                              //fork function to create child process

    switch (pid)                                                 //switch case to check pid,0 for child,-1 for error ,else parent
    {
    case -1:
        perror("Fork failed! Process not created.\n");
        exit(1);

    case 0:
        printf("IN CHILD: \n\n");

        
        printf("The numbers before sorting are:\n");                  //Printing unsorted array
        for (i = 0; i < max; i++)
            printf("%d\n", a[i]);

        
        merge_sort(0, max, a, b);                                         //Sorting in Child using Merge Sort

        //Printing the sorted array
        printf("The sorted array is: \n");
        for (i = 0; i < max; i++)
        {
            printf("%d\n", a[i]);
        }
        printf("\n");

                                                                      //if orphan option then let the child sleep
        if (option == 1)
        {
            printf("My PID is: %d\n", getpid());
            printf("PID of my parent is: %d\n", getppid());

            printf("Child going to sleep!...\n\n");
            sleep(10);

            printf("Child is awake now!\n");
            printf("My PID is: %d\n", getpid());
            printf("PID of my parent is: %d\n\n", getppid());
        }

        //system("ps -elf | grep s");
        printf("\nBYE CHILD!\n\n");

        break;

    default:
        system("wait");
        printf("IN PARENT: \n\n");

        
        printf("The numbers before sorting are:\n");                //Printing unsorted array
        for (i = 0; i < max; i++)
            printf("%d\n", a[i]);

        
        quick_sort(a, 0, max - 1);                                   //Sorting in Parent using Quick Sort

        
        printf("The sorted array is: \n");                              //Printing the sorted numbers
        for (i = 0; i < max; i++)
        {
            printf("%d\n", a[i]);
        }
        printf("\n");

                                                                        //if zombie let the parent sleep
        if (option == 2)
        {
            printf("My PID is: %d\n", getpid());
            printf("PID of my parent is: %d\n", getppid());

            printf("Parent is going to sleep...\n\n");
            sleep(10);

            printf("Parent is awake now...\n");
            printf("My PID is: %d\n", getpid());
            printf("PID of my parent is: %d\n\n", getppid());
        }

        
        printf("\nBYE PARENT!\n\n");

        break;
    }

    exit(0);
}
