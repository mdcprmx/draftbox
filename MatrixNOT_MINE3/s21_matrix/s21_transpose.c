#include "../s21_matrix.h"

// Функция транспонирования матрицы
int s21_transpose(matrix_t *A, matrix_t *result) {
  int err = OK;
  if (!check_correct_matrix(A)) {
    err = UNCORRECT_MATRIX;
  } else {
    err = s21_create_matrix(A->columns, A->rows, result);
    if (!err) {
      for (int i = 0; i < A->rows; i++) {
        for (int j = 0; j < A->columns; j++) {
          result->matrix[j][i] = A->matrix[i][j];
        }
      }
    } else {
      err = OTHER_ERROR;
    }
  }
  return err;
}