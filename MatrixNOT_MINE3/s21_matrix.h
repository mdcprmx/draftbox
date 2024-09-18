#ifndef S21_MATRIX_H_
#define S21_MATRIX_H_

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
//коды для сравнения
#define SUCCESS 1
#define FAILURE 0
//основные коды
#define OK 0
#define UNCORRECT_MATRIX 1
#define OTHER_ERROR 2

typedef struct matrix_struct {  //структура матрицы
  double **matrix;
  int rows;
  int columns;
} matrix_t;

int s21_create_matrix(int rows, int columns,
                      matrix_t *result);      //создание матриц
void s21_remove_matrix(matrix_t *A);          //очистка матриц
int s21_eq_matrix(matrix_t *A, matrix_t *B);  // сравнение матриц
int s21_sum_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  //сложение матриц
int s21_sub_matrix(matrix_t *A, matrix_t *B,
                   matrix_t *result);  //вычитание матриц
int s21_mult_number(matrix_t *A, double number,
                    matrix_t *result);  //умножение матрицы на число
int s21_mult_matrix(matrix_t *A, matrix_t *B,
                    matrix_t *result);  //умножение двух матриц
int s21_transpose(matrix_t *A, matrix_t *result);  // транспонирование матрицы
int s21_calc_complements(matrix_t *A, matrix_t *result);  //минор матрицы
int s21_determinant(matrix_t *A, double *result);  //определитель матрицы
int s21_inverse_matrix(matrix_t *A, matrix_t *result);  //обратная матрица

int check_correct_matrix(matrix_t *A);
int check_size_eq(matrix_t *A, matrix_t *B);
double determ(matrix_t *A);
void minor(int row, int col, matrix_t *A, matrix_t *result);
#endif
