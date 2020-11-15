#include <iostream>
//#include <algorithm>
//#include <iomanip>
#include <ctime>
#include <chrono>
#include"matoperation.hpp"


using namespace std;

int main()
{
    matrix m1;
    matrix m2;
    m1.row=1000;
    m1.column=4000;
    m2.row=4000;
    m2.column=1000;
    //float data[3][3] = {{1,2,3}, {4,5,6}, {7,8,9}};
    //float data2[3][3] = {{1,0,0}, {0,1,0}, {0,0,1}};
    m1.mat=new float*[m1.row];
    for(int i = 0;i<m1.row;i++)
    {
        m1.mat[i]=new float[m1.column];
        for(int j=0;j<m1.column;j++)
            m1.mat[i][j]=1;
    }
    m2.mat=new float*[m2.row];
    for(int i = 0;i<m2.row;i++)
    {
        m2.mat[i]=new float[m2.column];
        for(int j=0;j<m2.column;j++)
            m2.mat[i][j]=i+j;
    }
    matrix res;
    
    res.row = m1.row;
    res.column = m2.column;
    res.mat=new float*[res.row];
    for(int i = 0;i<res.row;i++)
    {
        res.mat[i]=new float[res.column];
    }
  
    auto start = std::chrono::steady_clock::now();
    matmul3(m1, m2, res);
    auto end = std::chrono::steady_clock::now();
    std::cout << "Matrix product calculations took "
            << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "mus = "
            << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ="
            << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.\n";

    //showMat(m1);
    //showMat(m2);
    //showMat(res);
    delete m1.mat;
    delete m2.mat;
    delete res.mat;
    return 0;
}