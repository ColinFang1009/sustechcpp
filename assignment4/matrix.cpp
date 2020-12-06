#include<iostream>
#include "matrix.hpp"

Matrix::Matrix()
{
    row = 1;
    column = 1;
    data = new float[1];
    refcount = new int;
    *refcount = 1;
}
Matrix::Matrix(int r, int c)
{
    row = r;
    column = c;
    data = new float[r*c];
    refcount = new int;
    *refcount = 1;
}
Matrix::Matrix(int r, int c, float * p)
{
    row = r;
    column = c;
    data = p;
    refcount = new int;
    *refcount = 1;
}
Matrix::Matrix(int r, int c, float * p,int* rv)
{
    row = r;
    column = c;
    data = p;
    refcount = rv;
    *rv = *rv +1;
}
Matrix::Matrix(const Matrix & m)
{
    row = m.row;
    column = m.column;
    data = m.data;
    refcount = m.refcount;
    CV_XADD(refcount, 1);
}
Matrix::~Matrix()
{
    std::cout << "Destructor is called."<<std::endl;
    release();
}
    
Matrix & Matrix::operator=(const Matrix & m) 
{
    if(this != &m)
    {
        if(m.refcount)
            CV_XADD(m.refcount,1); //refcount to m.data ++
        release();
        row = m.row;
        column = m.column;
        data = m.data;
        refcount = m.refcount;
        return *this;
    }
    else
    {
        return *this;
    }
    
} 
Matrix & Matrix::operator+(const Matrix & m) //mat+mat
{
    if(row != m.row || column != m.column)// deal with size mismatch
    {
        std::cout << "The sizes do not match, return the original matrix."<<std::endl;
        return *this;
    }
    else
    {
        int row_n = this->row;
        int col_n = this->column;
        Matrix * m_n = new Matrix(row_n,col_n);
        for(int i = 0;i<row;i++)
            for(int j=0;j<column;j++)
                m_n->data[i*row+j] = this->data[i*row+j] + m.data[i*row+j];
        return *m_n;
        
    }
        
}
Matrix & Matrix::operator-(const Matrix & m)  //mat-mat
{
    if(row != m.row || column != m.column)// deal with size mismatch
    {
        std::cout << "The sizes do not match, return the original matrix."<<std::endl;
        return *this;
    }
    else
    {
        int row_n = this->row;
        int col_n = this->column;
        Matrix * m_n = new Matrix(row_n,col_n);
        for(int i = 0;i<row;i++)
            for(int j=0;j<column;j++)
                m_n->data[i*row+j] = this->data[i*row+j] - m.data[i*row+j];
        return *m_n;
    }
}
Matrix & Matrix::operator*(const Matrix & m)  //mat * mat
{
    if(this->column != m.row)// deal with size mismatch
    {
        std::cout<<"Illegal multiplication, original value returned"<<std::endl;
        return *this;
    }
    int row_n = this->row;
    int col_n = m.column;
    Matrix * m_n = new Matrix(row_n,col_n);
    matmul_n(row_n,m.row,col_n,data,m.data,m_n->data);
    return *m_n;
}
Matrix & Matrix::operator*(const double d)  //mat * d
{
    int row_n = this->row;
    int col_n = this->column;
    Matrix * m_n = new Matrix(row_n,col_n);
    for(int i=0;i<row_n*col_n;i++)
        m_n->data[i] = d*data[i];
    return *m_n;
}
int Matrix::GetRow()
{return row;}

int Matrix::GetColumn()
{return column;}
float * Matrix::GetData()
{return data;}
Matrix operator *(double real, const Matrix& other) // a * M
{
    int row_n = other.row;
    int col_n = other.column;
    Matrix * m_n = new Matrix(row_n,col_n);
    for(int i=0;i<row_n*col_n;i++)
        m_n->data[i] = real*other.data[i];
    return *m_n;
}
Matrix operator +(double real, const Matrix& other) // c + M
{
    int row_n = other.row;
    int col_n = other.column;
    Matrix * m_n = new Matrix(row_n,col_n);
    for(int i=0;i<row_n*col_n;i++)
        m_n->data[i] = real+other.data[i];
    return *m_n;
}
std::ostream & operator <<(std::ostream & os, const Matrix & m )
{
    using namespace std;
    for(int r=0;r<m.row;r++)
    {
        os << endl;
        for(int c=0;c<m.column;c++)
            os<<m.data[r*m.column+c]<<" ";
    }
    return os;
}

void Matrix::release()
{
    if(*refcount == 1)
    {
        delete[] data;
        delete[] refcount;
    }
    else
        CV_XADD(refcount, -1);
    refcount = NULL;
}

