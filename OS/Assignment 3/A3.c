#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define SIZE 10
int *A[SIZE], *B[SIZE];    //declaring array of pointer for matrices

void *multiplication(void *arg)      //multiplication function 
{
	int *a, row, col, value, n;
	int *p = (int *)malloc(sizeof(int));
	a = (int *)arg;                                 //int pointer a stores array values of rows,columns and times to loop .
	row = a[0];
	col = a[1];
	n = a[2];
	value = 0;
	for (int k = 0; k < n; k++)
		value += A[row][k] * B[k][col];                         
	*p = value;

	pthread_exit(p);               //pointer p returned in thread exit
}

void display_matrix(int *M[SIZE], int n, int m)              //display matrix 
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			printf("%d\t", M[i][j]);
		printf("\n");
	}
}

void input_matrix(int *M[SIZE], int n, int m)    //input matirx
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < m; j++)
			scanf("%d", &M[i][j]);
	}
}

int main()
{
	int n1, m1, n2, m2, res, args[3], *C[SIZE];          //args array ,row,column values, result array of pointers
	void *val;

	while (1)                                         //input row,col values
	{
		printf("\nEnter number of rows for A: ");
		scanf("%d", &n1);
		printf("Enter number of cols for A: ");
		scanf("%d", &m1);
		printf("\nEnter number of rows for B: ");
		scanf("%d", &n2);
		printf("Enter number of cols for B: ");
		scanf("%d", &m2);

		if (m1 == n2)
			break;
		printf("\nEnter correct matrices again!\n");
	}
	printf("\nMatrix A elements: \n");                           //input and display matrices.
	for (int i = 0; i < n1; i++)
		A[i] = (int *)malloc(m1 * sizeof(int));
	input_matrix(A, n1, m1);
	printf("\nMatrix A : \n");
	display_matrix(A, n1, m1);

	printf("\nMatrix B elements: \n");
	for (int i = 0; i < n2; i++)
		B[i] = (int *)malloc(m2 * sizeof(int));
	input_matrix(B, n2, m2);
	printf("\nMatrix B : \n");
	display_matrix(B, n2, m2);

	for (int i = 0; i < n1; i++)
		C[i] = (int *)malloc(m2 * sizeof(int));

	pthread_t *new_thread[n1];   //declaring array of threads
	for (int i = 0; i < n1; i++)
		new_thread[i] = (pthread_t *)malloc(m2 * sizeof(pthread_t));

	printf("Waiting for threads to finish...\n");

	for (int i = 0; i < n1; i++)                        //looping through rows of mat1 and columns of mat2 
	{
		for (int j = 0; j < m2; j++)
		{
			args[0] = i;
			args[1] = j;
			args[2] = m1;
			res = pthread_create(&new_thread[i][j], NULL, multiplication, (void *)args);  //thread creation passing multiplication func and args
			if (res != 0)
			{
				perror("Thread creation failed");
				exit(EXIT_FAILURE);
			}
			sleep(1);
		}
	}

	for (int i = 0; i < n1; i++)             
	{
		for (int j = 0; j < m2; j++)
		{
			res = pthread_join(new_thread[i][j], &val);          //joining threads
			if (res != 0)
			{
				perror("Thread join failed");
				exit(EXIT_FAILURE);
			}
			C[i][j] = *((int *)val);
		}
	}
	printf("\nResultant Matrix C : \n");
	display_matrix(C, n1, m2);
	return 0;
}
