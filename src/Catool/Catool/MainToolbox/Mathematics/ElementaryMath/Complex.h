#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_COMPLEX_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_COMPLEX_H

#include<cmath>
#include<complex>
namespace catool
{
	namespace main_toolbox
	{
			using Complex = std::complex<double>;

			/*
			abs(z) returns the absolute value of z.
			If z is complex, abs(z) returns the complex modulus (magnitude) of z.

			abs(A) returns the absolute value of each element of A.
			If A is complex, abs(A) returns the complex modulus (magnitude) of each element of A.
			*/
			template<class T>
			T abs(const T& n)
			{
				return std::abs(n);
			}

			template<class T>
			Array<T> abs(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::abs(each);
				return result;
			}
			/*
			angle
			Phase angle
			*/
			template<class T>
			double angle(const T& com)
			{
				return std::arg(com);
			}
			template<class T>
			Array<T> angle(const Array<T>& com)
			{
				Array<T> result(com);
				for (auto& each : result)
					each = std::arg(each);
				return result;
			}
			/*
			conj
			Complex conjugate
			*/
			template<class T>
			double conj(const T& com)
			{
				return std::conj(com);
			}
			template<class T>
			Array<T> conj(const Array<T>& com)
			{
				Array<T> result(com);
				for (auto& each : result)
					each = std::conj(each);
				return result;
			}
			/*
			
			*/



			/*
			Y = sign(x) returns an array Y the same size as x, where each element of Y is:
			1 if the corresponding element of x is greater than 0.
			0 if the corresponding element of x equals 0.
			-1 if the corresponding element of x is less than 0.
			x./abs(x) if x is complex.
			*/
			template <class T>
			T sign(T x)
			{
				if (std::isnan(x) == true)
					return NAN;
				if (x > 0.0)
					return 1;
				else if (x < 0.0)
					return -1;
				else
					return 0;
			}
			Complex sign(const Complex& x)
			{
				return x / abs(x);
			}
			template<class T>
			Array<T> sign(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = sign(each);
				return result;
			}

	}
}
#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_COMPLEX_H