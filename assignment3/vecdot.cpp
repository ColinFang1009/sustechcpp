//vecdot.cpp vector dot product calculator
//Name: Weike Fang (22010055)
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>

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

int main()
{
    int n = 100;
    float *v1 = new float[n];
    float *v2 = new float[n];
    float temp;
    float result;
    int index1 = 0;
    int index2 = 0;

    cout << "Enter the first vector v1 = ";
    while (1)
    {
        cin >> temp;
        if (!cin)
        {
            cout << "There is an illegal input. Please Enter Again" << endl;
            cout << "Enter the first vector v1 = ";
            cin.clear();
            cin.sync();
            index1 = 0; //reset the index
        }
        else
        {
            v1[index1] = temp;
            index1++;
            if (getchar() == '\n') //break when Enter is inputted
                break;
        }
    }
    cin.clear();
    cin.sync();

    cout << "Enter the second vector v2 = ";
    while (1)
    {
        cin >> temp;
        if (!cin)
        {
            cout << "There is an illegal input. Please Enter Again" << endl;
            cout << "Enter the first vector v2 = ";
            cin.clear();
            cin.sync();
            index2 = 0; //clear the index
        }
        else
        {
            v2[index2] = temp;
            index2++;
            if (getchar() == '\n') //break when Enter is inputted
                break;
        }
    }

    if (index1 != index2)
    {
        cout << "The sizes of the vectors do not match" << endl;
    }
    else
    {
        float result;
        auto start = std::chrono::steady_clock::now();
        result = dot(index1, v1, v2);
        auto end = std::chrono::steady_clock::now();
        cout << "The dot product is " << result << endl;
        std::cout << "Dot product calculations took "
                  << std::chrono::duration_cast<std::chrono::microseconds>(end - start).count() << "mus = "
                  << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms ="
                  << std::chrono::duration_cast<std::chrono::seconds>(end - start).count() << "s.\n";
    }
    delete[] v1;
    delete[] v2;
}
