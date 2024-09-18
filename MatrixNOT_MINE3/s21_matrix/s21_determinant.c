#include "../s21_matrix.h"

int s21_determinant(matrix_t *A, double *result) {
  int error = OK;

  if (result != NULL) {
    *result = 0;

    if (check_correct_matrix(A)) {
      if (A->rows == A->columns) {
        *result = determ(A);
      } else {
        error = OTHER_ERROR;
      }
    } else {
      error = UNCORRECT_MATRIX;
    }
  } else {
    error = OTHER_ERROR;
  }

  return error;
}
