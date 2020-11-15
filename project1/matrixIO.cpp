#include <iostream>
#include <algorithm>
#include <iomanip>
#include <stdlib.h>

using namespace std;

struct matrix
{
    int row;
    int column;
    float **mat;
};

void matmul2(matrix m1, matrix m2, matrix &result)
{
    for (int i = 0; i < m1.row; i++)
    {
        for (int j = 0; j < m2.column; j++)
        {
            for (int k = 0; k < m1.column; k++)
                result.mat[i][j] += m1.mat[i][k] * m2.mat[k][j];
        }
    }
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
int main()
{
    matrix m1;
    matrix m2;
    cout << "Enter the first float matrix m1" << endl;
    cout << "Row = ";
    while (1)
    {
        cin >> m1.row;
        if (m1.row <= 0 || cin.fail())
        {
            cout << "The dimension of the matrix should be a positive integer.Enter again: ";
            cin.clear();
            cin.sync();
        }
        else
        {
            break;
        }
    }
    cout << "Column = ";
    while (1)
    {
        cin >> m1.column;
        if (m1.column <= 0 || cin.fail())
        {
            cout << "The dimension of the matrix should be a positive integer.Enter again: ";
            cin.clear();
            cin.sync();
        }
        else
        {
            break;
        }
    }
    cout << "Enter the second float matrix m2" << endl;
    cout << "Row = ";
    while (1)
    {
        cin >> m2.row;
        if (m2.row <= 0 || cin.fail())
        {
            cout << "The dimension of the matrix should be positive int.Enter again: ";
            cin.clear();
            cin.sync();
        }
        else
        {
            break;
        }
    }
    cout << "Column = ";
    while (1)
    {
        cin >> m2.column;
        if (m2.column <= 0 || cin.fail())
        {
            cout << "The dimension of the matrix should be positive int.Enter again: ";
            cin.clear();
            cin.sync();
        }
        else
        {
            break;
        }
    }
    if (m1.column != m2.row)
    {
        cout << "The sizes of the matrices do not match" << endl;
        exit(100);
    }
    matrix res;
    res.row = m1.row;
    res.column = m2.column;
    res.mat = new float *[res.row];
    for (int i = 0; i < res.row; i++)
    {
        res.mat[i] = new float[res.column];
    }

    float temp;
    int index1 = 0;
    int index2 = 0;

    float *data1 = new float[m1.row * m1.column];
    cout << "Data: ";
    while (1)
    {
        cin >> temp;
        if (!cin)
        {
            cout << "There is an illegal input. Please Enter Again" << endl;
            cout << "Enter the data: ";
            cin.clear();
            cin.sync();
            index1 = 0; //reset the index
        }
        else
        {
            data1[index1] = temp;
            index1++;
            if (index1 > (m1.row * m1.column))
            {
                cout << "The data exceeds the length and will not be taken" << endl;
                break;
            }
            else if (getchar() == '\n') //break when Enter is inputted
            {
                break;
            }
        }
    }
    cin.clear();
    cin.sync();

    float *data2 = new float[m2.row * m2.column];
    cout << "Data2: ";
    while (1)
    {
        cin >> temp;
        if (!cin)
        {
            cout << "There is an illegal input. Please Enter Again" << endl;
            cout << "Enter the data: ";
            cin.clear();
            cin.sync();
            index2 = 0; //reset the index
        }
        else
        {
            data2[index2] = temp;
            index2++;
            if (index2 > (m2.row * m2.column))
            {
                cout << "The data exceeds the length and will not be taken" << endl;
                break;
            }
            else if (getchar() == '\n') //break when Enter is inputted
            {
                break;
            }
        }
    }
    cin.clear();
    cin.sync();

    m1.mat = new float *[m1.row];
    for (int i = 0; i < m1.row; i++)
    {
        m1.mat[i] = new float[m1.column];
        for (int j = 0; j < m1.column; j++)
            m1.mat[i][j] = data1[i * m1.column + j];
    }

    m2.mat = new float *[m2.row];
    for (int i = 0; i < m2.row; i++)
    {
        m2.mat[i] = new float[m2.column];
        for (int j = 0; j < m2.column; j++)
            m2.mat[i][j] = data2[i * m2.column + j];
    }

    matmul2(m1, m2, res);
    cout << "M1= ";
    showMat(m1);
    cout << "M2= ";
    showMat(m2);
    cout << "\nThe product is ";
    showMat(res);
    delete m1.mat;
    delete m2.mat;
    delete res.mat;
    delete[] data1;
    delete[] data2;

    return 0;
}