# CS205 C/C++ Program Design

### Project 1

**Name**: 方唯可 Weike Fang  **SID**: 22010055

#### Part 1. Analysis & Description

This project asks us to design a function that computes the multiplication of two matrices, with data type being float. We should first test our function by using Input/output and make sure the function does not crash when receiving incorrect input. Then, it asks us to measure the time taken to multiply two matrices containing 200M elements, try to improve the efficiency, and compare it with OpenBLAS function *cblas_sgemm()* .

The first task is straightforward: asking the users to input the values for two matrices (row, column, data), and then calculate the product of the two matrices. Possible crashes include: illegal characters in the input, dimension mismatches, illegal input of data or excess of data. All of the cases are dealt with in the function and explained below.

The second task asks us to measure the time (in *ms*) that the calculation takes for matrices of 200 million elements. To create a float matrices with 200 M elements, I use **new** to assign a block of dynamic memory to the matrices and then use `float r = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));`to assign to each element a floating-point number between 0 and 1 (for testing). Since the brute-force method takes too much time, I start with matrices of lower dimensions, and try enhancing the efficiency step by step.

To improve the efficiency of the function, I tried the methods I used in the previous assignment (1. dividing the tasks into 4 to reduce the access of memory 2. Adding compiling flags such as *-Ofast -O3 -march=native*, etc.). Both of them improves the brute-force method, but still not enough to calculate the 200M-element matrices. By a little research online, a simple yet efficient method is to **swap two loops（j loop and k loop)**, allowing the program to access the memory continuously and reducing the time complexity by a degree.

Furthermore, as inspired from Lecture 7 about improving the dot product using intrinsics (SIMD) and parallel operations (openmp) and author lcd's idea to use blocks lhd(https://gitee.com/optimization/dgemm/tree/master). I further improve the efficiency of my code without sacrificing the accuracy, to around **19 s** for computing two matrices with a total of 209 M elements, comparable to OpenBLAS's operation, which takes **4 s** to arrive at the result. 



#### Part 2. Code

I hosted my source codes on GitHub and they can be viewed via https://github.com/ColinFang1009/sustechcpp/tree/master/project1

"include" and "lib" directories are necessary for OpenBLAS usage. matrixIO.cpp is used for requirement 1 and 2 for Input/Output calculation. {main.cpp, matrixop.hpp, matrixop.cpp} are for the remaining requirements to enhance the efficiency and compare the speed with OpenBLAS. There are six separate matrix multiplication functions (matmul1 to matmul6) in the matrixop.hpp and matrixop.cpp).

The "struct" folder include the corresponding codes that uses Matrix Structure in the calculation.



#### Part 3. Result & Verification

I/O part

**Test case #1**: If two matrices (specified row and column) are entered, the result of the multiplication will be shown.

```
Input:
m1:row = 2 column = 3 data = 1 2 3 4 5 6
m2:row = 3 column = 4 data = 1 2 3 4 5 6 7 8 9 10 11 12
Output:
Product:
38 44 50 56
83 98 113 128
```

Screen-shot for case #1:

![IO1](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\IO1.PNG)

**Test case #2**: If row/column input is not a positive integer, the program will prompt the user to enter again.

```
Row = -2
The dimension of the matrix should be a positive integer. Enter again:2
Column = -2.0
The dimension of the matrix should be a positive integer. Enter again:2
Row = a
The dimension of the matrix should be a positive integer. Enter again:2
Column = *=1
The dimension of the matrix should be a positive integer. Enter again:2
Data1:1 2 3 4 Data2: 1 0 0 1
Product:
1 2
3 4
```

Screen-shot for case #2:

![IO2](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\IO2.PNG)

**Test case #3**: If the data entered contain illegal character (letters, punctuations, etc.), the program will prompt the user to make another input. If the data from the input exceeds its dimension, the excess will not be taken.

