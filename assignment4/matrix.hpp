#pragma once
#ifndef MATRIX1_H_
#define MATRIX1_H_
#include<iostream>

static inline int CV_XADD(int* addr, int delta)
{
    int tmp = *addr;
    *addr += delta; 
    return tmp;
}
static inline void matmul_n(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
    //m1: r1*c, m2: c*c2, result: r1*c2
    float s;
    for (int i = 0; i < r1; ++i)
    {
        for (int k = 0; k < c; ++k)
        {
            s = m1[i * c + k];
            for (int j = 0; j < c2; ++j)
            {
                result[i * (c2) + j] += s * m2[k * (c2) + j];
            }
        }
    }
}
class Matrix
{
    private:
    int row;
    int column;
    float *data;
    int *refcount;

    public:
    Matrix();
    Matrix(int r, int c);
    Matrix(int r, int c, float * p,int *rv);
    Matrix(const Matrix & m);
    ~Matrix();
    Matrix & operator=(const Matrix & m) ; //assignment operator
    Matrix & operator+(const Matrix & m) ; //mat+mat
    Matrix & operator-(const Matrix & m) ; //mat-mat
    Matrix & operator*(const Matrix & m) ; //mat * mat
    Matrix & operator*(const double d);
    int GetRow();
    int GetColumn();
    void release();
    friend Matrix operator *(double real, const Matrix& other); // a * M
    friend Matrix operator +(double real, const Matrix& other); // c + M
    friend std::ostream & operator <<(std::ostream & os, const Matrix & m );
};


#endif