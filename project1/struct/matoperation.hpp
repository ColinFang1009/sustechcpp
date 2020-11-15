#pragma once //make sure this is only included once
#include <cstddef>
struct matrix
{
    int row;
    int column;
    float **mat;
};
//float dotproduct1(const float *p1, const float * p2, size_t n);
//float dotproduct2(const float *p1, const float * p2, size_t n);
//float dotproduct3(const float *p1, const float * p2, size_t n);
//float dotproduct4(const float *p1, const float * p2, size_t n);

void showMat(matrix m);
void matmul3(matrix m1, matrix m2, matrix &result);
float dot(int index, float *v1, float *v2);
void matmul1(matrix m1, matrix m2, matrix &result);
void matmul2(matrix m1, matrix m2, matrix &result);
void matmul4(matrix m1, matrix m2, matrix &result);