```
Input: 
(2*3) 
Data1: 1 2 3 4 a 2
There is an illegal input. Please Enter Again.
1 2 3 4 5 6
(3*2)
Data2: 1 2 3 4 5 6 7
The data exceeds the expected length
Output: 
M1=1 2 3;4 5 6
M2= 1 2 3;4 5 6
Product =
22 28
49 64
```

Screen-shot for case #3:

![IO3](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\IO3.PNG)

**Test case #4**: If the dimensions of the two matrices do not fit, the program will report the error and exit.

```
Enter the first float matrix m1
Row = 4
Column = 5
Enter the second float matrix m2
Row = 6
Column = 4
The sizes of the matrices do not match
```

Screen-shot for case #4:

![IO4](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\IO4.PNG)

**Efficiency improvement and Comparison with OpenBLAS**

**Test case #1**: Brute-force function (1st version) for matrices with 2 million element (not 200M because it takes around 2 hours)

```c++
void matmul2(matrix m1, matrix m2, matrix &result)
{
    for(int i=0;i<m1.row;i++)
        for(int j=0;j<m2.column;j++)
            for(int k=0;k<m1.column;k+=1)
                result.mat[i][j]+=m1.mat[i][k] * m2.mat[k][j];  
}
Output:
Matrix product calculations took 10s. (2M elements each)
```

Screen-shot for case #1:

![image-20201112170641686](C:\Users\colin\AppData\Roaming\Typora\typora-user-images\image-20201112170641686.png)

The brute force method takes around 10 second. Since the operation is simple (multiplication and addition), the majority of the time spent is accessing the memory. Therefore, a natural improvement (from assignment 3) is to reduce the times it accesses the 2D array.

**Test case #2**: Improvement by introducing temp to reduce access to memory.

```c++
void matmul2(matrix m1, matrix m2, matrix &result)
{
    float temp1=0, temp2=0, temp3=0, temp4=0;
    for(int i=0;i<m1.row;i++)
    {
        for(int j=0;j<m2.column;j++)
        {
            for(int k=0;k<m1.column;k+=4)
            {
                temp1 += m1.mat[i][k] * m2.mat[k][j];
                temp2 += m1.mat[i][k+1] * m2.mat[k+1][j];
                temp3 += m1.mat[i][k+2] * m2.mat[k+2][j];
                temp4 += m1.mat[i][k+3] * m2.mat[k+3][j];
            }
            result.mat[i][j] = temp1 + temp2 + temp3 + temp4;
        }
    }
}
Output:
Matrix product calculations took 5s. (2M elements each)
```

Screen-shot for case #2:

![temp](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\temp.PNG)

The matrix multiplication function spends most of its time retrieving data from the (dynamic) memory since the function does little actual and straightforward computation. Thus, the efficiency will be very much dependent on its memory access (bandwidth).

The idea reduces the time accessing the matrix (instead, just add on to the temporary float). It also represents the naive approach for SIMD (Single Instruction Multiple Data) operation, which allows us  to access and process multiple data simultaneously

Such a trick (by limiting accessing of the result matrix) reduces the time taken for multiplying two 2M-element matrices to 5 s. Still, it's too slow to multiply two 200M-element matrices with this approach. 



**Test case #3**: Compile with chosen optimization flags (Let the compiler to its job!)

```
Compile(my method):g++ -Ofast -march=native -funroll-loop
Compile(Prof.Yu's approach): g++ -O3 -std=c++11
Output:
Dot product calculations took 2600ms=2s. (2M elements each)
```

Screen-shot for case #3:

![allflag](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\allflag.PNG)

After permuting the compliers'  flags, I find that *-O3* and *-Ofast* have similar effect on efficiency, reducing the time taken ***from ~5.6s to ~2.6s***. The other 2 flags have very little effect in this case (compared with that in dot product). The time taken fluctuate only a little. 

**Test case #4**: Simple trick: switch the order of the for loops

```C++
for(int i=0;i<m1.row;++i)
    for(int k=0;k<m1.column;++k)
        s=m1.mat[i][k];
        for(int j=0;j<m2.column;++j)
                result.mat[i][j]+= s * m2.mat[k][j];

Output:
Matrix product calculations took 364ms.
```

