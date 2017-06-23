#pragma once
#ifndef CATOOL_FUNDAMENTALS_ARRAY
#define CATOOL_FUNDAMENTALS_ARRAY

#include<vector>

namespace catool
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
			Array() noexcept{}
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
				ArrayConstructor(arg...);
				dim.push_back(p);
			}
			void ArrayConstructor()
			{
				int sum = 0;
				for (const auto& each:dim)
					sum += each;
				data.resize(sum);
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
			std::vector<T> get_data() const{ return data; }
		};
		//functions
		inline int zeros()
		{
			return 0;
		}
		inline Array<int> zeros(int n)
		{
			return Array<int>(n,n);
		}

		inline Array<int> zeros_impl()
		{
			return Array<int>();
		}
		template<typename T1, typename... T2>
		inline Array<int> zeros_impl(T1 p, T2... arg)
		{
			Array<int> result = zeros_impl(arg...);
			result.dim.push_back(p);
			return result;
		}

		template<typename T1, typename... T2>
		inline Array<int> zeros(T1 p, T2... arg)
		{
			Array<int> result = zeros_impl(arg...);
			result.dim.push_back(p);
			return result;
		}

		inline Array<int> zeros(const Array<int> & dim)
		{
			Array<int> result;
			for (const auto& each:dim)
			{
				result.get_dim().push_back(each);
			}
			int sum = 0;
			for (const auto& each : dim)
				sum += each;
			result.get_data().resize(sum);
			return result;
		}

		
	}

}


#endif // !CATOOL_FUNDAMENTALS_ARRAY
