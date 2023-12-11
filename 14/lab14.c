#include <stdio.h>
#include <stdlib.h>

typedef int **Matrix;

Matrix CreateMatrix(int rows, int cols)
{
    Matrix matrix = (Matrix)malloc(rows * sizeof(int *));
    for (int i = 0; i < rows; ++i)
    {
        matrix[i] = (int *)malloc(cols * sizeof(int));
    }
    return matrix;
}

void FreeMatrix(Matrix matrix, int rows)
{
    for (int i = 0; i < rows; ++i)
    {
        free(matrix[i]);
    }
    free(matrix);
}

void InputMatrix(Matrix matrix, int rows, int cols)
{
    printf("Введите элементы матрицы:\n");
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < cols; ++j)
        {
            scanf("%d", &matrix[i][j]);
        }
    }
}

int *DiagonalLinearizeMatrix(Matrix matrix, int rows, int cols)
{
    int *linear_array = (int*)malloc(rows * cols * sizeof(int));
    int linear_index = 0;
    int total_diagonal_quantity = rows + cols - 1;

    for (int diagonal = 1; diagonal <= total_diagonal_quantity; ++diagonal)
    {
        int start_row, end_row, col;

        if (diagonal <= cols)
        {
            start_row = 0;
            end_row = diagonal < rows ? diagonal - 1 : rows - 1;
            col = cols - diagonal;
        }
        else
        {
            start_row = diagonal - cols;
            end_row = rows - 1;
            col = 0;
        }

        for (int row = start_row; row <= end_row; ++row)
        {
            linear_array[linear_index++] = matrix[row][col++];
        }
    }

    return linear_array;
}

int main()
{
    int rows, cols;
    printf("Введите количество строк и столбцов матрицы: ");
    scanf("%d %d", &rows, &cols);

    Matrix matrix = CreateMatrix(rows, cols);
    InputMatrix(matrix, rows, cols);

    int *linear_array = DiagonalLinearizeMatrix(matrix, rows, cols);

    printf("Линеаризованный массив:\n");
    for (int i = 0; i < rows * cols; ++i)
    {
        printf("%d ", linear_array[i]);
    }
    printf("\n");

    free(linear_array);
    FreeMatrix(matrix, rows);
    return 0;
}
