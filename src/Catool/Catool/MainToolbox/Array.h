#pragma once
#ifndef CATOOL_FUNDAMENTALS_ARRAY
#define CATOOL_FUNDAMENTALS_ARRAY

#include<vector>
#include<string>
#include<algorithm>
#include<tuple>
#include<functional>
#include <type_traits>
#include <iterator>
#include<mutex>
#include<cstdlib>
#include<ctime>

#include"Range.h"

namespace catool
{
	namespace main_toolbox
	{
		template<typename T>
		struct ArrayIntervalIterator; 
		template<typename T>
		struct ArrayConstIntervalIterator;
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
			//mutable std::mutex mtx;

			using SizeType = int;
			using IntervalIterator = ArrayIntervalIterator<T>;
			using ConstIntervalIterator = ArrayConstIntervalIterator<T>;
			Array() noexcept {}
			Array(int row_)
			{
				if (row_ < 0)row_ = 0;
				dim.push_back(row_);
				dim.push_back(1);
				data.resize(row_);
			}
			Array(const std::vector<int> &dims)
				:dim(dims)
			{
				this->resize_from_dim();
			}
			Array(const std::vector<Range> &dims)
			{
				for (const auto & each_range:dims)
					dim.push_back((each_range.end - each_range.begin)/each_range.interval);
				resize_from_dim();
			}
			template<class ...K>
			Array(K ...arg)
			{
				ArrayConstructor(arg...);
			}

			Array(std::initializer_list<T> list)
				:data(list)
			{
				dim.push_back(1);
				dim.push_back(list.size());
			}

			template<class U>
			explicit Array(const Array<U>& other)
				:dim(other.get_dim()), data(other.begin(), other.end()) {}

			Array(const Array<T>& other)
				: dim(other.get_dim()), data(other.begin(), other.end()) {}

			Array<T>& operator =(const Array<T>& other)
			{
				dim = other.dim;
				data = other.data;
				return *this;
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

			T& at(int n)
			{
				return data[n];
			}
			const T& at(int n)const
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
			const std::vector<int>& get_dim() const { return dim; }
			std::vector<T> & get_data() { return data; }
			const std::vector<T>& get_data() const { return data; }

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
					acc *= dim[i];
				return acc;
			}
			template<typename T1, typename... T2>
			void resize(T1 p, T2... arg)
			{
				dim.clear();
				dim.push_back(p);
				resize_impl(arg...);
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
				int count = 0;
				for (unsigned int i = 0; i < dim.size(); ++i)
				{
					if (dim[i] > 1)
					{
						count++;
						if (count >= 2)
							return true;
					}
				}
				return false;
			}
			bool isVector()const
			{
				int count = 0;
				for (unsigned int i = 0; i < dim.size(); ++i)
				{
					if (dim[i] > 1)
					{
						count++;
						if (count >= 2)
							return false;
					}
				}
				return true;
			}
			bool isRow()const
			{
				for (unsigned int i = 0; i < dim.size(); ++i)
					if (i != 1 && dim[i] != 1)return false;
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
					if (dim[i] == 0)return true;
				return true;
			}


			void swapRow(int a, int b)
			{
				if (dim_size() > 2)
					throw std::runtime_error("error: swapRow not defined for N-D objects");
				int d0= get_dim_data(0), d1= get_dim_data(1);
				for (int i = 0; i < d1; ++i)
				{
					std::swap(at(i*d0 + a), at(i*d0 + b));
				}
			}
			void swapCol(int a, int b)
			{
				if (dim_size() > 2)
					throw std::runtime_error("error: swapCol not defined for N-D objects");
				int d0 = get_dim_data(0), d1 = get_dim_data(1);
				for (int i = 0; i < d0; ++i)
				{
					std::swap(at(a*d0 + i), at(b*d0 + i));
				}
			}

