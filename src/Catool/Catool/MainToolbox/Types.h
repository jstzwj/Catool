#pragma once
#ifndef CATOOL_TYPES_H
#define CATOOL_TYPES_H

#include<cstdint>
#include<string>
#include<vector>
#include<complex>
#include<initializer_list>
#include<typeinfo>
#include"Array.h"
#include"Complex.h"

namespace catool
{
	namespace main_toolbox
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

		/*
		var_dump :print the info of variables.
		*/
		template<class T>
		void var_dump(const T & v)
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
					ans += ":";
				}
				else if (i == 1)
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
		void var_dump_impl(const Array<T> & v, std::vector<int>& loop, int cur_loop)
		{
			int &i = loop[cur_loop];
			for (i = 0; i < v.get_dim_data(cur_loop); ++i)
			{
				if (cur_loop < 2)
				{
					std::cout << compose_index(loop) << "\t=" << std::endl;

					int prefix_index = 0;
					for (unsigned int i = 2; i < loop.size(); ++i)
					{
						prefix_index += v.get_dim_acc(i)*loop[i];
					}

					for (int i = 0; i < v.get_dim_data(0); ++i)
					{
						for (int j = 0; j < v.get_dim_data(1); ++j)
						{
							std::cout << v[prefix_index + j*v.get_dim_data(0) + i] << " ";
						}
						std::cout << std::endl;
					}
					break;
				}
				else
				{
					var_dump_impl(v, loop, cur_loop - 1);
				}
			}
		}

		template<class T>
		void var_dump(const Array<T> & v)
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
					//change [](0) to [](0x1)
					if (v.dim_size() == 1)
					{
						std::cout << "x1";
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
						std::cout << v[j];
						std::cout << std::endl;
					}
				}
				else
				{
					/*int counter = 0;
					for (int i = 0; i < v.get_dim_data(1); ++i)
					{
						for (int j = 0; j < v.get_dim_data(0); ++j)
						{
							std::cout << v[i*v.get_dim_acc(1) + j] << " ";
							++counter;
							if (counter%v.get_dim_data(1) == 0)
							{
								std::cout << std::endl;
							}
						}
					}*/
					for (int i = 0; i < v.get_dim_data(0); ++i)
					{
						for (int j = 0; j < v.get_dim_data(1); ++j)
						{
							std::cout << v[j*v.get_dim_data(0) + i] << " ";
						}
						std::cout << std::endl;
					}
				}
			}
			else
			{
				std::vector<int> loop;
				loop.resize(v.dim_size());
				int &i = loop[v.dim_size() - 1];
				for (i = 0; i < v.get_dim_data(v.dim_size() - 1); ++i)
				{
					var_dump_impl(v, loop, v.dim_size() - 2);
				}
			}
		}

		void var_dump(const Complex & com)
		{
			std::cout << typeid(com).name() << "=" << std::endl;
			std::cout << com.real() << "+";
			std::cout << com.imag();
			std::cout << "i" << std::endl;
		}



		//disp
		template<class T = void>
		using void_t = void;

		template<class T, class = void_t<>>
		struct HasMemberTostring
		{
			using type = std::false_type;
		};

		template<class T>
		struct HasMemberTostring<T, void_t<decltype(&T::to_string)>>
		{
			using type = std::true_type;
		};

		template<class T>
		void disp_impl(const T & obj, std::true_type /*to_string_tag*/)
		{
			std::cout << obj.to_string() << std::endl;
		}
		template<class T>
		void disp_impl(const T & obj, std::false_type /*to_string_tag*/)
		{
			std::cout << obj << std::endl;
		}

		template<class T>
		void disp(const T & obj)
		{
			disp_impl(obj, typename HasMemberTostring<T>::type());
		}
		template<>
		void disp<Complex>(const Complex & obj)
		{
			std::cout << obj.real() << "+";
			std::cout << obj.imag() << "i";
		}


		//type_info
		template<class T>
		void print_type_info(const T & obj)
		{
			std::cout << typeid(obj).name() << std::endl;
		}
		template<class T>
		void print_type_info(const Array<T> & obj)
		{
			std::cout << typeid(obj).name() << obj.composeIndexToString(obj.get_dim(),false) << std::endl;
		}

	}
}

#endif // !CATOOL_TYPES_H
