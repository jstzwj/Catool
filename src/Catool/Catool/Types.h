#pragma once
#ifndef CATOOL_TYPES_H
#define CATOOL_TYPES_H

#include<cstdint>
#include<string>
#include<complex>
#include<initializer_list>
#include"Fundamentals\Array.h"

namespace catool
{
	using int8 = std::int8_t;
	using int16 = std::int16_t;
	using int32 = std::int32_t;
	using int64 = std::int64_t;

	using uint8 = std::uint8_t;
	using uint16 = std::uint16_t;
	using uint32 = std::uint32_t;
	using uint64 = std::uint64_t;

	using single = std::float_t;

	using logical = bool;
	using string = std::string;

	using complex = std::complex<double>;

	/*
	var_dump :print the info of variables.
	*/
	template<class T>
	inline void var_dump(const T & v)
	{
		std::cout << typeid(v).name() << std::endl;
		std::cout << v << std::endl;
	}

	template<class T>
	inline void var_dump(const fundamentals::Array<T> & v)
	{
		std::cout << typeid(v).name() << std::endl;
		std::cout << "[";
		for (const auto & each : v)
		{
			std::cout << each << " ";
		}
		std::cout << "]" << std::endl;
	}

	inline void var_dump(const complex & com)
	{
		std::cout << typeid(com).name() << std::endl;
		std::cout << "[";
		std::cout << com.real() << ",";
		std::cout << com.imag();
		std::cout << "]" << std::endl;
	}
}

#endif // !CATOOL_TYPES_H
