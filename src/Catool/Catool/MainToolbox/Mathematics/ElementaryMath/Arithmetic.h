#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H

#include<cmath>
#include"../../../Types.h"
#include"../../Fundamentals/Array.h"
namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			//using namespace ::ca;
			/*
			C = A + B adds arrays A and B and returns the result in C.
			C = plus(A,B) is an alternate way to execute A + B, but is rarely used.
			It enables operator overloading for classes.
			*/
			template<class T,class U>
			inline auto plus(const T& a, const U& b)-> decltype(a + b)
			{
				return a + b;
			}
			template<class T, class U>
			inline Array<T> plus(const Array<T>& a, const Array<U>& b)
			{
				if (a.get_dim()==b.get_dim())
				{
					Array<T> result(a);
					for (int i = 0; i < a.size(); ++i)
					{
						result[i] = a[i] + b[i];
					}
					return result;
				}
				else
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
			}
			template<class T, class U>
			inline Array<T> plus(const Array<T>& a, const U& b)
			{
				Array<T> result(a);
				for (auto &each : result)
				{
					each += b;
				}
				return result;
			}

			template<class T, class U>
			inline Array<T> plus(const U& a, const Array<T>& b)
			{
				Array<T> result(b);
				for (auto &each : result)
				{
					each += a;
				}
				return result;
			}

			/*
			C = +A returns array A and stores it in C.
			C = uplus(A) is an alternate way to execute +A, but is rarely used.
			It enables operator overloading for classes.
			*/
			inline double uplus(double a)
			{
				return a;
			}
			template<class T>
			inline Array<T> uplus(const Array<T>& a)
			{
				return a;
			}
			/*
			C = A - B subtracts array B from array A and returns the result in C.
			C = minus(A,B) is an alternate way to execute A - B, but is rarely used.
			It enables operator overloading for classes.
			*/
			template<class T,class U>
			inline auto minus(const T& a, const U& b)->decltype(a-b)
			{
				return a - b;
			}
			template<class T,class U>
			inline Array<T> minus(const Array<T>& a, const Array<U>& b)
			{
				if (a.get_dim() == b.get_dim())
				{
					Array<T> result(a);
					for (int i = 0; i < a.size(); ++i)
					{
						result[i] = a[i] - b[i];
					}
					return result;
				}
				else
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
			}
			template<class T, class U>
			inline Array<T> minus(const Array<T>& a, const U & b)
			{
				Array<T> result(a);
				for (auto &each : result)
				{
					each -= b;
				}
				return result;
			}
			template<class T, class U>
			inline Array<T> minus(const U & a, const Array<T>& b)
			{
				Array<T> result(b);
				for (auto &each : result)
				{
					each -= a;
				}
				return result;
			}
			/*
			C = -A negates the elements of A and stores the result in C.
			C = uminus(A) is an alternative way to execute -A, but is rarely used.
			It enables operator overloading for classes.
			*/
			inline double uminus(double a)
			{
				return -a;
			}
			template<class T>
			inline Array<T> uminus(const Array<T>& a)
			{
				Array<T> result(a);
				for (auto &each : result)
				{
					each=-each;
				}
				return result;
			}
			/*
			C = A.*B multiplies arrays A and B element by element and returns the result in C.
			C = times(A,B) is an alternate way to execute A.*B, but is rarely used.
			It enables operator overloading for classes.
			*/
			template<class T>
			inline Array<T> times(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result(a);
				if (a.get_dim() != b.get_dim())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i]=a[i] * b[i];
				}
				return result;
			}
			/*
			x = A./B divides each element of A by the corresponding element of B.
			*/
			template<class T>
			inline Array<T> rdivide(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result(a);
				if (a.get_dim() != b.get_dim())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i]=a[i] / b[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> rdivide(const Array<T>& a, const T & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i]=a[i] / b;
				}
				return result;
			}
			template<class T>
			inline Array<T> rdivide(const T &  a, const Array<T>& b)
			{
				Array<T> result(b);
				for (unsigned int i = 0; i < b.size(); ++i)
				{
					result[i]=a / b[i];
				}
				return result;
			}

			/*
			x = B.\A divides each element of A by the corresponding element of B.
			*/
			template<class T>
			inline Array<T> ldivide(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result(a);
				if (a.get_dim() != b.get_dim())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i]=b[i] / a[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> ldivide(const Array<T>& a, const T & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i]=b / a[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> ldivide(const T &  a, const Array<T>& b)
			{
				Array<T> result(b);
				for (unsigned int i = 0; i < b.size(); ++i)
				{
					result[i]=b[i] / a;
				}
				return result;
			}
			/*
			C = A.^B raises each element of A to the corresponding power in B.
			TODO:
			Calculate the roots of -1 to the 1/3 power.
			For negative base A and noninteger B, if abs(B) is less than 1, the power function returns the complex roots of A.
			Use the nthroot function to obtain the real roots.
			*/
			template<class T>
			inline Array<T> power(const Array<T>& a, const T & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i]=std::pow(a[i], b);
				}
				return result;
			}
			/*
			C = A*B is the matrix product of A and B.
			*/
			template<class T>
			inline Array<T> mtimes(const Array<T>& a, const Array<T>& b)
			{
				if (a.dim_size()>2||b.dim_size()>2)
				{
					throw std::runtime_error("Arguments must be 2 - D, or at least one argument must be scalar.Use TIMES(.*) for elementwise multiplication.");
				}
				if (a.get_dim_data(1)!=b.get_dim_data(0))
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
				Array<T> result(a.get_dim_data(0), b.get_dim_data(1));
				//result.resize(a.rows()*b.cols());
				for (int i = 0; i < a.get_dim_data(0); ++i)
				{
					for (int j = 0; j < b.get_dim_data(1); ++j)
					{
						int des = i*a.get_dim_data(0) + j;
						for (int k = 0; k < a.get_dim_data(1); ++k)
						{
							result[des] += a[i*a.get_dim_data(1) + k] * b[k*b.get_dim_data(1) + j];
						}
					}
				}
				return result;
			}
			/*
			Y = fix(X) rounds each element of X to the nearest integer toward zero. 
			For positive X, the behavior of fix is the same as floor. 
			For negative X, the behavior of fix is the same as ceil.
			*/
			template<class T>
			inline T fix(T x)
			{
				if (x > 0.0)
					return std::floor(x);
				else
					return std::ceil(x);
			}
			template<class T>
			inline Array<T> fix(const Array<T> & t)
			{
				Array<T> result(t);
				for (auto & each:result)
					each = fix(each);
				return result;
			}
			/*
			floor
			Round toward negative infinity
			*/
			template<class T>
			inline T floor(T x)
			{
				return std::floor(x);
			}
			template<class T>
			inline Array<T> floor(const Array<T> & t)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = std::floor(each);
				return result;
			}
			/*
			ceil
			Round toward positive infinity
			*/
			inline double ceil(double x)
			{
				return std::ceil(x);
			}
			/*
			
			*/
			inline double round(double x)
			{
				return std::round(x);
			}
			/*
			rat:
			R = rat(X) returns the rational fraction approximation of X to within the default tolerance, 1e-6*norm(X(:),1). The approximation is a character array containing the truncated continued fractional expansion.
			R = rat(X,tol) approximates X to within the tolerance, tol.
			[N,D] = rat(___) returns two arrays, N and D, such that N./D approximates X, using any of the above syntaxes.
			3 + 1/(7 + 1/(16 + 1/(-294)))
			*/

			inline Array<int> rat(double x, double tol)
			{
				int n, d;
				double float_part = x;
				int stack[32], top = 0;

				while (true)
				{
					stack[top] = (int)round(float_part);
					++top;
					assert((top < 32) && "rat stack full.");

					n = 1;
					d = 0;
					for (int i = top - 1; i >= 0; --i)
					{
						int tmp = n;
						n = n*stack[i] + d;
						d = tmp;
					}
					double tmp = x - (double)n / d;
					if (tmp<tol&& tmp>-tol)
						break;
					float_part = 1.0 / (float_part - stack[top - 1]);
				}
				if (n < 0 && d < 0)
					return{ -n,-d };
				else
					return{ n,d };
			}

			inline Array<int> rat(double x)
			{
				return rat(x, 1e-6);
			}
			/*
			S = rats(X) returns a character vector containing the rational approximations to the elements of X using the default length of 13.
			rats returns asterisks for elements that cannot be printed in the allotted space, but which are not negligible compared to the other elements in X.
			S = rats(X,strlen) returns a character vector of length strlen. The rational approximation uses a tolerance that is inversely proportional to the length.
			*/
			inline string rats(double x)
			{
				Array<int> result = rat(x);
				return std::to_string(result[0]) + "/" + std::to_string(result[1]);
			}




		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
