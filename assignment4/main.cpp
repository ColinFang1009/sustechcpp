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
        //cout<<p[i]<<" ";
    }
    //Matrix m1(4,8,p,r);
    //Matrix m2(8,4,p,r);
    //Matrix m3 = m1*m2;
    //Matrix m4 = 2*m1;
    //Matrix m5 = 3+m2;
    // cout <<"\nm1="<<m1<<endl;
    // cout <<"\nm2="<< m2<<endl;
    // cout << "\nThe number of time the float * p is referenced:\nrefcount= "<<*r<<endl;//should be 2, m1, m2 referenced
    // cout <<"\nm3=m1*-m2="<<m3<<endl;
    // cout <<"\nm4=4+m1="<<m4<<endl;
    // cout <<"\nm5=m1+2*m2="<<m5<<endl;
    // cout <<"Use Copy Constructor to build m6 (copy m1)"<<endl;
    // Matrix m6(m1);//m6 uses copy constructor
    // cout << "\nThe number of time the float * p is referenced:\nrefcount= "<<*r<<endl;//3
    // cout <<"\nm6=Matrix(m1)="<<m6<<endl;
    // cout<<"Assignment operator, m1=m4."<<endl;
    // m1 = m4;//delete 1, should be back to 2
    // cout <<"\nm1="<<m1<<endl;
    // cout << "\nThe number of time the float * p is referenced:\nrefcount= "<<*r<<endl;//2

    int n = 2;
	float *aa = new float[n*n];
	for (int i = 0; i < n*n; i++)
		aa[i]=i-0.5;
    Matrix m7(n,n,aa);
    cout << m7<<endl;
    cout <<"Determinant of m7: "<<det(n, m7.GetData())<<endl;
    
	delete[] aa;
    delete[] p;
    delete[] r;
    return 0;
}