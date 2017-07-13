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
			inline T exp(const T & n)
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
			/*
			log	Natural logarithm
			*/
			template<class T>
			T log(const T & n)
			{
				return std::log(n);
			}
			template<class T>
			Array<T> log(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::log(each);
				return result;
			}

			/*
			log10	Common logarithm (base 10)
			*/
			template<class T>
			T log10(const T & n)
			{
				return std::log10(n);
			}
			template<class T>
			Array<T> log10(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::log10(each);
				return result;
			}
			/*
			log2	Base 2 logarithm and dissect floating-point numbers into exponent and mantissa
			*/
			template<class T>
			T log2(const T & n)
			{
				return std::log2(n);
			}
			template<class T>
			Array<T> log2(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::log2(each);
				return result;
			}
			/*
			nextpow2
			Exponent of next higher power of 2
			*/
			template<class T>
			T nextpow2(T n)
			{
				double num = std::log2(n);
				return static_cast<int>(num + 1);
			}

			/*
			sqrt	Square root
			*/
			template<class T>
			T sqrt(const T & n)
			{
				return std::sqrt(n);
			}
			template<class T>
			Array<T> sqrt(const Array<T>& n)
			{
				Array<T> result(n);
				for (auto& each : result)
					each = std::sqrt(each);
				return result;
			}
		}
	}
}
#endif	//CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_EXPONENTSLOGARITHMS_H