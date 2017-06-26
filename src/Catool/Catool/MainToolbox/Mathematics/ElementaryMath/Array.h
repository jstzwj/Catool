#pragma once
#ifndef CATOOL_FUNDAMENTALS_ARRAY
#define CATOOL_FUNDAMENTALS_ARRAY

#include<vector>
#include<algorithm>
#include<cstdlib>
#include<ctime>

namespace catool
{
	namespace main_toolbox
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
			Array(int row_) noexcept
			{
				if (row_ < 0)row_ = 0;
				dim.push_back(row_);
				dim.push_back(1);
				data.resize(row_);
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
				dim.push_back(1);
				dim.push_back(list.size());
			}

			template<class U>
			Array(const Array<U>& other)
				:dim(other.get_dim()),data(other.begin(),other.end()){}

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
			/*void resize(int size) { data.resize(size); }*/
			std::vector<int> & get_dim() { return dim; }
			std::vector<int> get_dim() const { return dim; }
			std::vector<T> & get_data() { return data; }
			std::vector<T> get_data() const { return data; }

			int dim_size()const { return dim.size(); }
			int get_dim_data(int n) const
			{
				if (n >= static_cast<int>(dim.size()))
					return 1;
				else
					return dim[n];
			}
			int get_dim_acc(int n)const
			{
				int acc = 1;
				for (int i = 0; i < n; ++i)
				{
					acc *= dim[i];
				}
				return acc;
			}
			template<typename T1, typename... T2>
			void resize(T1 p, T2... arg)
			{
				dim.clear();
				dim.push_back(p);
				resize_impl(arg...);
			}
			template<typename T1, typename... T2>
			void resize_impl(T1 p, T2... arg)
			{
				dim.push_back(p);
				resize_impl(arg...);
			}
			void resize_impl()
			{
				resize_from_dim();
			}

			void resize(const std::vector<int> & sz)
			{
				dim = sz;
				resize_from_dim();
			}

