#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
1. Рассчитать количество дней до даты. (ввод даты читается из файла input.txt)
2. Сделать функцию создания матрицы размера n*m, заполненную случайными числами от 0 до 9
3. Создавать матрицы пока не появятся две с одинаковой суммой всех элементов. Вывести их в файл output.txt
4. Замерить вермя работы программы
*/

// Генератор матриц с заданным размером и значениями элементов от 0 до 9
// Возвращает сумму элементов матрицы
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
	// Инициализируем переменные для замера времени выполнения программы
	clock_t start, stop; 
	start = clock();
	
	// Инициализируем указатель на файл output.txt,
	// в который будут выписаны будущие матрицы
	FILE *out = fopen("output.txt", "w");
	
	int i, j, N, M;
	
	// Считываем размеры матриц из консоли
	
	scanf("%d %d", &N, &M);
	
	// Инициализируем матрицы и выделяем под них память
	
	int **matrix1, **matrix2;
	
	matrix1 = (int**)malloc(N * sizeof(int*));
	matrix2 = (int**)malloc(N * sizeof(int*));
	
	for(i = 0; i < N; i++)
	{
		matrix1[i] = (int*)malloc(M * sizeof(int));
		matrix2[i] = (int*)malloc(M * sizeof(int));
	}
	
	// Генерируем матрицы до тех пор, пока суммы их элементов не совпадут
	
	while(generate_matrix(matrix1, N, M) != generate_matrix(matrix2, N, M));
	
	// Есть совпадение!
	
	printf("Match!\n");
	
	// Выписываем в output.txt значения первой матрицы
	
	for(i = 0; i < N; i++)
	{
		for(j = 0; j < M; j++)
			fprintf(out, "%d ", matrix1[i][j]);
		fprintf(out, "\n");
	} fprintf(out, "\n");
	
	// Выписываем в output.txt значения второй матрицы
	
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
