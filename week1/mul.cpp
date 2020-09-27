//mul.cpp
//Name: Weike Fang (22010055)
// Credit to https://www.cnblogs.com/tonglingliangyong/p/3908463.html for checking c-input datatype
// long long int(8byte/64bits ~2^63-1) is good enough for the product of two 9- or 10-digit integers
#include <iostream>
#include <iomanip>
#include <string>
#include <string.h>
#include <algorithm>

using namespace std;

int main()
{
    cout << "Integer Multiplier!" << endl;
    cout << "Please input two integers separated with a space." << endl;
    long long int a, b;
    while (1)
    {
        cin >> a >> b;
        if (cin.fail()) // or !cin
        {
            cout << "The input should be 2 integers separated by a space. Enter Again" << endl;
            cin.clear();
            cin.sync();
        }
        else
        {
            long long int product = a * b;
            cout << "How would you like your answer be presented? Decimal or Scientific." << endl;
            string format;
            while (1)
            {
                cin >> format;
                transform(format.begin(), format.end(), format.begin(), ::tolower);
                string d = "decimal";
                string s = "scientific";
                if (format.compare(d) == 0)
                {
                    cout << "The product of " << a << " and " << b << " is ";
                    cout << dec << product << endl;
                    break;
                }
                else if (format.compare(s) == 0)
                {
                    cout << "The product of " << a << " and " << b << " is ";
                    cout << scientific << double(product) << endl;
                    break;
                }
                else
                {
                    cout << "The input should be either Scientific or Decimal. Enter Again" << endl;
                    cin.clear();
                    cin.sync();
                }
            }

            break;
        }
    }
    return 0;
}
