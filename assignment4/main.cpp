#include <iostream>
#include "matrix.hpp"
using namespace std;

int main()
{
    float *p = new float[32];
    int * r = new int;
    *r = 0;
    for(int i=0;i<32;i++)
    {
        p[i]=1.0f+i;
        cout<<p[i]<<" ";
    }
    Matrix m1(4,8,p,r);
    Matrix m2(8,4,p,r);
    //Matrix m3 = Matrix(2,2);
    Matrix m3 = m1*m2;
    Matrix m4 = 4*m1;
    Matrix m5 = m2*2;
    cout << "\nThe number of time the float * p is referenced:\nrefcount= "<<*r<<endl;//should be 2, m1, m2 referenced
    cout <<"\nm1="<<m1<<endl;
    cout <<"\nm2="<< m2<<endl;
    cout <<"\nm3=m1*m2="<<m3<<endl;
    cout <<"\nm4=4*m1="<<m4<<endl;
    cout <<"\nm5=m2*2="<<m5<<endl;
    cout <<"Use Copy Constructor to build m6 (copy m1)"<<endl;
    Matrix m6(m1);//m6 uses copy constructor
    cout << "\nThe number of time the float * p is referenced:\nrefcount= "<<*r<<endl;//3
    m1 = m4;//delete 1, should be back to 2
    cout << "\nThe number of time the float * p is referenced:\nrefcount= "<<*r<<endl;//2
    delete[] p;
    return 0;
}