Screen-shot for case #4:

![switchorder](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\switchorder.PNG)

With this little trick (together with the compiling optimization flag), the speed enhances almost by 10 times. Time taken for the calculation decreases from 2700 ms to around 350 ms.

This method works due to how matrices (2-D arrays) are stored in the memory. 

Normal (ijk): 2-D arrays stored by rows. For each element in the result, we access m1's element continuously (in the same row), but m2's element discretely (accessing element of the same column). For each element, we switch rows in m1 and m2 for (n+1) times.

Improved(ikj): we avoid accessing m2's elements (1-D arrays) discretely. When we calculate the first row of our resulting matrix, we fix k=0, obtain the first entry of m1[0], and access m2's first row continuously for calculation. 

For matrices with 20 M elements for each, the calculation takes around **35 s**, closer to our goal for matrices with 200M elements 

**More Improvement and Comparison**

Since accessing the "data" float pointer in the Matrix Structure takes additional time, I decided to take the input of my function to be pointers to an float array. Looking at OpenBLAS *cblas_sgemm()* function, it takes in 1-D arrays as inputs, so I use 1-D array for my data for convenience. This also reduces the calculation time by using 1-D arrays instead of 2-D, as shown by experiments.

It remains to check whether the calculation is accurate enough, as we don't know the correct result given two randomized  matrices. Thus, I then wish to compare my result with OpenBLAS function to see whether the result is accurate and compare the time taken (efficiency).

Additional: Calculate using OpenBLAS and compare the results

```C++
void matCompare(size_t r1, size_t c1,size_t r2, size_t c2, float *m1, float *m2)
This function compares two matrices (M1:r1*c1, M2:r2*c2). If their dimensions align, we compare each element, calculate their percentage difference, and print the total average percentage difference.(Actual code can be viewed in the matrixop.cpp file on GitHub)
Using OpenBLAS
#include <cblas.h>
cblas_sgemm(CblasRowMajor, CblasNoTrans, CblasNoTrans, r1, c2, c, 1.0, m1, c, m2,c2 , 0.0, res, c2);
compile: g++ -o xxx xxx.cpp xxx.cpp -I ./include -L ./lib -lopenblas ...
```

Revisit case: Compare the "Swap j k" function with OpenBLAS

```C++
void matmul2(size_t r1, size_t c, size_t c2, float * m1, float * m2, float * result); //swap j and k loop
compile: g++ -o xxx xxx.cpp xxx.cpp -I ./include -L ./lib -lopenblas -O3
```

![matmul2](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul2.PNG)

As we can see from the result, swapping the j and k loop and compiling it with *-O3* flag reduces the time greatly. For the 2048*2048 case, it takes 2009 ms and is 54 times slower than OpenBLAS (compared with OpenBLAS, 37 ms).

**Test case #5**: Using  AVX intrinsics to vectorizing our calculation (Single Instruction Multiple Data, SIMD), inspired from Lecture 7 

```C++
void matmul3(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
	//m1: r1*c, m2: c*c2, result: r1*c2
    //each _mm256 can store 8 float,(=8*4 byte = 256bit)
    for (size_t i = 0; i < r1; i ++) 
	{
		for (size_t j = 0; j < c2; j+=8) 
		{
            __m256 c0 = _mm256_load_ps(result+i*c2+j); /* c0 = Cij*/
			for (size_t k = 0; k < c; k++) 
			{
				c0 = _mm256_add_ps(c0,
					_mm256_mul_ps(_mm256_load_ps(m1+i*c+k),
						_mm256_broadcast_ss(m2+k*c2+j)));
			}
			_mm256_store_ps(result+i*c2+j, c0);  // Cij = c0
		}
	}
}

Comparison with OpenBLAS, two 2048*2048 matrices
Compiling flag: -O3 -mavx2 -I ./include -L ./lib -lopenblas
The OpenBLAS Matrix product calculations took 42195mus = 42ms =0s.
Intrinsics Matrix product calculations took 19779325mus = 19779ms =19s.
The percentage difference is around 7.91496e-06 
```

