//calculator.cpp
//Name: Weike Fang (22010055)
//credit to Simple Snippet for the function InfixtoPostfix and precedence www.youtube.com/watch?v=dJESbyFR1sU
//remaining: task3,5, 4needmore, double calculation with the floating point
#include <iostream>
#include <string>
#include <stack>
#include <cmath>
#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;
//credit to Simple Snippet
bool isOperator(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^')
    {
        return true;
    }
    else
    {
        return false;
    }
}
int precedence(char c)
{
    if (c == '^')
        return 3;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}
string InfixToPostfix(stack<char> stack, string infix) //convert Infix operation to PostFix
{
    string postfix;
    for (int i = 0; i < infix.length(); i++)
    {
        if ((infix[i] >= 'a' && infix[i] <= 'z') 
        || (infix[i] >= 'A' && infix[i] <= 'Z') 
        || (isdigit(infix[i]))
        ||(infix[i] == '.'))
        {
            postfix += infix[i];
        }
        else if(infix[i] == ' ')
        {
            continue;
        }
        else if (infix[i] == '(')
        {
            postfix += ' '; //added
            stack.push(infix[i]);
        }
        else if (infix[i] == ')')
        {
            postfix += ' '; //added
            while ((stack.top() != '(') && (!stack.empty()))
            {
                char temp = stack.top();
                postfix += temp;
                stack.pop();
            }
            if (stack.top() == '(')
            {
                stack.pop();
            }
        }
        else if (isOperator(infix[i]))
        {
            postfix += ' '; //added
            if (stack.empty())
            {
                stack.push(infix[i]);
            }
            else
            {
                if (precedence(infix[i]) > precedence(stack.top()))
                {
                    stack.push(infix[i]);
                }
                else if ((precedence(infix[i]) == precedence(stack.top())) && (infix[i] == '^'))
                {
                    stack.push(infix[i]);
                }
                else
                {
                    while ((!stack.empty()) && (precedence(infix[i]) <= precedence(stack.top())))
                    {
                        char temp = stack.top();
                        postfix += temp;
                        stack.pop();
                    }
                    stack.push(infix[i]);
                }
            }
        }
    }
    while ((!stack.empty()))
    {
        char temp = stack.top();
        postfix += temp;
        stack.pop();
    }
    return postfix;
}
double operation(double a, double b, char oprt)
{
    if (oprt == '+')
        return a + b;
    else if (oprt == '-')
        return b - a;
    else if (oprt == '*')
        return b * a;
    else if (oprt == '/')
        return b / a;
    else if (oprt == '^')
        return pow(b, a);
    else
        return -1000;
}
double calc(string post)
{
    stack<double> s;
    string temp;
    for (int i = 0; i < post.length(); i++)
    {
        if (isdigit(post[i]) || (post[i] == '.'))
        {
            temp += post[i];
        }
        else if (post[i] == ' ')
        {
            if (!temp.empty())
            {
                s.push(stod(temp)); //stod converts string to double
                temp.clear();
            }
            continue;
        }
        else if (isOperator(post[i]))
        {
            if (!temp.empty())
            {
                s.push(stod(temp)); //stod converts string to double
                temp.clear();
            }
            double a = s.top();
            s.pop();
            double b = s.top();
            s.pop();
            s.push(operation(a, b, post[i]));
        }
    }
    return s.top();
}
void add(char a[], char b[])
{
    int alen = strlen(a), blen = strlen(b), t = 0, i;
    int idx1 = 0, idx2 = 0;
    int a1[202] = {0}, b1[202] = {0};
    string res;
    // char* res;

    for (i = 0; i < alen; i++)
        a1[i + 1] = a[alen - 1 - i] - '0';
    for (i = 0; i < blen; i++)
        b1[i + 1] = b[blen - 1 - i] - '0';
    for (int j = 0; j < alen; j++)
    {
        if (a1[j] == -2)
            idx1 = j;
    }
    for (int j = 0; j < blen; j++)
    {
        if (b1[j] == -2)
            idx2 = j;
    }

    if (idx1 <= idx2)
    {
        int diff = idx2 - idx1;
        int temp[202] = {0};
        for (int j = 1; j <= alen; j++)
            temp[j + diff] = a1[j];
        for (int j = 1; j <= 202; j++)
            a1[j] = temp[j];
    }
    else
    {
        int diff = idx1 - idx2;
        int temp[202] = {0};
        for (int j = 1; j <= blen; j++)
            temp[j + diff] = b1[j];
        for (int j = 1; j <= 202; j++)
            b1[j] = temp[j];
    }
    int idx_diff = (idx1 > idx2) ? idx1 - idx2 : idx2 - idx1;
    alen = (alen > blen) ? alen : blen;
    int idx;
    for (i = 1; i <= alen + idx_diff + 1; i++)
    {
        t = a1[i] + b1[i];
        a1[i] = t % 10;
        if (a1[i + 1] == -2) //if the digit is the floating point
        {
            idx = i + 1;
            a1[i + 2] += t / 10;
            i++;
            continue;
        }
        a1[i + 1] += t / 10;
    }
    while (!a1[i] && i)
        i--;
    int len = i;
    for (; i > 0; i--)
    {
        if (i == idx)
        {
            // res[len-i] = '.';
            cout << '.';
            res += '.';
            continue;
        }
        res += a1[i];
        // res[len - i] = a1[i];
        printf("%d", a1[i]);
    }
    // res[len] = '-1';
    // return res;
}
void substract(char a[], char b[])
{
    int alen = strlen(a), blen = strlen(b), t = 0, i;
    int idx1 = 0, idx2 = 0;
    int a1[202] = {0}, b1[202] = {0};
    // char* res;

    for (i = 0; i < alen; i++)
        a1[i + 1] = a[alen - 1 - i] - '0';
    for (i = 0; i < blen; i++)
        b1[i + 1] = b[blen - 1 - i] - '0';
    for (int j = 0; j < alen; j++)
    {
        if (a1[j] == -2)
            idx1 = j;
    }
    for (int j = 0; j < blen; j++)
    {
        if (b1[j] == -2)
            idx2 = j;
    }

    if (idx1 <= idx2)
    {
        int diff = idx2 - idx1;
        int temp[202] = {0};
        for (int j = 1; j <= alen; j++)
            temp[j + diff] = a1[j];
        for (int j = 1; j <= 202; j++)
            a1[j] = temp[j];
    }
    else
    {
        int diff = idx1 - idx2;
        int temp[202] = {0};
        for (int j = 1; j <= blen; j++)
            temp[j + diff] = b1[j];
        for (int j = 1; j <= 202; j++)
            b1[j] = temp[j];
    }
    int idx_diff = (idx1 > idx2) ? idx1 - idx2 : idx2 - idx1;
    alen = (alen > blen) ? alen : blen;
    int idx;
    for (i = 1; i <= alen + idx_diff + 1; i++)
    {
        t = a1[i] - b1[i];
        if (a1[i + 1] == -2) //if the digit is the floating point
        {
            idx = i + 1;
            t<0 ? (t+=10, a1[i+2]--) : t, a1[i]=t;
            i++;
            continue;
        }
        t<0 ? (t+=10, a1[i+1]--) : t, a1[i]=t;
    }
    while (!a1[i] && i)
        i--;
    int len  = i;
    for (; i > 0; i--)
    {
        if (i == idx)
        {
            // res[len-i] = '.';
            cout << '.';
            continue;
        }
        // res[len-i] = a1[i];
        printf("%d", a1[i]);
    }
    // res[len]= 't';
    // return res;
}
void multiply(char a[], char b[]) // huge integer multiplication
{
    int alen = strlen(a), blen = strlen(b), t = 0, i;
    int a1[202] = {0}, b1[202] = {0};
    // char* res;

    for (i = 0; i < alen; i++)
        a1[i] = a[alen - 1 - i] - '0';
    for (i = 0; i < blen; i++)
        b1[i] = b[blen - 1 - i] - '0';

    int c[404] = {0};
    for (i = 0; i < alen; i++)
    {
        for(int j = 0; j < blen;j++)
        {
            c[i+j] += a1[i] * b1[j];
        }
        for(int k = 0;k<alen+blen;k++)
        {
            if(c[k] >= 10)
            {
                c[k+1] += c[k]/10;
                c[k] %= 10;
            }
        }   
    }
    i = 400;
    while (!c[i] && i)
        i--;
    long long len = i;
    for (; i >= 0; i--)
    {
        //res[len-i] = c[i];
        printf("%d", c[i]);
    }
    //res[len+1] = 't'; // mark the stop
    //return res;
}
void operationLong(char a[], char b[], char oprt)
{
    if (oprt == '+')
        add(a, b);
    else if (oprt == '-')
        substract(a,b);
    else if (oprt == '*')
        multiply(a,b);
}
string longCalc(string post)
{
    stack<string> s;
    string temp;
    for (int i = 0; i < post.length(); i++)
    {
        if (isdigit(post[i]) || (post[i] == '.'))
        {
            temp += post[i];
        }
        else if (post[i] == ' ')
        {
            if (!temp.empty())
            {
                
                s.push(temp); 
                temp.clear();
            }
            continue;
        }
        else if (isOperator(post[i]))
        {
            if (!temp.empty())
            {
                s.push(temp); 
                temp.clear();
            }
            int len1 = s.top().length();
            char str1[200] = {0};
            for(int i = 0; i<len1; i++)
            {
                str1[i] = s.top()[i];
            }
            s.pop();
            int len2 = s.top().length();
            char str2[200] = {0};
            for(int i = 0; i<len2; i++)
            {
                str2[i] = s.top()[i];
            }
            s.pop();
            operationLong(str1, str2, post[i]);
        }
    }
    return s.top();
}
bool containLetter(string str)
{

    for (int i = 0; i < str.length(); i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z'))
            return true;
    }
    return false;
}
string findNum(string str)
{
    string res;
    for (int i = 0; i < str.length(); i++)
    {
        if ((str[i] >= 'a' && str[i] <= 'z') || (str[i] >= 'A' && str[i] <= 'Z') || isOperator(str[i]) || str[i] == '(' || str[i] == ')')
        {
            continue;
        }
        else if (isdigit(str[i]) || str[i] == '.')
        {
            res += str[i];
        }
        else
        {
            res += ' ';
        }
    }
    return res;
}
bool checkLen(string str)
{
    string num = findNum(str);
    bool res = true;
    int count = 0;
    for(int i = 0; i < num.length();i++)
    {
        if(count > 9) //limit for double?
        {
            res = false;
            break;
        }
        if (isdigit(num[i]) || num[i] == '.')
            count ++;
        else if(num[i] == ' ')
        {
            count = 0;
            continue;
        }
    }
    return res;
}
bool isVar(string str)
{
    bool res = true;
    for (int i = 0; i < str.length(); i++)
    {
        if (isdigit(str[i]))
            res = false;
    }
    return res;
}

