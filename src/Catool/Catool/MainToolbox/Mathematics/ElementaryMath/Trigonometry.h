#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H

#include<cmath>
#include"../../../Types.h"
#include"../../Fundamentals/Array.h"
#include"Constants.h"
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
			sind
			Sine of argument in degrees
			*/
			template<class T>
			inline T sind(T n)
			{
				return std::sin(n*CATOOL_PI/180);
			}
			template<class T>
			inline Array<T> sind(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::sin(each*CATOOL_PI / 180);
				return result;
			}
			/*
			asin
			Inverse sine in radians
			*/
			template<class T>
			inline T asin(T n)
			{
				return std::asin(n);
			}
			template<class T>
			inline Array<T> asin(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::asin(each);
				return result;
			}
			/*
			asind
			Inverse sine in degrees
			*/
			template<class T>
			inline T asind(T n)
			{
				return std::asin(n)*180/CATOOL_PI;
			}
			template<class T>
			inline Array<T> asind(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::asin(each) * 180 / CATOOL_PI;
				return result;
			}
			/*
			sinh
			Hyperbolic sine of argument in radians
			*/
			template<class T>
			inline T sinh(T n)
			{
				return std::sinh(n);
			}
			template<class T>
			inline Array<T> sinh(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::sinh(each);
				return result;
			}

			/*
			asinh
			Inverse hyperbolic sine
			*/
			template<class T>
			inline T asinh(T n)
			{
				return std::asinh(n);
			}
			template<class T>
			inline Array<T> asinh(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::asinh(each);
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
			/*
			cosd
			Sine of argument in degrees
			*/
			template<class T>
			inline T cosd(T n)
			{
				return std::cos(n*CATOOL_PI / 180);
			}
			template<class T>
			inline Array<T> cosd(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::cos(each*CATOOL_PI / 180);
				return result;
			}
			/*
			acos
			Inverse cose in radians
			*/
			template<class T>
			inline T acos(T n)
			{
				return std::acos(n);
			}
			template<class T>
			inline Array<T> acos(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::acos(each);
				return result;
			}
			/*
			acosd
			Inverse cose in degrees
			*/
			template<class T>
			inline T acosd(T n)
			{
				return std::acos(n) * 180 / CATOOL_PI;
			}
			template<class T>
			inline Array<T> acosd(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::acos(each) * 180 / CATOOL_PI;
				return result;
			}
			/*
			cosh
			Hyperbolic cose of argument in radians
			*/
			template<class T>
			inline T cosh(T n)
			{
				return std::cosh(n);
			}
			template<class T>
			inline Array<T> cosh(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::cosh(each);
				return result;
			}

			/*
			acosh
			Inverse hyperbolic cose
			*/
			template<class T>
			inline T acosh(T n)
			{
				return std::acosh(n);
			}
			template<class T>
			inline Array<T> acosh(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::acosh(each);
				return result;
			}

		}
	}
}
#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H