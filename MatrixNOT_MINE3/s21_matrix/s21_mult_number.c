#include "../s21_matrix.h"

// Функция умножения матрицы на число
int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int err = OK;
  if (!check_correct_matrix(A)) {
    err = UNCORRECT_MATRIX;
  } else {
    err = s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return err;
}