			void addRow(double val, int from, int to)
			{
				if (dim_size() > 2)
					throw std::runtime_error("error: swapRow not defined for N-D objects");
				int d0 = get_dim_data(0), d1 = get_dim_data(1);
				for (int i = 0; i < d1; ++i)
				{
					data[i*d0 + to] += data[i*d0 + from]*val;
				}
			}
			void addCol(double val, int from, int to)
			{
				if (dim_size() > 2)
					throw std::runtime_error("error: swapRow not defined for N-D objects");
				int d0 = get_dim_data(0), d1 = get_dim_data(1);
				for (int i = 0; i < d0; ++i)
				{
					data[to*d0 + i] += data[from*d0 + i] * val;
				}
			}
			std::vector<Range> getFullLoop()const
			{
				std::vector<Range> rst;
				for (const auto& each:dim)
					rst.emplace_back(0,each,1);
				return rst;
			}
			int composeIndex(const std::vector<int> &dims)const
			{
				int index = 0;
				int acc = 1;
				for (unsigned int i = 0; i < dims.size(); ++i)
				{
					index += dims[i] * acc;
					acc *= get_dim_data(i);
				}
				return index;
			}
			//用于完全遍历
			void loop(const std::vector<Range>& loop_range, 
				std::function<void(const Array<T>& m,const std::vector<int>&dims)> f)const
			{
				std::vector<int> dims;
				dims.resize(dim.size());
				loop_impl(dims,dim.size()-1,loop_range,f);
			}
			//用于按某一维度遍历
			void dimloop(int loop_dim,
				std::function<void(const Array<T>& m, std::vector<int>&dims)> f)const
			{
				std::vector<int> dims;
				dims.resize(dim.size());
				dimloop_impl(dims, dim.size() - 1, loop_dim, f);
			}

			void dimloop(int loop_dim,
				std::function<void(Array<T>& m, std::vector<int>&dims)> f)
			{
				std::vector<int> dims;
				dims.resize(dim.size());
				dimloop_impl(dims, dim.size() - 1, loop_dim, f);
			}

			
			Array<T> subArray(const std::vector<Range>& loop_range)const
			{
				Array<T> rst(loop_range);
				loop(loop_range, [&rst,&loop_range](const Array<T>& m, const std::vector<int>&dims) 
				{
					int index = 0;
					int size = dims.size();
					for (unsigned int i = 0; i < size; ++i)
						index += (dims[i] - loop_range[i].begin) * rst.get_dim_acc(i);
					rst[index] = m[m.composeIndex(dims)];
				});
				return rst;
			}

			//tostring
			static std::string composeIndexToString(const std::vector<int>& loop,bool ignoreHead=true)
			{
				std::string ans = "(";
				for (unsigned int i = 0; i < loop.size(); ++i)
				{
					if (ignoreHead == false)
					{
						if (i == 0)
							ans += std::to_string(loop[i]);
						else
							ans += "," + std::to_string(loop[i]);
					}
					else
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
				}
				ans += ")";
				return ans;
			}

			std::string to_string()const
			{
				std::string rst;
				//dimension empty
				for (int i = 0; i < this->dim_size(); ++i)
				{
					if (this->get_dim_data(i) <= 0)
					{
						//print empty dimension matrix
						rst += "[](";
						for (int j = 0; j < this->dim_size(); ++j)
						{
							if (j == 0)
							{
								rst += std::to_string(this->get_dim_data(j));
							}
							else
							{
								rst += "x" + std::to_string(this->get_dim_data(j));
							}
						}
						//change [](0) to [](0x1)
						if (this->dim_size() == 1)
						{
							rst += "x1";
						}
						rst += ")\n";
						return rst;
					}
				}
				//all dimension are not empty
				if (this->dim_size() - 1 < 2)
				{
					if (this->dim_size() == 1)
					{
						for (int j = 0; j < this->get_dim_data(0); ++j)
						{
							rst += std::to_string(at(j)) + "\n";
						}
					}
					else
					{
						for (int i = 0; i < this->get_dim_data(0); ++i)
						{
							for (int j = 0; j < this->get_dim_data(1); ++j)
							{
								rst += std::to_string(at(j*this->get_dim_data(0) + i)) + " ";
							}
							rst += "\n";
						}
					}
				}
				else
				{
					std::vector<int> loop;
					loop.resize(this->dim_size());
					int &i = loop[this->dim_size() - 1];
					for (i = 0; i < this->get_dim_data(this->dim_size() - 1); ++i)
					{
						rst += to_string_impl(loop, this->dim_size() - 2);
					}
				}
				return rst;
			}
			//private method
		private:

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

