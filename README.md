# Catool
A technical computing tool.

# Introduction
The library was inspired by Octave. Catool is a computing toolbox written in c++.  
Catool provide an easy-used technical computing c++ environment.  
Cuda or opencl acceleration will be added in latter versions.


# Compatibility

These compilers which have been tested are shown in the following list.

* Visual C++ 2015 on Windows (32/64-bit)
* Mingw 4.9.2 on Windows (32-bit)


# Usage

## Output
This simple example is 'hello world'.

```cpp
#include"MainToolbox\Types.h"
int main()
{
    catool::main_toolbox::disp("hello world!");
    return 0;
}

```

## Create a array

```cpp
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
int main()
{
    catool::main_toolbox::Array<int> intArry=ones<int>(100);
    catool::main_toolbox::disp(intArray);
    return 0;
}
```

# Function index

## Fundamentals

### Array and matrix
`zeros`	Create array of all zeros  
`ones`	Create array of all ones  
`rand`	Uniformly distributed random numbers  
`true`	Logical 1 (true)  
`false`	Logical 0 (false)  
`eye`	Identity matrix  
`diag`	Create diagonal matrix or get diagonal elements of matrix  
`blkdiag`	Construct block diagonal matrix from input arguments  
`cat`	Concatenate arrays along specified dimension  
`horzcat`	Concatenate arrays horizontally  
`vertcat`	Concatenate arrays vertically  

`linspace`	Generate linearly spaced vector  
`logspace`	Generate logarithmically spaced vector  
`meshgrid`	2-D and 3-D grids  


`length`	Length of largest array dimension  
`size`	Array size  
`ndims`	Number of array dimensions  
`numel`	Number of array elements  
`isscalar`	Determine whether input is scalar  
`isvector`	Determine whether input is vector  
`ismatrix`	Determine whether input is matrix  
`isrow`	Determine whether input is row vector  
`iscolumn`	Determine whether input is column vector  
`isempty`	Determine whether array is empty  

`sort`	Sort array elements  
`flip`	Flip order of elements  
`fliplr`	Flip array left to right  
`flipud`	Flip array up to down  
`rot90`	Rotate array 90 degrees  
`transpose`	Transpose vector or matrix  
`ctranspose`	Complex conjugate transpose  
`reshape`	Reshape array
`squeeze`	Remove singleton dimensions  

## Elementary Math

### Arithmetic

`plus`	Addition  
`uplus`	Unary plus  
`minus`	Subtraction  
`uminus`	Unary minus  
`times`	Element-wise multiplication  
`rdivide`	Right array division  
`ldivide`	Left array division  
`power`	Element-wise power  
`mtimes`	Matrix Multiplication 

`cumprod`  Cumulative product  
`cumsum`	Cumulative sum  
`diff`	Differences and Approximate Derivatives  
`movsum`	Moving sum  
`prod`	Product of array elements  
`sum`	Sum of array elements   


`ceil`	Round toward positive infinity  
`fix`	Round toward zero  
`floor`	Round toward negative infinity<br/>
`mod`	Remainder after division (modulo operation)  
`rem`	Remainder after division  
`round`	Round to nearest decimal or integer  

### Trigonometry

`sin`	Sine of argument in radians  
`sind`	Sine of argument in degrees  
`asin`	Inverse sine in radians  
`asind`	Inverse sine in degrees  
`sinh`	Hyperbolic sine of argument in radians  
`asinh`	Inverse hyperbolic sine  
  
`cos`	Cosine of argument in radians  
`cosd`	Cosine of argument in degrees  
`acos`	Inverse cosine in radians  
`acosd`	Inverse cosine in degrees   
`cosh`	Hyperbolic cosine  
`acosh`	Inverse hyperbolic cosine  
  
`tan`	Tangent of argument in radians  
`tand`	Tangent of argument in degrees  
`atan`	Inverse tangent in radians  
`atand`	Inverse tangent in degrees  
`atan2`	Four-quadrant inverse tangent  
`atan2d`	Four-quadrant inverse tangent in degrees  
`tanh`	Hyperbolic tangent  
`atanh`	Inverse hyperbolic tangent  
  

### Exp and Log
`exp`	Exponential  
`log`	Natural logarithm  
`log10`	Common logarithm (base 10)  
`log2`	Base 2 logarithm and dissect floating-point numbers into exponent and mantissa  
`sqrt`	Square root  


### Complex Numbers
`abs`	Absolute value and complex magnitude  
`angle`	Phase angle  
`conj`	Complex conjugate  
`sign`	Sign function (signum function)  

### Discrete Math
`gcd`	Greatest common divisor  
`lcm`	Least common multiple  
`rat`	Rational fraction approximation  
`rats`	Rational output  


### Constants
`Inf`	Infinity  
`pi`	Ratio of circle's circumference to its diameter  
`natural constant`   
`euler constant`   
`NaN`	Not-a-Number  
`isfinite`	Array elements that are finite  
`isinf`	Array elements that are infinite  
`isnan`	Array elements that are NaN  

## Linear Algebra
`mldivide`	Solve systems of linear equations Ax = B for x  
`mrdivide`	Solve systems of linear equations xA = B for x  
`inv`	Matrix inverse  
`pinv`	Moore-Penrose pseudoinverse of matrix  


`lu`  LU matrix factorization  

`transpose`	Transpose vector or matrix  
`ctranspose`	Complex conjugate transpose  
`mtimes`	Matrix Multiplication  
`mpower`	Matrix power  

`rank`	Rank of matrix  
`trace`	Sum of diagonal elements  



## Random Number Generation

`rand`	Uniformly distributed random numbers  
`randn`	Normally distributed random numbers  
`randi`	Uniformly distributed pseudorandom integers  

`rng`	Control random number generation  

## Graphics
Attension: this function needs GnuPlot interface.


## Data Import and Analysis

### Workspace Variables and MAT-Files
`load`	Load variables from file into workspace  

### Data Import and Export 

`audioread`	Read audio file  
`audiowrite`	Write audio file  

`imwrite`	Write image to graphics file  

### Descriptive Statistics
`min`	Smallest elements in array  
`max`	Largest elements in array  
`bounds`	Smallest and largest elements  
`mean`	Average or mean value of array  
`median`	Median value of array  


## Sparse Matrices
`spalloc`	Allocate space for sparse matrix  
`spdiags`	Extract and create sparse band and diagonal matrices  coming  
`speye`	Sparse identity matrix  
`sprand`	Sparse uniformly distributed random matrix coming  
`sprandn`	Sparse normally distributed random matrix coming  
`sparse`	Create sparse matrix  

`issparse`	Determine whether input is sparse  coming  
`nnz`	Number of nonzero matrix elements  

