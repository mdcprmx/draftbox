#include "../s21_matrix.h"

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (check_correct_matrix(A)) {
    if (A->rows == A->columns) {
      double determinant = 0;
      s21_determinant(A, &determinant);

      if (determinant != 0 && fabs(determinant) > 1e-07) {
        matrix_t tmp_calc = {0};
        matrix_t tmp_trans = {0};

        s21_calc_complements(A, &tmp_calc);
        s21_transpose(&tmp_calc, &tmp_trans);
        s21_mult_number(&tmp_trans, 1. / determinant, result);
        s21_remove_matrix(&tmp_calc);
        s21_remove_matrix(&tmp_trans);

      } else {
        error = OTHER_ERROR;
      }
    } else {
      error = OTHER_ERROR;
    }
  } else {
    error = UNCORRECT_MATRIX;
  }

  return error;
}
