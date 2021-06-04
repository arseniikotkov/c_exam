#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define DEBUG
#undef DEBUG

struct matrix
{
	int N;
	int M;
	int **matrix;
};

void generate_matrix_into_file(int N, int M, FILE *in)
{
	int i, j, **matrix;
	
	matrix = (int**)malloc(N * sizeof(int*));
	
	for(i = 0; i < N; i++)
		matrix[i] = (int*)malloc(M * sizeof(int));
	
	fprintf(in, "%d %d\n", N, M);
	for(i = 0; i < N; i++)
	{
	
		for(j = 0; j < M; j++)
		{
			matrix[i][j] = rand() % 10; // «десь можно задать диапазон случайных чисел
			fprintf(in, "%d ", matrix[i][j]);
		}
		fprintf(in, "\n");
	}
	fprintf(in, "\n");
	
	
	for(i = 0; i < N; i++)
		free(matrix[i]);
	free(matrix);
	
	return;
}


int main()
{
	clock_t start, stop;
	start = clock();
	
	int i, j, k, N, M;
	
	// √енерируем две матрицы N*M и сохран€ем их в input.txt
	
	FILE *in = fopen("input.txt", "w");
	for(i = 0; i < 2; i++)
	{
		scanf("%d %d", &N, &M);
		generate_matrix_into_file(N, M, in);
	}
	
	fclose(in);
	in = fopen("input.txt", "r");
	
	struct matrix matrixes[2];
	int **sum, **mul, buffer;
	
	// —читываем матрицы из input.txt и сохран€ем их в массив
	
	for(k = 0; k < 2; k++)
	{
		fscanf(in, "%d %d", &matrixes[k].N, &matrixes[k].M);
		
		matrixes[k].matrix = (int**)malloc(N * sizeof(int*));
		
		for(i = 0; i < matrixes[k].N; i++)
			matrixes[k].matrix[i] = (int*)malloc(M * sizeof(int));
			
		for(i = 0; i < matrixes[k].N; i++)
			for(j = 0; j < matrixes[k].M; j++)
				fscanf(in, "%d", &matrixes[k].matrix[i][j]);
		
		#ifdef DEBUG
		printf("%d %d\n", N, M);
		for(i = 0; i < N; i++)
		{
			for(j = 0; j < M; j++)
				printf("%d ", matrixes[k][i][j]);
			printf("\n");
		}
		printf("\n");
		#endif
	}
	
	FILE *out = fopen("output.txt", "w");
	
	if(matrixes[0].N != matrixes[1].N || matrixes[0].M != matrixes[1].M)
		printf("Cannot sum two matrixes: different dimensions.\n");
	else
	{
		sum = (int**)malloc(matrixes[0].N * sizeof(int*));
	
		for(i = 0; i < matrixes[0].N; i++)
			sum[i] = (int*)malloc(matrixes[0].M * sizeof(int));
			
		fprintf(out, "SUM\n");
		for(i = 0; i < matrixes[0].N; i++)
		{
			for(j = 0; j < matrixes[0].M; j++)
			{
				sum[i][j] = matrixes[0].matrix[i][j] + matrixes[1].matrix[i][j];
				fprintf(out, "%d ", sum[i][j]);
			}
			fprintf(out, "\n");
		}
		fprintf(out, "\n");
		
		for(i = 0; i < N; i++)
			free(sum[i]);
		free(sum);
	}
	
	if(matrixes[0].M != matrixes[1].N)
		printf("Cannot multiply two matrixes: not compatible.\n");
	else
	{
		mul = (int**)malloc(matrixes[1].M * sizeof(int*));
		for(i = 0; i < matrixes[1].M; i++)
			mul[i] = (int*)malloc(matrixes[0].N * sizeof(int));
			
		for(i = 0; i < matrixes[0].N; i++)
		{
			for(j = 0; j < matrixes[1].M; j++)
				printf("0 ");
			printf("\n");
		}
		
		int sum = 0;
			
		for(i = 0; i < matrixes[0].N; i++)
			for(j = 0; j < matrixes[1].M; j++)
			{ 
				for(k = 0; k < matrixes[1].N; k++)
				{
					sum += matrixes[0].matrix[i][k] * matrixes[1].matrix[k][j];
				}
				mul[i][j] = sum;
				sum = 0;
				printf("mul[%d][%d]: %d\n", i, j, mul[i][j]);
			}
		
		fprintf(out, "MULTIPLICATION\n");
		for(i = 0; i < matrixes[0].N; i++)
		{
			for(j = 0; j < matrixes[1].M; j++)
				fprintf(out, "%d ", mul[i][j]);
			fprintf(out, "\n");
		}
	}
	
	stop = clock();
	printf("Time taken to execute the program: %.3lf seconds.\n", difftime(stop, start) / 1000);
	return 0;
}