			void loop_impl(std::vector<int>& dims, int cur_dim, const std::vector<Range>& loop_range
				, std::function<void(const Array<T>& m, const std::vector<int>&)> &f)const
			{
				if (cur_dim < 0)return;
				Range range = loop_range[cur_dim];
				dims[cur_dim] = range.begin;
				for (int &i = dims[cur_dim]; i<range.end; i += range.interval)
				{
					if (cur_dim == 0)
						f(*this, dims);
					loop_impl(dims,cur_dim-1, loop_range, f);
				}
			}
			void dimloop_impl(std::vector<int>& dims, int cur_dim, int loop_dim,
				std::function<void(const Array<T>& m, std::vector<int>&dims)> &f)const
			{
				if (cur_dim < 0)
				{
					f(*this, dims);
					return;
				}
				if (cur_dim == loop_dim)
					dimloop_impl(dims, cur_dim - 1, loop_dim, f);
				else
					for (int &i = dims[cur_dim]; i<dim[cur_dim]; ++i)
						dimloop_impl(dims, cur_dim - 1, loop_dim, f);
			}

			void dimloop_impl(std::vector<int>& dims, int cur_dim, int loop_dim,
				std::function<void(Array<T>& m, std::vector<int>&dims)> &f)
			{
				if (cur_dim < 0)
				{
					f(*this, dims);
					return;
				}
				if (cur_dim == loop_dim)
					dimloop_impl(dims, cur_dim - 1, loop_dim, f);
				else
					for (int &i = dims[cur_dim]; i<dim[cur_dim]; ++i)
						dimloop_impl(dims, cur_dim - 1, loop_dim, f);
			}

			std::string to_string_impl(std::vector<int>& loop, int cur_loop)const
			{
				std::string rst;
				int &i = loop[cur_loop];
				for (i = 0; i < this->get_dim_data(cur_loop); ++i)
				{
					if (cur_loop < 2)
					{
						rst += composeIndexToString(loop) + "\t=" + "\n";

						int prefix_index = 0;
						for (unsigned int i = 2; i < loop.size(); ++i)
						{
							prefix_index += this->get_dim_acc(i)*loop[i];
						}

						for (int i = 0; i < this->get_dim_data(0); ++i)
						{
							for (int j = 0; j < this->get_dim_data(1); ++j)
							{
								rst += std::to_string(at(prefix_index + j*this->get_dim_data(0) + i)) + " ";
							}
							rst += "\n";
						}
						break;
					}
					else
					{
						rst += to_string_impl(loop, cur_loop - 1);
					}
				}
				return rst;
			}
		};
		//Array的interval迭代器
		template<typename T>
		struct ArrayIntervalIterator :public std::iterator<std::random_access_iterator_tag, T> 
		{
			typedef ArrayIntervalIterator<T>      Self;
			typedef Array<T>					Container;
			typedef T&                          reference;
			typedef T*                          pointer;
			typedef typename Array<T>::SizeType			SizeType;
			Array<T> *arry;
			SizeType index;
			SizeType interval;
			
			explicit ArrayIntervalIterator(Container & arry, SizeType index, SizeType interval)noexcept
				:arry(&arry), index(index), interval(interval) {}
			ArrayIntervalIterator(const ArrayIntervalIterator &)=default;
			Self& operator=(const ArrayIntervalIterator &)=default;


