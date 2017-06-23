#pragma once
#ifndef CATOOL_FUNDAMENTALS_ARRAY
#define CATOOL_FUNDAMENTALS_ARRAY

#include<vector>

namespace catool
{
	namespace main_toolbox
	{
		namespace fundamentals
		{
			/*
			array
			*/
			template<class T>
			class Array
			{
			protected:
				std::vector<int> dim;
				std::vector<T> data;
			public:
				Array() noexcept {}
				Array(int col_) noexcept
				{
					dim.push_back(col_);
					data.resize(col_);
				}
				template<class ...K>
				Array(K ...arg)
				{
					ArrayConstructor(arg...);
				}
				template<typename T1, typename... T2>
				void ArrayConstructor(T1 p, T2... arg)
				{
					dim.push_back(p);
					ArrayConstructor(arg...);
				}
				void ArrayConstructor()
				{
					resize_from_dim();
				}

				Array(std::initializer_list<T> list)
					:data(list)
				{
					dim.push_back(data.size());
				}

				//using iterator = std::vector<T>::iterator;
				//using const_iterator = std::vector<T>::const_iterator;

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
				typename std::vector<T>::const_iterator begin() const { return data.begin(); }
				typename std::vector<T>::const_iterator end() const { return data.end(); }
				typename std::vector<T>::const_iterator cbegin() const { return data.cbegin(); }
				typename std::vector<T>::const_iterator cend() const { return data.cend(); }
				int size() const { return data.size(); }
				void resize(int size) { data.resize(size); }
				std::vector<int> & get_dim() { return dim; }
				std::vector<int> get_dim() const { return dim; }
				std::vector<T> & get_data() { return data; }
				std::vector<T> get_data() const { return data; }

				int dim_size()const { return dim.size(); }
				int get_dim_data(int n) const
				{ 
					if (n >= static_cast<int>(dim.size()))
						return 0;
					else
						return dim[n]; 
				}
				int get_dim_acc(int n)const
				{
					int acc = 1;
					for (int i = 0; i < n;++i)
					{
						acc *= dim[i];
					}
					return acc;
				}

				template<typename T1, typename... T2>
				void reshape(T1 p, T2... arg)
				{
					dim.push_back(p);
					reshape(arg...);
				}
				void reshape()
				{
					resize_from_dim();
				}


				void reshape(const Array<int> & sz)
				{
					if (sz.dim.size()!=1)
					{
						throw std::runtime_error("the size array shall be one dimension array.");
					}
					dim = sz.data();
					resize_from_dim();
				}
				void resize_from_dim()
				{
					int acc = 1;
					for (const auto& each : dim)
						acc *= each;
					data.resize(acc);
				}

			};
			//functions
			inline int zeros()
			{
				return 0;
			}
			inline Array<int> zeros(int n)
			{
				return Array<int>(n, n);
			}

			template<typename T1, typename... T2>
			inline Array<int> zeros(T1 p, T2... arg)
			{
				Array<int> result;
				result.reshape(p,arg...);
				return result;
			}

			inline Array<int> zeros(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<int> result;
				result.get_dim() = sz.get_data();
				result.resize_from_dim();
				return result;
			}
		}
	}
}

#endif // !CATOOL_FUNDAMENTALS_ARRAY
