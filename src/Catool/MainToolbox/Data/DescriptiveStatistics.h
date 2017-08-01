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
		Array<T> min(const Array<T>& m, int dim = 0)
		{
			Array<T> result;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result.resize(dims);

			m.dimloop(dim, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
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
		Array<T> max(const Array<T>& m, int dim = 0)
		{
			Array<T> result;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result.resize(dims);

			m.dimloop(dim, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
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
				result[rst_index] = *(std::max_element(begin, end));
			});
			return result;
		}
		/*bounds	Smallest and largest elements*/
		template<class T>
		std::tuple<Array<T>, Array<T>> bounds(const Array<T>& m, int dim = 0)
		{
			Array<T> result_min, result_max;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result_min.resize(dims);
			result_max.resize(dims);

			m.dimloop(dim, [&result_min, &result_max, &dim](const Array<T>& m, const std::vector<int>&dims)
			{
				int rst_index = 0;
				for (unsigned int i = 0; i < dims.size(); ++i)
				{
					if (i != dim)
						rst_index += dims[i] * result_min.get_dim_acc(i);
				}
				int index = m.composeIndex(dims);
				int acc = m.get_dim_acc(dim);
				int len = m.get_dim_data(dim);

				typename Array<T>::ConstIntervalIterator begin(m, index, acc);
				typename Array<T>::ConstIntervalIterator end(m, index + len*acc, acc);
				auto minmax_pair = std::minmax_element(begin, end);
				result_min[rst_index] = minmax_pair.first;
				result_max[rst_index] = minmax_pair.second;
			});
			return{ result_min ,result_max };
		}

		/*mean	Average or mean value of array*/
		template<class T>
		Array<double> mean(const Array<T> & m, int dim = 0)
		{
			return rdivide((Array<double>)sum(m, dim), size(m, dim));
		}

		/*
		median
		Median value of array
		*/
		template<class T>
		Array<T> median(const Array<T>& m, int dim = 0)
		{
			Array<T> result;
			std::vector<int> dims = m.get_dim();
			dims[dim] = 1;
			result.resize(dims);

			std::vector<T> tmp;
			tmp.resize(m.get_dim_data(dim));

			m.dimloop(dim, [&tmp, &result, &dim](const Array<T>& m, const std::vector<int>&dims)
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

				std::copy(begin, end, tmp.begin());

				std::nth_element(tmp.begin(), tmp.begin() + tmp.size() / 2, tmp.end());

				result[rst_index] = tmp[tmp.size() / 2];
			});
			return result;
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_DATA_DESCRIPTIVESTATISTICS_H