#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H

#include<cmath>
#include"../../Types.h"
#include"Array.h"
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
			inline T sin(const T & n)
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
			inline T sind(const T & n)
			{
				return std::sin(n*CATOOL_PI / 180);
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
			inline T asin(const T & n)
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
			inline T asind(const T & n)
			{
				return std::asin(n) * 180 / CATOOL_PI;
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
			inline T sinh(const T & n)
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
			inline T asinh(const T & n)
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
			inline T cos(const T & n)
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
			inline T cosd(const T & n)
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
			inline T acos(const T & n)
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
			inline T acosd(const T & n)
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
			inline T cosh(const T & n)
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
			inline T acosh(const T & n)
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
			/*
			tan	Tangent of argument in radians
			*/
			template<class T>
			inline T tan(const T & n)
			{
				return std::tan(n);
			}
			template<class T>
			inline Array<T> tan(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::tan(each);
				return result;
			}
			/*
			tand	Tangent of argument in degrees
			*/
			template<class T>
			inline T tand(const T & n)
			{
				return std::tan(n*CATOOL_PI / 180);
			}
			template<class T>
			inline Array<T> tand(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::tan(each*CATOOL_PI / 180);
				return result;
			}
			/*
			atan	Inverse tangent in radians
			*/
			template<class T>
			inline T atan(const T & n)
			{
				return std::atan(n);
			}
			template<class T>
			inline Array<T> atan(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::atan(each);
				return result;
			}
			/*
			atand	Inverse tangent in degrees
			*/
			template<class T>
			inline T atand(const T & n)
			{
				return std::atan(n) * 180 / CATOOL_PI;
			}
			template<class T>
			inline Array<T> atand(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::atan(each) * 180 / CATOOL_PI;
				return result;
			}
			/*
			atan2	Four - quadrant inverse tangent
			*/
			template<class T>
			inline T atan2(const T& y, const T& x)
			{
				return std::atan2(y, x);
			}
			/*
			atan2d	Four - quadrant inverse tangent in degrees
			*/
			template<class T>
			inline T atan2d(const T& y, const T& x)
			{
				return std::atan2(y, x) * 180 / CATOOL_PI;
			}

			/*
			tanh	Hyperbolic tangent
			*/
			template<class T>
			inline T tanh(const T & n)
			{
				return std::tanh(n);
			}
			template<class T>
			inline Array<T> tanh(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::tanh(each);
				return result;
			}
			/*
			atanh	Inverse hyperbolic tangent
			*/
			template<class T>
			inline T atanh(const T & n)
			{
				return std::atanh(n);
			}
			template<class T>
			inline Array<T> atanh(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::atanh(each);
				return result;
			}
		}
	}
}
#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_TRIGONOMETRY_H