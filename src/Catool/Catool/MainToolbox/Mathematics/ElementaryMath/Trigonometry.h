#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H

#include<cmath>
#include"../../../Types.h"
#include"../../Fundamentals/Array.h"
namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			/*
			sin
			Sine of argument in radians
			*/
			template<class T>
			inline T sin(T n)
			{
				return std::sin(n);
			}
			template<class T>
			inline Array<T> sin(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::sin(each);
				return result;
			}
			/*
			cos
			Cosine of argument in radians
			*/
			template<class T>
			inline T cos(T n)
			{
				return std::cos(n);
			}
			template<class T>
			inline Array<T> cos(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::cos(each);
				return result;
			}


		}
	}
}
#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H