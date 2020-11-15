#include <iostream>
#include <algorithm>
#include <iomanip>
#include "matoperation.hpp"
#include <immintrin.h>
#include <omp.h>

using namespace std;

float dot(int index, float *v1, float *v2)
{
    float result;
    for (int i = 0; i < index; i++)
    {
        result += v1[i] * v2[i];
    }
    return result;
}
//doesn't work
void matmul1(matrix m1, matrix m2, matrix &result)
{
    float *m2_col = new float[m2.row];
    for(int i=0;i<m1.row;i++)
    {
        for(int j=0;j<m2.column;j++)
        {
             for(int q=0;q<m2.row;q++)
            {
                 m2_col[q]=m2.mat[q][j];
            }
            result.mat[i][j]=dot(m1.column, m1.mat[i], m2_col);  
        }
    }
    delete m2_col;
}

void matmul2(matrix m1, matrix m2, matrix &result)
{
    float temp1=0, temp2=0, temp3=0, temp4=0;
    for(int i=0;i<m1.row;i++)
    {
        for(int j=0;j<m2.column;j++)
        {
            for(int k=0;k<m1.column;k+=4)
            {
                //result.mat[i][j]+=m1.mat[i][k] * m2.mat[k][j];
                temp1 += m1.mat[i][k] * m2.mat[k][j];
                temp2 += m1.mat[i][k+1] * m2.mat[k+1][j];
                temp3 += m1.mat[i][k+2] * m2.mat[k+2][j];
                temp4 += m1.mat[i][k+3] * m2.mat[k+3][j];
            }
            result.mat[i][j] = temp1 + temp2 + temp3 + temp4;
        }
    }
}
void matmul3(matrix m1, matrix m2, matrix &result)
{
    float s;
    for(int i=0;i<m1.row;++i)
    {
        for(int k=0;k<m1.column;++k)
        {
            s=m1.mat[i][k];
            for(int j=0;j<m2.column;++j)
            {
                result.mat[i][j]+= s * m2.mat[k][j];
            }
        }
    }
}
void matmul4(matrix m1, matrix m2, matrix &result)
{
    float sum[8] = {0};
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();
    for(int i=0;i<m1.row;++i)
        for(int j=0;j<m2.column;++j)
        {
            for(size_t k=0;k<m1.column;k+=8)
            {
                a = _mm256_load_ps(m1.mat[i] + k);
                b = _mm256_load_ps(m2.mat[k] + j);
                c =  _mm256_add_ps(c, _mm256_mul_ps(a, b));
            }
            _mm256_store_ps(sum, c);
            result.mat[i][j] = sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]; 
        }
    
}
float dotproduct3(const float *p1, const float * p2, size_t n)
{
    if(n % 8 != 0)
    {
        std::cerr << "The size n must be a multiple of 8." <<std::endl;
        return 0.0f;
    }

    float sum[8] = {0};
    __m256 a, b;
    __m256 c = _mm256_setzero_ps();

    for (size_t i = 0; i < n; i+=8)
    {
        a = _mm256_load_ps(p1 + i);
        b = _mm256_load_ps(p2 + i);
        c =  _mm256_add_ps(c, _mm256_mul_ps(a, b));
    }
    _mm256_store_ps(sum, c);
    return (sum[0]+sum[1]+sum[2]+sum[3]+sum[4]+sum[5]+sum[6]+sum[7]);
}

void showMat(matrix m)
{
    cout << endl;
    for (int i = 0; i < m.row; i++)
    {
        for (int j = 0; j < m.column; j++)
            cout << m.mat[i][j] << " ";
        cout << endl;
    }
}