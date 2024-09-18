#include "../s21_matrix.h"

// Функция определения минора матрицы с алгебраическим дополнением
int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int error = OK;

  if (check_correct_matrix(A)) {
    if (A->rows == A->columns) {
      error = s21_create_matrix(A->rows, A->columns, result);

      if (!error) {
        if (A->rows == 1) {
          result->matrix[0][0] = A->matrix[0][0];
        } else {
          matrix_t tmp = {0};

          error = s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);

          if (!error) {
            for (int i = 0; i < result->rows; i++) {
              for (int j = 0; j < result->columns; j++) {
                minor(i, j, A, &tmp);
                result->matrix[i][j] = determ(&tmp);
              }
            }

            for (int i = 0; i < result->rows; i++) {
              for (int j = 0; j < result->columns; j++) {
                result->matrix[i][j] = pow(-1, i + j) * result->matrix[i][j];
              }
            }
          } else {
            error = OTHER_ERROR;
          }

          s21_remove_matrix(&tmp);
        }
      }

    } else {
      error = OTHER_ERROR;
    }
  } else {
    error = UNCORRECT_MATRIX;
  }

  return error;
}
