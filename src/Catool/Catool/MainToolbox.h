#pragma once
#ifndef CATOOL_MAINTOOLBOX_H
#define CATOOL_MAINTOOLBOX_H

#include"Types.h"
#include<cmath>
#include<cassert>

namespace catool
{
	namespace main_toolbox
	{
		inline double qPow(double i, int n)
		{
			double result = i;
			int m = 1;
			if (n >= 0)
			{
				for (; (m << 1) < n; m <<= 1)		result *= result;
				for (; m != n; ++m)		result *= i;
			}
			else if (n == 0)
			{
				result = 1;
			}
			else
			{
				result = 1.0 / qPow(i, -n);
			}
			return result;
		}

		//trigonometric functions
		/*
		sin
		*/

		const double ONE_SIX = 0.166666666666666666666666666666666666;
		const double ONE_120 = 0.00833333333333333333333333333333;
		const double ONE_5040 = 1.984126984126984126984126984127e-4;
		const double ONE_362880 = 2.7557319223985890652557319223986e-6;
		const double ONE_39916800 = 2.5052108385441718775052108385442e-8;
		const double PI = 3.1415926535897932384626433832795;
		const double TWO_PI = 6.283185307179586476925286766559;
		const double HALF_PI = 1.5707963267948966192313216916398;
		const double ONE_TWO_PI = 0.15915494309189533576888376337251;

		inline double sin(double n)
		{
			if (n > 0)
			{
				n -= (int)(n * ONE_TWO_PI + 0.5)*TWO_PI;
				if (n > HALF_PI) n = PI - n;
			}
			else
			{
				n -= (int)(n * ONE_TWO_PI - 0.5)*TWO_PI;
				if (n < -HALF_PI) n = -PI - n;
			}
			double n3 = n*n*n;
			return n - ONE_SIX*n3 + ONE_120*n*n*n3 - ONE_5040*n3*n3*n + ONE_362880*n3*n3*n3 - ONE_39916800*n*n*n3*n3*n3;
		}
		/*
		cos
		*/
		inline double cos(double n)
		{
		}

		//integer
		inline double fix(double x)
		{
			if (x > 0.0)
				return std::floor(x);
			else
				return std::ceil(x);
		}
		inline double floor(double x)
		{
			return std::floor(x);
		}
		inline double ceil(double x)
		{
			return std::ceil(x);
		}
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

		inline vector<int> rat(double x, double tol)
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

		inline vector<int> rat(double x)
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
			vector<int> result = rat(x);
			return std::to_string(result[0]) + "/" + std::to_string(result[1]);
		}
		/*
		Y = sign(x) returns an array Y the same size as x, where each element of Y is:
			1 if the corresponding element of x is greater than 0.
			0 if the corresponding element of x equals 0.
			-1 if the corresponding element of x is less than 0.
			x./abs(x) if x is complex.
		*/
		inline double sign(double x)
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
		/*
		r = rem(a,b) returns the remainder after division of a by b, where a is the dividend and b is the divisor. 
		This function is often called the remainder operation, which can be expressed as r = a - b.*fix(a./b). 
		The rem function follows the convention that rem(a,0) is NaN.
		*/
		double rem(double x, double y)
		{
			return std::fmod(x,y);
		}
		/*
		gcd(x, y)：整数x和y的最大公因数
		lcm(x, y)：整数x和y的最小公倍数
		exp(x) ：自然指数
		pow2(x)：2的指数
		log(x)：以e为底的对数，即自然对数或
		log2(x)：以2为底的对数
		log10(x)：以10为底的对数
	*/
	}
}

#endif // !CATOOL_MAINTOOLBOX_H
