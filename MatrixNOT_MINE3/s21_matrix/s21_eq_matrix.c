#include "../s21_matrix.h"

// Функция сравнения матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int err = SUCCESS;
  if ((!check_correct_matrix(A)) || (!check_correct_matrix(B)))
    return err = FAILURE;
  if (!check_size_eq(A, B)) return FAILURE;
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < A->columns; j++) {
      if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 0.0000001) {
        err = FAILURE;
      }
    }
  }

  return err;
}