			void resize(const Array<int> & sz)
			{
				if (sz.dim_size() > 2)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				dim = sz.get_data();
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
			bool isRow()const
			{
				for (unsigned int i = 0; i < dim.size();++i)
					if (i!=1&&dim[i] != 1)return false;
				return true;
			}
			bool isCol()const
			{
				for (unsigned int i = 0; i < dim.size(); ++i)
					if (i != 0 && dim[i] != 1)return false;
				return true;
			}
			bool isEmpty()const
			{
				if (dim.size() == 0)return true;
				for (unsigned int i = 0; i < dim.size(); ++i)
					if (dim[i]==0)return true;
				return true;
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
			result.resize(p, arg...);
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
			result.resize(p, arg...);
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
			result.resize(p, arg...);
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
			result.resize(p, arg...);
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
			result.resize(m, n);
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
			if (!(sz.size() <= 2 && sz.size()>0 && sz.dim_size() <= 2))
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
					result.resize(0);
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
						result.resize(i);
					}
					else
					{
						int i;
						for (i = 0; i + absk < m&& i < n; ++i)
						{
							result[i] = v[(i + absk)*n + i];
						}
						result.resize(i);
					}
				}
				return result;
			}
		}
		/*
		blkdiag(a, b, c, d, ...)
		*/
		template<class T>
		inline int dimSum(int n, const Array<T>& v)
		{
			return v.get_dim_data(n);
		}

		template<class T, class ...Targs>
		inline int dimSum(int n, const Array<T>& v, Targs ...args)
		{
			return v.get_dim_data(n) + dimSum(n, args...);
		}

		template<class T>
		inline void blkdiag_impl(Array<T>& result, int m, int n, const Array<T>& v)
		{
			if (v.dim_size() > 2)
			{
				throw std::runtime_error("Matrix must be 2-dimensional");
			}
			for (int i = 0; i < v.get_dim_data(0); ++i)
			{
				for (int j = 0; j < v.get_dim_data(1); ++j)
				{
					result[(i + m)*result.get_dim_data(1) + j + n] = v[i*v.get_dim_data(1) + j];
				}
			}
		}

		template<class T, class ...Targs>
		inline void blkdiag_impl(Array<T>& result, int m, int n, const Array<T>& v, Targs ...args)
		{
			if (v.dim_size() > 2)
			{
				throw std::runtime_error("Matrix must be 2-dimensional");
			}
			for (int i = 0; i < v.get_dim_data(0); ++i)
			{
				for (int j = 0; j < v.get_dim_data(1); ++j)
				{
					result[(i + m)*result.get_dim_data(1) + j + n] = v[i*v.get_dim_data(1) + j];
				}
			}
			blkdiag_impl(result, m + v.get_dim_data(0), n + v.get_dim_data(1), args...);
		}
		template<class T, class ...Targs>
		inline Array<T> blkdiag(const Array<T>& v, Targs ...args)
		{
			if (v.dim_size() > 2)
			{
				throw std::runtime_error("Matrix must be 2-dimensional");
			}
			int m = dimSum(0, v, args...);
			int n = dimSum(1, v, args...);

			Array<T> result(m, n);
			blkdiag_impl(result, 0, 0, v, args...);
			return result;
		}
		/*
		cat
		Concatenate arrays along specified dimension
		*/





		/*
		length
		Length of largest array dimension
		*/
		template<class T>
		int length(const T& n)
		{
			return 1;
		}
		template<class T>
		int length(const Array<T>& n)
		{
			return std::max_element(n.get_dim().begin(),n.get_dim().end());
		}
		/*
		size
		Array size
		*/
		template<class T>
		Array<int> size(const T&n)
		{
			return{ 1 };
		}
		template<class T>
		Array<int> size(const Array<T> &n)
		{
			return n.get_dim();
		}
		template<class T>
		int size(const Array<T> &n,int dim)
		{
			if (dim <= 0)
				throw std::runtime_error("error: size: requested dimension DIM out of range");
			return n.get_dim_data(dim);
		}
		/*
		ndims
		Number of array dimensions
		*/
		template<class T>
		int ndims(const T&n)
		{
			return 1;
		}
		template<class T>
		int ndims(const Array<T> &n)
		{
			return n.dim_size();
		}
		/*
		numel
		Number of array elements
		*/
		template<class T>
		int numel(const T&n)
		{
			return 1;
		}
		template<class T>
		int numel(const Array<T> &n)
		{
			return n.size();
		}
		/*
		isscalar	
		Determine whether input is scalar
		*/
		template<class T>
		bool isscalar(const T&n)
		{
			return std::is_pod<T>::value;
		}
		/*
		isvector	
		Determine whether input is vector
		*/
		template<class T>
		bool isvector(const T& n)
		{
			return false;
		}
		template<class T>
		bool isvector(const Array<T>& n)
		{
			return n.isVector();
		}

		/*
		ismatrix	
		Determine whether input is matrix
		*/
		template<class T>
		bool ismatrix(const T& n)
		{
			return false;
		}
		template<class T>
		bool ismatrix(const Array<T>& n)
		{
			return n.isMatrix();
		}
		/*
		isrow	
		Determine whether input is row vector
		*/
		template<class T>
		bool isrow(const T& n)
		{
			return true;
		}
		template<class T>
		bool isrow(const Array<T>& n)
		{
			return n.isRow();
		}
		/*
		iscolumn	Determine whether input is column vector
		*/
		template<class T>
		bool iscolumn(const T& n)
		{
			return true;
		}
		template<class T>
		bool iscolumn(const Array<T>& n)
		{
			return n.isCol();
		}

		/*
		isempty	Determine whether array is empty
		*/
		template<class T>
		bool isempty(const T& n)
		{
			return false;
		}
		template<class T>
		bool isempty(const Array<T>& n)
		{
			return n.isEmpty();
		}

	}
}

#endif // !CATOOL_FUNDAMENTALS_ARRAY
