#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_CONSTANTS_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_CONSTANTS_H

#include<cmath>
#include"Array.h"

#define CATOOL_PI 3.1415926535897932384626433832795
#define CATOOL_NATURAL_CONSTANT 2.71828182845904523536
#define CATOOL_GOLD_SECTION 1.61803398874989484820458683436563811772030917980576286
#define CATOOL_PYTHAGORAS_CONSTANT 1.41421356237309504880168872420969807
#define CATOOL_EULER_CONSTANT 0.57721566490153286060651209008240243
#define CATOOL_NAN NAN
#define CATOOL_INF INFINITY

namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			/*
			isfinite	Array elements that are finite
			*/
			template<class T>
			bool isfinite(T n)
			{
				return std::isfinite(n);
			}
			template<class T>
			Array<bool> isfinite(const Array<T> & n)
			{
				Array<bool> result;
				result.resize(n.get_dim());
				for (int i = 0; i < result.size(); ++i)
				{
					result[i] = std::isfinite(n[i]);
				}
				return result;
			}
			/*
			isinf	Array elements that are infinite
			*/
			template<class T>
			bool isinf(T n)
			{
				return std::isinf(n);
			}
			template<class T>
			Array<bool> isinf(const Array<T> & n)
			{
				Array<bool> result;
				result.resize(n.get_dim());
				for (int i = 0; i < result.size(); ++i)
				{
					result[i] = std::isinf(n[i]);
				}
				return result;
			}
			/*
			isnan
			*/
			template<class T>
			bool isnan(T n)
			{
				return std::isnan(n);
			}
			template<class T>
			Array<bool> isnan(const Array<T> & n)
			{
				Array<bool> result;
				result.resize(n.get_dim());
				for (int i = 0; i < result.size(); ++i)
				{
					result[i] = std::isnan(n[i]);
				}
				return result;
			}
		}
	}
}

#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_CONSTANTS_H