			Self& operator+=(SizeType n)
			{
				index += n*interval;
				return *this;
			}
			Self operator+(SizeType n)const
			{
				Self tmp = *this;
				tmp.index += n*tmp.interval;
				return tmp;
			}
			Self& operator-=(SizeType n)
			{
				index -= n*interval;
				return *this;
			}
			Self operator-(SizeType n)const
			{
				Self tmp = *this;
				tmp.index -= n*tmp.interval;
				return tmp;
			}
			SizeType operator-(const Self & other)const
			{
				return (index - other.index) / interval;
			}
			reference operator[](SizeType n)const
			{
				return (*arry)[index+n*interval];
			}
			bool operator<(const Self & other)const
			{
				return index < other.index;
			}
			bool operator>(const Self & other)const
			{
				return index > other.index;
			}
			bool operator<=(const Self & other)const
			{
				return index <= other.index;
			}
			bool operator>=(const Self & other)const
			{
				return index >= other.index;
			}

			Self& operator++()noexcept {
				index += interval;
				return *this;
			}
			Self operator++(int) {
				Self tmp = *this;
				++(*this);
				return tmp;
			}
			Self& operator--()noexcept {
				index -= interval;
				return *this;
			}
			Self operator--(int) {
				Self tmp = *this;
				--(*this);
				return tmp;
			}
			reference operator*() const noexcept
			{
				return (*arry)[index];
			}
			pointer operator->() const noexcept
			{
				return &(*arry)[index];
			}
			bool operator==(const Self& v) const noexcept
			{
				return arry == v.arry&&index == v.index&&interval == v.interval;
			}
			bool operator!=(const Self& v) const noexcept
			{
				return arry != v.arry || index != v.index || interval != v.interval;
			}
		};


		template<typename T>
		struct ArrayConstIntervalIterator :public std::iterator<std::random_access_iterator_tag, T>
		{
			typedef ArrayConstIntervalIterator<T>      Self;
			typedef Array<T>					Container;
			typedef const T&                          reference;
			typedef const T*                          pointer;
			typedef typename Array<T>::SizeType			SizeType;
			const Array<T> *arry;
			SizeType index;
			SizeType interval;

			explicit ArrayConstIntervalIterator(const Container & arry, SizeType index, SizeType interval)noexcept
				:arry(&arry), index(index), interval(interval) {}
			ArrayConstIntervalIterator(const ArrayConstIntervalIterator &) = default;
			Self& operator=(const ArrayConstIntervalIterator &) = default;


			Self& operator+=(SizeType n)
			{
				index += n*interval;
				return *this;
			}
			Self operator+(SizeType n)const
			{
				Self tmp = *this;
				tmp.index += n*tmp.interval;
				return tmp;
			}
			Self& operator-=(SizeType n)
			{
				index -= n*interval;
				return *this;
			}
			Self operator-(SizeType n)const
			{
				Self tmp = *this;
				tmp.index -= n*tmp.interval;
				return tmp;
			}
			SizeType operator-(const Self & other)const
			{
				return (index - other.index) / interval;
			}
			reference operator[](SizeType n)const
			{
				return (*arry)[index + n*interval];
			}
			bool operator<(const Self & other)const
			{
				return index < other.index;
			}
			bool operator>(const Self & other)const
			{
				return index > other.index;
			}
			bool operator<=(const Self & other)const
			{
				return index <= other.index;
			}
			bool operator>=(const Self & other)const
			{
				return index >= other.index;
			}

