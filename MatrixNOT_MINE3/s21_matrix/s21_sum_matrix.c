#include "../s21_matrix.h"

// Функция суммирования двух матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = OK;
  if (!check_correct_matrix(A) || !check_correct_matrix(B))
    return UNCORRECT_MATRIX;
  if (!check_size_eq(A, B)) return OTHER_ERROR;
  err = s21_create_matrix(A->rows, A->columns, result);
  if (err == OK) {
    for (int i = 0; i < A->rows; ++i) {
      for (int j = 0; j < A->columns; ++j) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }

  return err;
}