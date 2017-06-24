#pragma once
#ifndef CATOOL_TYPES_H
#define CATOOL_TYPES_H

#include<cstdint>
#include<string>
#include<vector>
#include<complex>
#include<initializer_list>
#include"MainToolbox\Fundamentals\Array.h"

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
	using Array = main_toolbox::fundamentals::Array<T>;
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
	inline string compose_index(std::vector<int>& loop)
	{
		string ans = "(";
		for (unsigned int i = 0; i < loop.size(); ++i)
		{
			if (i == 0)
			{
				ans += std::to_string(loop[i]);
			}
			else if (i == loop.size()-1)
			{
				ans += ",:";
			}
			else if (i == loop.size() - 2)
			{
				ans += ",:";
			}
			else
			{
				ans += "," + std::to_string(loop[i]);
			}
		}
		ans += ")";
		return ans;
	}

	template<class T>
	inline void var_dump_impl(const Array<T> & v, std::vector<int>& loop, int cur_loop)
	{
		if (cur_loop >v.dim_size()-3)
		{
			std::cout << compose_index(loop) << "\t=" << std::endl;

			int prefix_index = 0;
			for (unsigned int i = 0; i < loop.size()-2; ++i)
			{
				prefix_index += v.get_dim_acc(i)*loop[i];
			}

			for (int i = 0; i < v.get_dim_data(v.dim_size()-2); ++i)
			{
				for (int j = 0; j < v.get_dim_data(v.dim_size() - 1); ++j)
				{
					std::cout << v[prefix_index + i*v.get_dim_acc(v.dim_size() - 1) + j] << " ";
				}
				std::cout << std::endl;
			}
		}
		else
		{
			int &i = loop[cur_loop];
			for (i = 0; i < v.get_dim_data(cur_loop); ++i)
			{
				var_dump_impl(v, loop, cur_loop + 1);
			}
		}
	}

	template<class T>
	inline void var_dump(const Array<T> & v)
	{
		//dimension empty
		for (int i = 0; i < v.dim_size(); ++i)
		{
			if (v.get_dim_data(i) <= 0)
			{
				//print empty dimension matrix
				std::cout << typeid(v).name() << "\t=" << std::endl << "[](";
				for (int j = 0; j < v.dim_size(); ++j)
				{
					if (j == 0)
					{
						std::cout << v.get_dim_data(j);
					}
					else
					{
						std::cout << "x" << v.get_dim_data(j);
					}
				}
				std::cout << ")" << std::endl;
				return;
			}
		}
		//all dimension are not empty
		if (v.dim_size() - 1 < 2)
		{
			std::cout << typeid(v).name() << "\t=" << std::endl;
			if (v.dim_size() == 1)
			{
				for (int j = 0; j < v.get_dim_data(0); ++j)
				{
					std::cout << v[j] << " ";
				}
				std::cout << std::endl;
			}
			else
			{
				for (int i = 0; i < v.get_dim_data(v.dim_size() - 2); ++i)
				{
					for (int j = 0; j < v.get_dim_data(v.dim_size() - 1); ++j)
					{
						std::cout << v[i*v.get_dim_acc(1) + j] << " ";
					}
					std::cout << std::endl;
				}
			}
		}
		else
		{
			std::vector<int> loop;
			loop.resize(v.dim_size());
			int &i = loop[0];
			for (i = 0; i < v.get_dim_data(0); ++i)
			{
				var_dump_impl(v, loop, 1);
			}
		}
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
