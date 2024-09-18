#include "../s21_matrix.h"

// Функция выделения памяти для матрицы
int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = OK;
  *result = (matrix_t){0};
  if (rows > 0 && columns > 0) {
    result->rows = rows;
    result->columns = columns;
    double **matrix = (double **)calloc(rows, sizeof(double *));
    double *values = (double *)calloc(rows * columns, sizeof(double));
    for (int i = 0; i < rows; i++) {
      matrix[i] = values + columns * i;
    }
    result->matrix = matrix;
  } else {
    res = UNCORRECT_MATRIX;
    result->matrix = NULL;
  }
  return res;
}
