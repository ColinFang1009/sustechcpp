#pragma once
#ifndef MATRIX1_H_
#define MATRIX1_H_
#include<iostream>

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
    Matrix(int r, int c, float *p);
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
    float * GetData();
    void release();
    friend Matrix operator *(double real, const Matrix& other); // a * M
    friend Matrix operator +(double real, const Matrix& other); // c + M
    friend std::ostream & operator <<(std::ostream & os, const Matrix & m );
};
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
static inline double det(int n, float* aa) // use recursion to calculate determinant of a square matrix
{
	if (n == 1)
		return aa[0];
	float *bb = new float[(n - 1)*(n - 1)];//sub-matrix bb 
	int move = 0;//determine whether row number moves   
	double sum = 0.0;//the value of determinant 
    //Calculate Determinant over the first column
	for (int arow = 0; arow<n; arow++) //extract the submatrix excluding (arow, 0-col)
	{
		for (int brow = 0; brow<n - 1; brow++)
		{    
			move = arow > brow ? 0 : 1; //if arow>brow, skip the row and +1;arow=brow, skip;No change if arow<brow  
			for (int j = 0; j<n - 1; j++)  //From the second col of aa to the last col
			{
				bb[brow*(n - 1) + j] = aa[(brow + move)*n + j + 1];
			}
		}
		int flag = (arow % 2 == 0 ? 1: -1);//index cij 
		sum += flag* aa[arow*n] * det(n - 1, bb);//Det += cij * det(submatrix)
	}
	delete[]bb;
	return sum;
}

#endif