As we can see from the result, using AVX intrinsics to vectorizing our computation gives very accurate results, with average percentage difference only around 7.91e-06.

Surprisingly, this function runs slower than the previous one, taking around 19 s to compute the product of two 2048*2048 matrices. Part of the reason is that we do not reduce the number of accesses to the memory (as what we did in the "swap j and k" case). Although the function is faster than the brute force method, there are still much space to improve.

Screen-shot for test case #5:

![matmul3](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul3.PNG)

**Test case #6**: Using  *arrays* of AVX intrinsics for vectorization. Inspired by lhd(https://gitee.com/optimization/dgemm/tree/master)

```C++
#define UNROLL 4
void matmul4(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
	for (size_t i = 0; i < r1; i ++)
		for (size_t j = 0; j < c2; j+= 8*UNROLL)
        {
			__m256 ca[UNROLL]; //array containing UNROLL number of __m256 element
			for (int x = 0; x < UNROLL; x++) {
				ca[x] = _mm256_load_ps(result+i*c2+x*8+j);
			}
			for (size_t k = 0; k < c; k++) {
				__m256 b = _mm256_broadcast_ss(m2+k*c2+j);
				for (int x = 0; x < UNROLL; x++) {
					ca[x] = _mm256_add_ps(ca[x],
						_mm256_mul_ps(_mm256_load_ps(m1+i*c+k+x*8),
							b));
				}
			}
			for (int x = 0; x < UNROLL; x++) {
				_mm256_store_ps(result+i*c2+x*8+j, ca[x]);
			}
		}
}
Comparison with OpenBLAS, two 2048*2048 matrices
The OpenBLAS Matrix product calculations took 39715mus = 39ms =0s.
Matmul4 Matrix product calculations took 4121862mus = 4121ms =4s.
The percentage difference is around 3.47245e-05
```

If we use __m256 array with 4 elements to unroll, we have further reduced the times to access the memory. As we can see from the result, this method reduces the multiplication of two 2048*2048 matrices to around 4 s (compared with 39 ms using OpenBLAS, 100 times slower). Furthermore, the percentage difference between the OpenBLAS result and the output of the function is still very low.

If we unroll the intrinsics more (i.e. using __m256 array with 8/16/32 elements), we can further reduce the time

Screen-shot for case #6

![matmul4](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul4.PNG)

UNROLL = 4

![matmul4_8](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul4_8.PNG)

UNROLL = 8

![matmul4_16](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul4_16.PNG)

UNROLL = 16

As we can see from the screen-shots, if we increase the size of our __mm256 array, we can improve our efficiency even more (4 s to 3 s to 2 s). The time stops decreasing when I set UNROLL to be 32 in this 2048*2048 case. However, this is at the expense of some accuracy, as the average percentage difference keeps rising. 

Therefore, we should take different values for UNROLL given different sizes of our matrices. For example, if our matrices are around 100 M, we can take UNROLL to be 32 or even more (comparable to the sizes).

**Test case #7**: Using cache blocking to divide the huge matrices to sub matrices and calculate each independently. Inspired by lhd (https://gitee.com/optimization/dgemm/tree/master)

```c++
#define UNROLL 4
#define BLOCKSIZE 64
static inline void do_block_f(size_t r1, size_t c, size_t c2, int si, int sj, int sk,float *A, float *B, float *C); //calculate the block, details on GitHub
void matmul5(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result); //cache blocking, divide the matrices into submatrices
{
    for (int sj = 0; sj < c2; sj += BLOCKSIZE) 
		for (int si = 0; si < r1; si += BLOCKSIZE) 
			for (int sk = 0; sk < c; sk += BLOCKSIZE) 
				do_block_f(r1,c,c2, si, sj, sk, m1, m2, result);

}
Comparison (8192*8192 matrices, a total of 134 M)
The OpenBLAS Matrix product calculations took 2520164mus = 2520ms =2s.
Matmul4 Matrix product calculations took 60970869mus = 60970ms =60s.
The percentage difference is around 2.27074e-06
```

