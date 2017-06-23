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
			using namespace fundamentals;
			/*
			C = A + B adds arrays A and B and returns the result in C.
			C = plus(A,B) is an alternate way to execute A + B, but is rarely used.
			It enables operator overloading for classes.
			*/
			inline double plus(double a, double b)
			{
				return a + b;
			}
			template<class T>
			inline Array<T> plus(const Array<T>& a, const Array<T>& b)
			{
				if (a.size() != b.size())
					throw std::runtime_error("Matrix dimensions must agree.");
				Array<T> result(a.size());
				for (int i = 0; i < a.size(); ++i)
				{
					result[i]=a[i] + b[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> plus(const Array<T>& a, const T& b)
			{
				Array<T> result;
				for (const auto &each : a)
				{
					result.push_back(each + b);
				}
				return result;
			}

			template<class T>
			inline Array<T> plus(const T& a, const Array<T>& b)
			{
				Array<T> result;
				for (const auto &each : b)
				{
					result.push_back(a + each);
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
			template<class T>
			inline T minus(const T& a, const T& b)
			{
				return a - b;
			}
			template<class T>
			inline Array<T> minus(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result;
				if (a.size() != b.size())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(a[i] - b[i]);
				}
				return result;
			}
			template<class T>
			inline Array<T> minus(const Array<T>& a, const T & b)
			{
				Array<T> result;
				for (const auto &each : a)
				{
					result.push_back(each - b);
				}
				return result;
			}
			template<class T>
			inline Array<T> minus(const T & a, const Array<T>& b)
			{
				Array<T> result;
				for (const auto &each : b)
				{
					result.push_back(a - each);
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
				Array<T> result;
				for (const auto &each : a)
				{
					result.push_back(-a);
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
				Array<T> result;
				if (a.size() != b.size())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(a[i] * b[i]);
				}
				return result;
			}
			/*
			x = A./B divides each element of A by the corresponding element of B.
			*/
			template<class T>
			inline Array<T> rdivide(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result;
				if (a.size() != b.size())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(a[i] / b[i]);
				}
				return result;
			}
			template<class T>
			inline Array<T> rdivide(const Array<T>& a, const T & b)
			{
				Array<T> result;
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(a[i] / b);
				}
				return result;
			}
			template<class T>
			inline Array<T> rdivide(const T &  a, const Array<T>& b)
			{
				Array<T> result;
				for (unsigned int i = 0; i < b.size(); ++i)
				{
					result.push_back(a / b[i]);
				}
				return result;
			}

			/*
			x = B.\A divides each element of A by the corresponding element of B.
			*/
			template<class T>
			inline Array<T> ldivide(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result;
				if (a.size() != b.size())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(b[i] / a[i]);
				}
				return result;
			}
			template<class T>
			inline Array<T> ldivide(const Array<T>& a, const T & b)
			{
				Array<T> result;
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(b / a[i]);
				}
				return result;
			}
			template<class T>
			inline Array<T> ldivide(const T &  a, const Array<T>& b)
			{
				Array<T> result;
				for (unsigned int i = 0; i < b.size(); ++i)
				{
					result.push_back(b[i] / a);
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
				Array<T> result;
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result.push_back(std::pow(a[i], b));
				}
				return result;
			}

			/*
			C = A*B is the matrix product of A and B.
			*/
			template<class T>
			inline Array<T> mtimes(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result;
				if (a.col_size() != b.row_size())
					throw std::runtime_error("nonconformant arguments.");
				result.resize(a.rows()*b.cols());
				for (int i = 0; i < a.rows();++i)
				{
					for (int j = 0; j < b.cols();++j)
					{
						int des = i*a.cols() + j;
						for (int k = 0; k < a.cols();++k)
						{
							result[des] += a[i*a.cols() + k] * b[k*b.cols()+j];
						}
					}
				}
				return result;
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
