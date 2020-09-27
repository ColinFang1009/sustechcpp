# CS205 C/C++ Program Design

### Assignment 2

**Name**: 方唯可   **SID**: 22010055

#### Part 1. Analysis & Description

This assignment asked us to design a much better calculator, with functions such as supporting operator precedence and parenthesis in the expression, calling some useful math functions, doing variable calculation, and high-precision calculation.

After some research, I found that the common way to deal with operator precedence is through evaluating Postfix expression equipped with *stack*. As we typically find Infix expression more  comprehensible such as ***a/(b+c)*** , computer finds the postfix expression more readable (in this case, ***a b c / +***). The ***Stack*** data structure has the property of LIFO (last in first out), which allows us to implement Postfix evaluation more easily. Therefore, I wrote a function *InfixToPostfix* to convert Infix expression from the input to Postfix expression and another function to evaluate the Postfix expression. (Credit to Simple Snippets for the function *InfixToPostfix* on [https://www.youtube.com/watch?v=dJESbyFR1sU&pbjreload=101](https://www.youtube.com/watch?v=dJESbyFR1sU&pbjreload=101)).

As for the requirement 3 (variable calculation), my natural intuition is to store the variable (like x,y,z) and values assigned (like 3 if x=3) in two different ***vector***. When the calculation is inputted, we then can substitute variables with the corresponding values, and treat it similarly as in requirement 1 and 2.

The 4th requirement asks us to support some basic math functions in the library <cmath>, such as *sqrt(), cos(), sin()*, etc. The basic idea of mine was also intuitive, as we can just treat the functions as some other operators with the highest precedence. While doing the operation, we can simply call the corresponding function in the <cmath> library.

Requirement 5 poses some challenges to me at first since we have deal with the overflow in even long long int or double. After some research, I found that we could store the values in ***lists***, either integer list or character list, and then evaluate the equation vertically, just as what we learn in primary school. For huge integer calculation, we line up the last digit and then proceeds with our calculation. For floating-point number, we then need to lien up the floating point for addition and subtraction. (Credit to https://blog.csdn.net/weixin_41162823/article/details/80044079 for tutorial on high-precision integer addition and subtraction, inspired me to implement floating-point addition, subtraction, and high-precision multiplication).

#### Part 2. Code

Due to the length of the code (over 500 lines), I hosted my source code at GitHub via [https://github.com/ColinFang1009/sustechcpp/tree/master/week2](https://github.com/ColinFang1009/sustechcpp/tree/master/week2). I also uploaded my source code together with this report just in case.

#### Part 3. Result & Verification

Test case #1:

```
Input:5+2*3-1
Output:10
```

Screen-shot for case #1:

![case1](C:\Users\colin\Desktop\SUSTech\cpp\SUSTech_cpp_HW\sustechcpp\week2\case1.png)

Test case #2:

```
Input:(5+2)*3-12/(2+4)
Output:19
```

Screen-shot for case #2:

![case2](C:\Users\colin\Desktop\SUSTech\cpp\SUSTech_cpp_HW\sustechcpp\week2\case2.png)

Test case #3:

```
Input:
x=3
y=6
z=2
x+y*z-2
Output:13
```

Screen-shot for case #3:

![case3](C:\Users\colin\Desktop\SUSTech\cpp\SUSTech_cpp_HW\sustechcpp\week2\case3.png)

Test case #4:

```
Input:sqrt(3.0)
Output:1.73205
Input:cos(3.14) //in radian
Output:-0.999999
Input:sin(1.5)
Output:0.997485 //1.5 rad ~ pi/2 ~90°
```

Screen-shot for case #4:

![case4](C:\Users\colin\Desktop\SUSTech\cpp\SUSTech_cpp_HW\sustechcpp\week2\case4.png)

Test case #5: high-precision addition

```
Input: 99999999999999999999999999.22222222222222222222+1.0
Output:100000000000000000000000000.22222222222222222222
```

Screen-shot for case #5:

![case5](C:\Users\colin\Desktop\SUSTech\cpp\SUSTech_cpp_HW\sustechcpp\week2\case5.png)

Test case #6: high-precision multiplication

```
Input:123456789789456123*987654321123456789
Output:121932631907586598968511722001969047
```

Such operation is something that I failed to implement in assignment 1. After figuring out high-precision addition and subtraction, I found huge number multiplication can be done in a similar manner.

Screenshot for case #6:

![case6](C:\Users\colin\Desktop\SUSTech\cpp\SUSTech_cpp_HW\sustechcpp\week2\case6.png)

#### Part 4. Difficulties & Solutions

Difficulty 1:Evaluating the postfix expression

Solution: Create a stack, read the postfix expression one by one, and push the number (either double or integer) to the stack. When encountering an operator, take out the first element on the stack and pop, then take out the second element and pop, implement the operation on the two number/characters.

Difficulty 2: High-precision addition and subtraction, lining up the floating point

Solution: Use list to store the number in the reverse order, find the index of floating point (if integer, floating-point will be immediately after the last digit), shifts the number so that the floating point can line up, and finally evaluate the expression as how we do vertical calculation. Print out the result in the reverse order.

Difficulty 3: Huge-digit multiplication

Solution: Store the two numbers in a list in the reverse order (say, a1[] and b1[]), create a longer list to store the result (say c[]), observe that when we run through a1 and b1, **c[i+j] += a1[i] * b1[j]**. If the element in c[k] exceeds 10, we take ***c[k] %=10*** for the digit, and add the remaining ***c[k]/10*** to the higher digit.

Difficulty 4: Continuously do the calculation, exit the calculator by inputting 'q'

Solution: 

```
    while (infix != "q")
    {
        if (***)
        {
			***
        }
        else if (***)
        {
			***
        }
        else
        {
            ***
        }
        cout << result << endl;
        cin.clear();
        cin.sync();
        cin >> infix;
    }
```

Difficulty 5: Variables' value assignment, and calculation

Solution: Use two vectors, ***vector<int> num, vector<char> var***, the former for value storing and the latter for variable storing. When an infix expression is inputted, I first convert it to Postfix expression, and then substitute each element in ***var*** with the corresponding value in ***num***, and then do the calculation.

Difficulty 6: Operator precedence for high-precision calculation (may cause overflow if we use int/double)

Solution: Instead of using a double stack to evaluate the postfix expression, I use a string stack in the funcion longCalc(string post), altering some parts in the body, and eventually return a string/char[] to be further calculated.