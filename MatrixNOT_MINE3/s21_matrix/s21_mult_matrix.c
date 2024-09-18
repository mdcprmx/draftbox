#include "../s21_matrix.h"

// Функция умножения двух матриц
int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int err = 0;
  if (!check_correct_matrix(A) || !check_correct_matrix(B)) {
    err = UNCORRECT_MATRIX;
  } else if (A->columns == B->rows) {
    err = s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        for (int k = 0; k < B->rows; k++) {
          result->matrix[i][j] += A->matrix[i][k] * B->matrix[k][j];
        }
      }
    }
  } else {
    err = OTHER_ERROR;
  }
  return err;
}
