# CS205 C/C++ Program Design

### Assignment 2

**Name**: 方唯可   **SID**: 22010055

#### Part 1. Analysis & Description

This assignment asked us to design a much better calculator, with functions such as supporting operator precedence and parenthesis in the expression, calling some useful math functions, doing variable calculation, and high-precision calculation.

After some research, I found that the common way to deal with operator precedence is through evaluating Postfix expression equipped with *stack*. As we typically find Infix expression more  comprehensible such as ***a/(b+c)*** , computer finds the postfix expression more readable (in this case, ***a b c / +***). The ***Stack*** data structure has the property of LIFO (last in first out), which allows us to implement Postfix evaluation more easily. Therefore, I wrote a function *InfixToPostfix* to convert Infix expression from the input to Postfix expression and another function to evaluate the Postfix expression. (Credit to Simple Snippets for the function *InfixToPostfix* on [https://www.youtube.com/watch?v=dJESbyFR1sU&pbjreload=101](https://www.youtube.com/watch?v=dJESbyFR1sU&pbjreload=101)).

As for the requirement 3 (variable calculation), my natural intuition is to store the variable (like x,y,z) and values assigned (like 3 if x=3) in two different ***vector***. When the calculation is inputted, we then can substitute variables with the corresponding values, and treat it similarly as in requirement 1 and 2.

The 4th requirement asks us to support some basic math functions in the library <cmath>, such as *sqrt(), cos(), sin()*, etc. The basic idea of mine was also intuitive, as we can just treat the functions as some other operators with the highest precedence. While doing the operation, we can simply call the corresponding function in the <cmath> library.

Requirement 5 poses some challenges to me at first since we have deal with the overflow in even long long int or double. After some research, I found that we could store the values in ***lists***, either integer list or character list, and then evaluate the equation vertically, just as what we learn in primary school. For huge integer calculation, we line up the last digit and then proceeds with our calculation. For floating-point number, we then need to lien up the floating point for addition and subtraction.

#### Part 2. Code

Due to the length of the code (over 500 lines), I hosted my source code at GitHub via xxx. I also uploaded my source code together with this report just in case.

#### Part 3. Result & Verification

Test case #1:

Screen-shot for case #1:

Test case #2:

Screen-shot for case #2:

#### Part 4. Difficulties & Solutions

