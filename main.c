#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
1. ���������� ���������� ���� �� ����. (���� ���� �������� �� ����� input.txt)
2. ������� ������� �������� ������� ������� n*m, ����������� ���������� ������� �� 0 �� 9
3. ��������� ������� ���� �� �������� ��� � ���������� ������ ���� ���������. ������� �� � ���� output.txt
4. �������� ����� ������ ���������
*/

// ��������� ������ � �������� �������� � ���������� ��������� �� 0 �� 9
// ���������� ����� ��������� �������
generate_matrix(int **matrix, int N, int M)
{
	int i, j, sum = 0;
	
	for(i = 0; i < N; i++)
		for(j = 0; j < M; j++)
		{
			matrix[i][j] = rand() % 10;
			sum += matrix[i][j];
		}
	return sum;
}

int main(int argc, char *argv[])
{
	// �������������� ���������� ��� ������ ������� ���������� ���������
	clock_t start, stop; 
	start = clock();
	
	// �������������� ��������� �� ���� output.txt,
	// � ������� ����� �������� ������� �������
	FILE *out = fopen("output.txt", "w");
	
	int i, j, N, M;
	
	// ��������� ������� ������ �� �������
	
	scanf("%d %d", &N, &M);
	
	// �������������� ������� � �������� ��� ��� ������
	
	int **matrix1, **matrix2;
	
	matrix1 = (int**)malloc(N * sizeof(int*));
	matrix2 = (int**)malloc(N * sizeof(int*));
	
	for(i = 0; i < N; i++)
	{
		matrix1[i] = (int*)malloc(M * sizeof(int));
		matrix2[i] = (int*)malloc(M * sizeof(int));
	}
	
	// ���������� ������� �� ��� ���, ���� ����� �� ��������� �� ��������
	
	while(generate_matrix(matrix1, N, M) != generate_matrix(matrix2, N, M));
	
	// ���� ����������!
	
	printf("Match!\n");
	
	// ���������� � output.txt �������� ������ �������
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			fprintf(out, "%d ", matrix1[i][j]);
		fprintf(out, "\n");
	} fprintf(out, "\n");
	
	// ���������� � output.txt �������� ������ �������
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			fprintf(out, "%d ", matrix2[i][j]);
		fprintf(out, "\n");
	}
	
	stop = clock();
	printf("Time taken to execute the program: %.0lfms\n", difftime(stop, start));
	
	return 0;
}
