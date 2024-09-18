#include "../s21_matrix.h"

// 1 OK; 0 - плохо;
int check_correct_matrix(matrix_t *A) {
  int err = 1;
  if (A == NULL) return 0;
  if ((A->matrix == NULL) || (A->rows <= 0) || (A->columns <= 0)) return 0;
  return err;
}

int check_size_eq(matrix_t *A, matrix_t *B) {
  int err = 0;
  if (A->rows == B->rows && A->columns == B->columns) err = 1;
  return err;
}

void minor(int row, int col, matrix_t *A, matrix_t *result) {
  int m_row = 0;
  int m_col = 0;

  for (int i = 0; i < A->rows; i++) {
    if (i == row) {
      continue;
    }

    m_col = 0;

    for (int j = 0; j < A->columns; j++) {
      if (j == col) {
        continue;
      }

      result->matrix[m_row][m_col] = A->matrix[i][j];
      m_col++;
    }
    m_row++;
  }
}

double determ(matrix_t *A) {
  double res = 0.0;

  if (A->rows == 1) {
    res = A->matrix[0][0];
  } else {
    matrix_t tmp = {0};
    s21_create_matrix(A->rows - 1, A->columns - 1, &tmp);

    for (int i = 0; i < A->columns; i++) {
      minor(0, i, A, &tmp);

      if (i % 2) {
        res -= A->matrix[0][i] * determ(&tmp);
      } else {
        res += A->matrix[0][i] * determ(&tmp);
      }
    }
    s21_remove_matrix(&tmp);
  }

  return res;
}