int main()
{
    string infix, postfix;
    double result;
    vector<int> num;
    vector<string> var;
    stack<char> s;
    cout << "Please enter what you want to calculate (Enter q to quit):" << endl;
    cin >> infix;
    while (infix != "q")
    {
        if (containLetter(infix) && infix.find('=') == string::npos)
        {
            string temp = infix;
            transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
            string num_det = findNum(infix);
            double myDb = stod(num_det);
            if (temp.find('sqrt') != string::npos)
            {
                result = sqrt(myDb);
            }
            else if (temp.find('sin') != string::npos)
            {
                result = sin(myDb);
            }
            else if (temp.find('cos') != string::npos)
            {
                result = cos(myDb);
            }
            else if (temp.find('tan') != string::npos)
            {
                result = cos(myDb);
            }
        }
        else if (infix.find('=') != string::npos)
        {
            string temp = infix;
            while (temp.find('=') != string::npos)
            {
                int idx = temp.find('=');
                string str1 = temp.substr(0, idx);
                string str2 = temp.substr(idx + 1, temp.length());
                if (isVar(str1))
                {
                    var.push_back(str1);
                    num.push_back(stoi(str2));
                }
                else if (isVar(str2))
                {
                    var.push_back(str2);
                    num.push_back(stoi(str1));
                }
                else
                {
                    cout << "Invalid Input!" << endl;
                }
                cin.clear();
                cin.sync();
                cin >> temp;
            }
            int var_sz = var.size();
            int num_sz = num.size();
            for (int i = 0; i < var_sz; i++) //replace the variable with number
            {
                int index;
                string number = to_string(num[i]);
                int len = number.length();
                while (temp.find(var[i]) != string::npos)
                {
                    index = temp.find(var[i]);
                    temp.replace(index, len, number);
                }
            }
            cout << temp << endl;
            postfix = InfixToPostfix(s, temp);
            result = calc(postfix);
        }
        else
        {
            postfix = InfixToPostfix(s, infix);
            cout << "POSTFIX expression: " << postfix << endl;
            if(!checkLen(postfix))
            {
                longCalc(postfix); // deal with many digit calculation
                cout <<endl;
                continue;
            }        
            else
            {
                result = calc(postfix);
            }
        }
        cout << result << endl;
        cin.clear();
        cin.sync();
        cin >> infix;
    }

    return 0;
}
