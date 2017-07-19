#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_DESCRIPTIVESTATISTICS_H
#define CATOOL_MAINTOOLBOX_DATA_DESCRIPTIVESTATISTICS_H 

#include<tuple>
#include"../Array.h"

namespace catool
{
	namespace main_toolbox
	{
		/*min	Smallest elements in array*/
		template<class T>
		Array<T> min(const Array<T>& m,int dim=0)
		{
			Array<T> result;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result.resize(dims);

			m.dimloop(dim, [&result, &dim](const Array<T>& m, std::vector<int>&dims)
			{
				int rst_index = 0;
				for (unsigned int i = 0; i < dims.size(); ++i)
				{
					if (i != dim)
						rst_index += dims[i] * result.get_dim_acc(i);
				}
				int index = m.composeIndex(dims);
				int acc = m.get_dim_acc(dim);
				int len = m.get_dim_data(dim);

				typename Array<T>::ConstIntervalIterator begin(m, index, acc);
				typename Array<T>::ConstIntervalIterator end(m, index + len*acc, acc);
				result[rst_index] = *(std::min_element(begin, end));
			});
			return result;
		}

		/*max	Largest elements in array*/
		template<class T>
		Array<T> max(const Array<T>& m, int dim=0)
		{
			Array<T> result;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result.resize(dims);

			m.dimloop(dim, [&result, &dim](const Array<T>& m, std::vector<int>&dims)
			{
				int rst_index = 0;
				for (unsigned int i = 0; i < dims.size(); ++i)
				{
					if (i != dim)
						rst_index += dims[i] * result.get_dim_acc(i);
				}
				int index = m.composeIndex(dims);
				int acc = m.get_dim_acc(dim);
				int len = m.get_dim_data(dim);

				typename Array<T>::ConstIntervalIterator begin(m, index, acc);
				typename Array<T>::ConstIntervalIterator end(m, index + len*acc, acc);
				result[rst_index]=*(std::max_element(begin, end));
			});
			return result;
		}
		/*bounds	Smallest and largest elements*/
		template<class T>
		std::tuple<Array<T>, Array<T>> bounds(const Array<T>& m, int dim=0)
		{
			Array<T> result_min,result_max;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result_min.resize(dims);
			result_max.resize(dims);

			std::vector<Range> range = m.getFullLoop();
			for (int i = 0; i<m.get_dim_data(dim); ++i)
			{
				range[dim] = Range(i);
				m.loop(range, [&result_min,&result_max, &dim](const Array<T>& m, const std::vector<int>&dims)
				{
					int index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != dim)
							index += dims[i] * result.get_dim_acc(i);
					}
					//init min and max
					if (dims[dim] == 0)
					{
						result_min[index] = m[m.composeIndex(dims)];
						result_max[index] = m[m.composeIndex(dims)];
					}
					else
					{
						if (result_max[index] < m[m.composeIndex(dims)])
							result_max[index] = m[m.composeIndex(dims)];
						if (result_min[index] > m[m.composeIndex(dims)])
							result_min[index] = m[m.composeIndex(dims)];
					}
				});
			}
			return {result_min,result_max};
		}

		/*mean	Average or mean value of array*/
		template<class T>
		Array<double> mean(const Array<T> & m,int dim=0)
		{
			return rdivide(sum(static_cast<Array<double>>(m),dim),size(m,dim));
		}
	}
}


#endif // !CATOOL_MAINTOOLBOX_DATA_DESCRIPTIVESTATISTICS_H