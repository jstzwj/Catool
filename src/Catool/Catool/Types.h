#pragma once
#ifndef CATOOL_TYPES_H
#define CATOOL_TYPES_H

#include<cstdint>
#include<vector>
#include<string>
#include<complex>
#include<iostream>
#include<initializer_list>

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

	template<class T>
	class vector
	{
	protected:
		int row;
		int column;
		std::vector<T> data;
	public:
		vector() noexcept
			:row(1),column(0){}
		vector(int row_) noexcept 
			:row(row_), column(1) {}
		vector(int row_, int col_) noexcept 
			:row(row_), column(col_) {}
		vector(std::initializer_list<T> list)
			:data(list){}

		void push_back(const T& val)
		{
			data.push_back(val);
		}
		T& operator[](int n)
		{
			return data[n];
		}
		const T& operator[](int n)const
		{
			return data[n];
		}
		typename std::vector<T>::iterator begin() { return data.begin(); }
		typename std::vector<T>::iterator end() { return data.end(); }
		typename std::vector<T>::const_iterator begin() const{ return data.begin(); }
		typename std::vector<T>::const_iterator end() const{ return data.end(); }
		typename std::vector<T>::const_iterator cbegin() const{ return data.cbegin(); }
		typename std::vector<T>::const_iterator cend() const { return data.cend(); }
		int size() const{ return data.size(); }
	};

	using complex = std::complex<double>;

	/*
	var_dump :print the info of variables.
	*/
	template<class T>
	void var_dump(const T & v)
	{
		std::cout << typeid(v).name() << std::endl;
		std::cout << v << std::endl;
	}

	template<class T>
	void var_dump(const vector<T> & v)
	{
		std::cout << typeid(v).name() << std::endl;
		std::cout << "[";
		for (const auto & each : v)
		{
			std::cout << each << " ";
		}
		std::cout << "]" << std::endl;
	}

	void var_dump(const complex & com)
	{
		std::cout << typeid(com).name() << std::endl;
		std::cout << "[";
		std::cout << com.real() << ",";
		std::cout << com.imag();
		std::cout << "]" << std::endl;
	}
	
}

#endif // !CATOOL_TYPES_H