			Self& operator++()noexcept {
				index += interval;
				return *this;
			}
			Self operator++(int) {
				Self tmp = *this;
				++(*this);
				return tmp;
			}
			Self& operator--()noexcept {
				index -= interval;
				return *this;
			}
			Self operator--(int) {
				Self tmp = *this;
				--(*this);
				return tmp;
			}
			reference operator*() const noexcept
			{
				return (*arry)[index];
			}
			pointer operator->() const noexcept
			{
				return &(*arry)[index];
			}
			bool operator==(const Self& v) const noexcept
			{
				return arry == v.arry&&index == v.index&&interval == v.interval;
			}
			bool operator!=(const Self& v) const noexcept
			{
				return arry != v.arry || index != v.index || interval != v.interval;
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
		template<class T>
		inline Array<T> zeros(int n)
		{
			return Array<T>(n, n);
		}

		template<class T = int, typename T1, typename... T2>
		inline Array<T> zeros(T1 p, T2... arg)
		{
			Array<T> result;
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
		template<class T>
		inline Array<T> ones(int n)
		{
			Array<T> result(n, n);
			result.fill(1);
			return result;
		}

		template<class T=int,typename T1, typename... T2>
		inline Array<T> ones(T1 p, T2... arg)
		{
			Array<T> result;
			result.resize(p, arg...);
			result.fill(1);
			return result;
		}
		template<class T=int>
		inline Array<T> ones(const Array<int> & sz)
		{
			if (sz.dim_size() != 1)
			{
				throw std::runtime_error("the size array shall be one dimension array.");
			}
			Array<T> result;
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
					result[i] = v[i*n + i];		//maybe a bug n=>m
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
		template<class T>
		void cat_impl(Array<T> &result, int dim, int cur_pos)
		{
			return;
		}
		template<class T, class ...Targs>
		void cat_impl(Array<T> &result,int dim,int cur_pos, const Array<T>& A, Targs ...args)
		{
			std::vector<Range> range = A.getFullLoop();
			A.loop(range, [&result,&dim,&cur_pos](const Array<T>& m, const std::vector<int>&dims) 
			{
				int index = 0;
				for (unsigned int i = 0; i < dims.size(); ++i)
				{
					if (i == dim)
						index += (dims[i]+cur_pos) * result.get_dim_acc(i);
					else
						index += dims[i] * result.get_dim_acc(i);
				}
				result[index] = m[m.composeIndex(dims)];
			});

			cat_impl(result, dim, cur_pos+A.get_dim_data(dim),args...);
		}
		
		template<class T, class ...Targs>
		Array<T> cat(int dim, const Array<T>& A, Targs ...args)
		{
			Array<T> result;
			int cat_dim_sum = dimSum(dim, A,args...);

			std::vector<int> dims = A.get_dim();
			dims[dim] = cat_dim_sum;
			result.resize(dims);

			cat_impl(result, dim, 0, A, args...);
			return result;
		}



		/*
		horzcat
		Concatenate arrays horizontally
		*/
		template<class T, class ...Targs>
		Array<T> horzcat(const Array<T>& A, Targs ...args)
		{
			return cat(1,A,args...);
		}
		/*
		vertcat
		Concatenate arrays vertically
		*/
		template<class T, class ...Targs>
		Array<T> vertcat(const Array<T>& A, Targs ...args)
		{
			return cat(0, A, args...);
		}

		/*
		y = linspace(x1,x2)
		y = linspace(x1,x2,n)
		*/

		Array<double> linspace(double x1, double x2, int n)
		{
			Array<double> result;
			result.resize(1, n);
			double interval = (x2 - x1) / (n - 1);
			double cur_val = x1;

			for (auto & each : result)
			{
				each = cur_val;
				cur_val = cur_val + interval;
			}
			return result;
		}

		/*
		logspace
		Generate logarithmically spaced vector
		*/
		Array<double> logspace(double x1, double x2, int n)
		{
			Array<double> result;
			result.resize(1, n);
			double interval = (x2 - x1) / (n - 1);
			double cur_val = x1;

			for (auto & each : result)
			{
				each = std::pow(10, cur_val);
				cur_val = cur_val + interval;
			}
			return result;
		}
		/*
		freqspace
		Frequency spacing for frequency response
		*/

		/*
		[X,Y] = meshgrid(x,y)
		[X,Y] = meshgrid(x)
		[X,Y,Z] = meshgrid(x,y,z)
		[X,Y,Z] = meshgrid(x)
		*/

		template<class T>
		std::tuple<Array<T>, Array<T>> meshgrid(const Array<T>& x, const Array<T>& y)
		{
			if (x.dim_size() > 2 || y.dim_size() > 2)
			{
				throw std::runtime_error("error: meshgrid: X and Y must be vectors");
			}
			Array<T> m, n;
			m.resize(y.size(), x.size());
			n.resize(y.size(), x.size());
			for (int i = 0; i < y.size(); ++i)
			{
				for (int j = 0; j < x.size(); ++j)
				{
					m[j*y.size() + i] = x[j];
				}
			}
			for (int i = 0; i < x.size(); ++i)
			{
				for (int j = 0; j < y.size(); ++j)
				{
					n[i*y.size() + j] = y[j];
				}
			}
			return std::make_tuple(m, n);
		}
		template<class T>
		std::tuple<Array<T>, Array<T>, Array<T>> meshgrid(const Array<T>& x, const Array<T>& y, const Array<T>& z)
		{
			if (x.dim_size() > 2 || y.dim_size()>2 || z.dim_size()>2)
			{
				throw std::runtime_error("error: meshgrid: X , Y and Z must be vectors");
			}
			Array<T> m, n, o;
			m.resize(y.size(), x.size(), z.size());
			n.resize(y.size(), x.size(), z.size());
			o.resize(y.size(), x.size(), z.size());

			for (int i = 0; i < z.size(); ++i)
			{
				for (int j = 0; j < y.size(); ++j)
				{
					for (int k = 0; k < x.size(); ++k)
					{
						m[i*m.get_dim_acc(2) + k*m.get_dim_acc(1) + j] = x[k];
					}
				}
			}
			for (int i = 0; i < x.size(); ++i)
			{
				for (int j = 0; j < z.size(); ++j)
				{
					for (int k = 0; k < y.size(); ++k)
					{
						n[j*m.get_dim_acc(2) + i*m.get_dim_acc(1) + k] = y[k];
					}
				}
			}
			for (int i = 0; i < y.size(); ++i)
			{
				for (int j = 0; j < x.size(); ++j)
				{
					for (int k = 0; k < z.size(); ++k)
					{
						o[k*m.get_dim_acc(2) + j*m.get_dim_acc(1) + i] = z[k];
					}
				}
			}
			return std::make_tuple(m, n, o);
		}
		template<class T>
		std::tuple<Array<T>, Array<T>> meshgrid(const Array<T>& x)
		{
			return meshgrid(x, x);
		}
		/*
		ndgrid
		Rectangular grid in N-D space
		*/
		//TODO

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
			return std::max_element(n.get_dim().begin(), n.get_dim().end());
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
		int size(const Array<T> &n, int dim)
		{
			if (dim < 0)
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
		/*
		sort
		Sort array elements
		*/
		template<class T>
		void sort_in_place(Array<T> & m,int dim=0)
		{
			m.dimloop(dim, [&m, &dim](Array<T>& m, std::vector<int>&dims)
			{
				int index = m.composeIndex(dims);
				int acc = m.get_dim_acc(dim);
				int len = m.get_dim_data(dim);

				typename Array<T>::IntervalIterator begin(m, index,acc);
				typename Array<T>::IntervalIterator end(m, index+len*acc,acc);
				std::sort(begin,end);
			});
		}
		template<class T>
		Array<T> sort(Array<T> & m, int dim = 0)
		{
			if (dim<0 || dim >= m.dim_size())
				throw std::runtime_error("error: sort DIM must be a valid dimension");
			Array<T> rst(m);
			sort_in_place(rst,dim);
			return rst;
		}


		/*
		rot90
		Rotate array 90 degrees
		*/
		//Not support N-D matrix now.
		template<class T>
		Array<T> rot90(const Array<T>& m)
		{
			if (m.dim_size() > 2)
				throw std::runtime_error("error: rot90 not defined for N-D objects");
			Array<T> result(m.get_dim_data(1), m.get_dim_data(0));
			for (int i = 0; i < m.get_dim_data(0); ++i)
			{
				for (int j = 0; j < m.get_dim_data(1); ++j)
				{
					int des_m = m.get_dim_data(1) - 1 - j, des_n = i;
					result[des_n*m.get_dim_data(0) + des_m] = m[j*m.get_dim_data(0) + i];
				}
			}
			return result;
		}
		template<class T>
		Array<T> rot90(const Array<T>& m, int k)
		{
			if (m.dim_size() > 2)
				throw std::runtime_error("error: rot90 not defined for N-D objects");
			Array<T> result(m.get_dim_data(1), m.get_dim_data(0));
			for (int i = 0; i < m.get_dim_data(0); ++i)
			{
				for (int j = 0; j < m.get_dim_data(1); ++j)
				{
					int mod = k % 4;
					int des_m, des_n;
					switch (mod)
					{
					case 0:
						des_m = i;
						des_n = j;
						result[des_n*m.get_dim_data(0) + des_m] = m[j*m.get_dim_data(0) + i];
						break;
					case 1:
						des_m = m.get_dim_data(1) - 1 - j;
						des_n = i;
						result[des_n*m.get_dim_data(0) + des_m] = m[j*m.get_dim_data(0) + i];
						break;
					case 2:
						des_m = m.get_dim_data(0) - 1 - i;
						des_n = m.get_dim_data(1) - 1 - j;
						result[des_n*m.get_dim_data(0) + des_m] = m[j*m.get_dim_data(0) + i];
						break;
					case 3:
						des_m = j;
						des_n = m.get_dim_data(0) - 1 - i;
						result[des_n*m.get_dim_data(0) + des_m] = m[j*m.get_dim_data(0) + i];
						break;
					}
				}
			}
			return result;
		}
		/*
		transpose, .'
		Transpose vector or matrix
		*/
		template<class T>
		Array<T> transpose(const Array<T>& m)
		{
			if (m.dim_size() > 2)
				throw std::runtime_error("error: transpose not defined for N-D objects");
			int d0=m.get_dim_data(0), d1=m.get_dim_data(1);
			Array<T> result(d1, d0);
			for (int i = 0; i < d0; ++i)
			{
				for (int j = 0; j < d1; ++j)
				{
					result[i*d1 + j] = m[j*d0 + i];
				}
			}
			return result;
		}
		/*
		ctranspose
		Complex conjugate transpose
		*/
		template<class T>
		Array<T> ctranspose(const Array<T>& m)
		{
			if (m.dim_size() > 2)
				throw std::runtime_error("error: transpose not defined for N-D objects");
			Array<T> result(m.get_dim_data(1), m.get_dim_data(0));
			for (int i = 0; i < m.get_dim_data(0); ++i)
			{
				for (int j = 0; j < m.get_dim_data(1); ++j)
				{
					result[i*m.get_dim_data(1) + j] = std::conj(m[j*m.get_dim_data(0) + i]);
				}
			}
			return result;
		}
		/*
		reshape
		Reshape array
		*/
		template<class T>
		Array<T> reshape(const Array<T>& m, const std::vector<int>&new_dims)
		{
			int new_size = 1;
			for (const auto &each : new_dims)
				new_size *= each;
			if (new_size != m.size())
				throw std::runtime_error("error: reshape: can't reshape.");
			Array<T> result(m);
			m.get_dim() = new_dims;
			return result;
		}
		/*
		shiftdim
		Shift dimensions
		*/
		template<class T>
		Array<T> shiftdim(const Array<T>& X, int n)
		{
			Array<T> rst(X);
			int dim_size = rst.dim_size();
			if (n>=0)
			{
				for (int i=0;i<dim_size;++i)
					rst.get_dim().at((i + n) % dim_size) = X.get_dim().at(i);
			}
			else
			{
				rst.get_dim().resize(dim_size-n);
				for (int i=dim_size-1;i>=0;--i)
					rst.get_dim().at(i-n) = X.get_dim().at(i);
				for (int i=0;i<-n;++i) 
					rst.get_dim().at(i) = 1;
			}
			return rst;
		}
		template<class T>
		std::tuple<Array<T>,int> shiftdim(const Array<T>& X)
		{
			int nsize = 0;
			for (const auto &each:X.get_dim())
			{
				if (each == 1)
					++nsize;
				else
					break;
			}
			Array<T> rst(X);
			int dim_size = X.dim_size();
			rst.get_dim().resize(dim_size-nsize);
			for (int i=0;i<dim_size-nsize;++i)
				rst.get_dim().at(i) = X.get_dim().at(i+nsize);
			return rst;
		}

		/*
		isequal
		Determine array equality
		*/
		template<class T>
		bool isequal(const Array<T>& m, const Array<T>& n)
		{
			return m == n;
		}
	}
}

#endif // !CATOOL_FUNDAMENTALS_ARRAY
