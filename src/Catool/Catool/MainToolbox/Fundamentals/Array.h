#pragma once
#ifndef CATOOL_FUNDAMENTALS_ARRAY
#define CATOOL_FUNDAMENTALS_ARRAY

#include<vector>
#include<cstdlib>
#include<ctime>

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
					if (col_ < 0)col_ = 0;
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
					if (p < 0)p = 0;
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
					for (unsigned int i = n + 1; i < dim.size(); ++i)
					{
						acc *= dim[i];
					}
					return acc;
				}
				template<typename T1, typename... T2>
				void reshape(T1 p, T2... arg)
				{
					dim.clear();
					dim.push_back(p);
					reshape_impl(arg...);
				}
				template<typename T1, typename... T2>
				void reshape_impl(T1 p, T2... arg)
				{
					dim.push_back(p);
					reshape_impl(arg...);
				}
				void reshape_impl()
				{
					resize_from_dim();
				}

				void reshape(const Array<int> & sz)
				{
					if (sz.dim.size() != 1)
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

				void fill(const T& val)
				{
					std::fill(data.begin(), data.end(), val);
				}
				bool isMatrix()const
				{
					return dim.size() != 1;
				}
				bool isVector()const
				{
					return dim.size() == 1;
				}
			};
			//functions
			/*
			zeros: Create array of all zeros
			*/
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
				result.reshape(p, arg...);
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
			/*
			ones
			Create array of all ones
			*/
			inline int ones()
			{
				return 1;
			}
			inline Array<int> ones(int n)
			{
				Array<int> result(n, n);
				result.fill(1);
				return result;
			}

			template<typename T1, typename... T2>
			inline Array<int> ones(T1 p, T2... arg)
			{
				Array<int> result;
				result.reshape(p, arg...);
				result.fill(1);
				return result;
			}

			inline Array<int> ones(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<int> result;
				result.get_dim() = sz.get_data();
				result.resize_from_dim();
				result.fill(1);
				return result;
			}
			/*
			rand
			Uniformly distributed random numbers
			*/
			inline void rand_fill(Array<double>& arry)
			{
				std::srand(static_cast<unsigned int>(std::time(0)));
				for (auto& each : arry)
				{
					each = (double)std::rand() / RAND_MAX;
				}
			}
			inline double rand()
			{
				return ((double)std::rand() / RAND_MAX);
			}
			inline Array<double> rand(int n)
			{
				Array<double> result(n, n);
				rand_fill(result);
				return result;
			}
			template<typename T1, typename... T2>
			inline Array<double> rand(T1 p, T2... arg)
			{
				Array<double> result;
				result.reshape(p, arg...);
				rand_fill(result);
				return result;
			}
			inline Array<double> rand(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<double> result;
				result.get_dim() = sz.get_data();
				result.resize_from_dim();
				rand_fill(result);
				return result;
			}
			/*
			Logical 1 (true)
			*/

			inline bool logical_true()
			{
				return true;
			}
			inline Array<bool> logical_true(int n)
			{
				Array<bool> result(n, n);
				result.fill(true);
				return result;
			}
			template<typename T1, typename... T2>
			inline Array<bool> logical_true(T1 p, T2... arg)
			{
				Array<bool> result;
				result.reshape(p, arg...);
				result.fill(true);
				return result;
			}
			inline Array<bool> logical_true(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<bool> result;
				result.get_dim() = sz.get_data();
				result.resize_from_dim();
				result.fill(true);
				return result;
			}
			/*
			false
			Logical 0 (false)
			*/
			inline bool logical_false()
			{
				return false;
			}
			inline Array<bool> logical_false(int n)
			{
				Array<bool> result(n, n);
				result.fill(false);
				return result;
			}
			template<typename T1, typename... T2>
			inline Array<bool> logical_false(T1 p, T2... arg)
			{
				Array<bool> result;
				result.reshape(p, arg...);
				result.fill(false);
				return result;
			}
			inline Array<bool> logical_false(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<bool> result;
				result.get_dim() = sz.get_data();
				result.resize_from_dim();
				result.fill(false);
				return result;
			}
			/*
			eye
			Identity matrix
			*/
			inline int eye()
			{
				return 1;
			}
			template<class T>
			inline T eye()
			{
				return std::declval<T>();
			}
			template<class T = int>
			inline Array<T> eye(int n)
			{
				Array<T> result(n, n);
				for (int i = 0; i < n; ++i)
				{
					result[i*n + i] = 1;
				}
				return result;
			}
			template<typename T = int>
			inline Array<T> eye(int m, int n)
			{
				Array<T> result;
				result.reshape(m, n);
				int min = m > n ? n : m;
				for (int i = 0; i < min; ++i)
				{
					result[i*n + i] = 1;
				}
				return result;
			}
			template<typename T = int>
			inline Array<T> eye(const Array<int> & sz)
			{
				if (!(sz.dim_size() == 1 && sz.size() <= 2 && sz.size()>0))
				{
					throw std::runtime_error("Invalid call to eye.");
				}
				if (sz.size() == 1)
				{
					return eye(sz[0]);
				}
				else
				{
					return eye(sz[0], sz[1]);
				}
			}
			/*
			diag
			Create diagonal matrix or get diagonal elements of matrix
			*/
			template<class T = int>
			inline Array<T> diag(const Array<T> & v)
			{
				if (v.isVector())
				{
					int sz = v.size();
					Array<T> result(sz, sz);
					for (int i = 0; i < sz; ++i)
					{
						result[i*sz + i] = v[i];
					}
					return result;
				}
				else
				{
					if (v.dim_size() != 2)
					{
						throw std::runtime_error("Matrix must be 2-dimensional");
					}

					int m = v.get_dim_data(0);
					int n = v.get_dim_data(1);
					int min = m > n ? n : m;
					Array<T> result(min);
					for (int i = 0; i < min; ++i)
					{
						result[i] = v[i*n + i];
					}
					return result;
				}
			}

			template<class T = int>
			inline Array<T> diag(const Array<T> & v, int k)
			{
				int absk = k > 0 ? k : -k;
				if (v.isVector())
				{
					int matrix_sz = v.size() + absk;
					int diagonal_sz = v.size();
					Array<T> result(matrix_sz, matrix_sz);
					// places the elements of vector v on the kth diagonal.
					//k=0 represents the main diagonal, k>0 is above the main diagonal, and k<0 is below the main diagonal.
					if (k > 0)
					{
						for (int i = 0; i < diagonal_sz; ++i)
						{
							result[i*matrix_sz + i + absk] = v[i];
						}
					}
					else
					{
						for (int i = 0; i < diagonal_sz; ++i)
						{
							result[(i + absk)*matrix_sz + i] = v[i];
						}
					}
					return result;
				}
				else
				{
					if (v.dim_size() != 2)
					{
						throw std::runtime_error("Matrix must be 2-dimensional");
					}

					int m = v.get_dim_data(0);
					int n = v.get_dim_data(1);
					int min = m > n ? n : m;
					int max = m < n ? n : m;
					Array<T> result(min);
					//k out of matrix range
					if (absk > max)
					{
						result.reshape(0);
					}
					else
					{
						if (k > 0)
						{
							int i;
							for (i = 0; i < m&& i + absk < n; ++i)
							{
								result[i] = v[i*n + i + absk];
							}
							result.reshape(i);
						}
						else
						{
							int i;
							for (i = 0; i + absk < m&& i < n; ++i)
							{
								result[i] = v[(i + absk)*n + i];
							}
							result.reshape(i);
						}
					}
					return result;
				}
			}
		}
	}
}

#endif // !CATOOL_FUNDAMENTALS_ARRAY
