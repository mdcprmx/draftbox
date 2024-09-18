#include "../s21_matrix.h"
void s21_remove_matrix(matrix_t *A) {
  if (A->matrix) {
    if (A->matrix[0]) free(A->matrix[0]);
    free(A->matrix);
    if (A->rows) {
      A->rows = 0;
    }
    if (A->columns) {
      A->columns = 0;
    }
    A->matrix = NULL;
  }
}