This is the essence of the **Staissen algorithm**, where we divide the huge matrices into pieces and calculate each separately. For each separate block, we repeat our **matmul4()** function to use __mm256 arrays for vectorization. 

From experiment, I find (UNROLL=4, BLOCKSIZE=64) gives a relatively fast result, enhancing the efficiency by 3 to 4 times. Since our choice of UNROLL and BLOCKSIZE are powers of 2, I also set the dimensions of matrices to be powers of 2 to avoid crashing. The efficiency enhances by **three to four times**. (OpenBLAS takes 2 s while the matmul5() function takes 60 s for the multiplication).

Screen-shot for test case #7

![matmul5](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul5.PNG)

**Test case #8**: Using cache blocking together with omp parallel, as inspired from Lecture 7.

```c++
#include <omp.h> //parallel
void matmul6(size_t r1, size_t c, size_t c2, float *m1, float *m2, float *result)
{
#pragma omp parallel for
	for (int sj = 0; sj < c2; sj += BLOCKSIZE) 
		for (int si = 0; si < r1; si += BLOCKSIZE) 
			for (int sk = 0; sk < c; sk += BLOCKSIZE) 
				do_block_f(r1,c,c2, si, sj, sk, m1, m2, result);
}

Compile:g++ -o matrixop matrixop.cpp main.cpp -O3 -mavx2 -fopenmp  -I ./include -L ./lib -lopenblas
Comparison (multiply two 10240*10240 matrices, a total of 209 M)

```

As inspired in class, we can use <omp.h> to do calculation in parallel, i.e. doing several computations at the same time. Since our PCs have multiple CPU cores and excess threads to be used, we can use this method to optimize our function's efficiency (multi-threading). With this little trick, the matmul6() function has another 6 times improvement in efficiency. For the multiplication of two 10240*10240 matrices, the function takes 19 s (19938 ms), only around **4 to 5 times ** slower than OpenBLAS function (4325 ms = 4 s).

Furthermore, as indicated by the matCompare() function , the average percentage difference remains to be low (1.4 e-6), meaning that we don't have a crash or sacrifice of accuracy in this case.

Screen-shot for case #8:

![matmul6](C:\Users\colin\Desktop\SUSTech\cpp\project1\Project1Report\matmul6.PNG)

#### Part 4. Difficulties & Solutions

Difficulty 1: Preliminary enhancement of the brute-force method.

Solution: 1: From some research online (https://zhuanlan.zhihu.com/p/146250334?utm_source=wechat_session&utm_medium=social&utm_oi=715089843582943232&utm_campaign=shareopn), I learn that a simple trick to swap two loops in between can reduce the time by a lot.

Difficulty 2: Ways to use AVX intrinsics in the matrix multiplication case. Cannot find a way to load a column of elements into the __m256 type.

Solution: Use **_mm256_broadcast_ss()** to copy a float element 8 times into a __m256 type, and continue the operation. 

Difficulty 3: While dividing the matrices into blocks, I find it hard to find suitable BLOCKSIZE and UNROLL.

Solution: Experimenting different combinations to see which one gives the fastest computation without sacrificing much accuracy.

Difficulty 4: Confusion with the parameters in the cblas_sgemm() function.

Solution: Read the OpenBLAS users manual and follow an example online.

Difficulty 5: Compare the result from OpenBLAS and my functions.

Solution: Formulate a matCompare function to compare two matrices element-wise and return/print the average percentage uncertainty.

Difficulty 6: Final improvement using openmp

Solution: Put #pragma omp parallel for at the front of the for loops.

Difficulty 7 (I/O): dealing with possible crashes like illegal characters and data excess.

Solution: Ideas are derived from previous assignments to deal with illegal characters. When excessive data are entered, we add an indicator **index** to stop taking inputs when the data are full.