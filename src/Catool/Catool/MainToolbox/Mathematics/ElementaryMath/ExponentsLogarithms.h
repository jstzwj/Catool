#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_EXPONENTSLOGARITHMS_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_EXPONENTSLOGARITHMS_H

#include<cmath>
namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			/*
			exp
			Exponential
			*/
			template<class T>
			inline T exp(T n)
			{
				return std::exp(n);
			}
			template<class T>
			inline Array<T> exp(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::exp(each);
				return result;
			}
		}
	}
}
#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_EXPONENTSLOGARITHMS_H