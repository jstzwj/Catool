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

			std::vector<Range> range = m.getFullLoop();
			for (int i=0;i<m.get_dim_data(dim);++i)
			{
				range[dim] = Range(i);
				m.loop(range, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
				{
					int index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != dim)
							index += dims[i] * result.get_dim_acc(i);
					}
					//init min
					if (dims[dim]==0)
					{
						result[index] = m[m.composeIndex(dims)];
					}
					else
					{
						if (result[index] > m[m.composeIndex(dims)])
							result[index] = m[m.composeIndex(dims)];
					}
				});
			}
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

			std::vector<Range> range = m.getFullLoop();
			for (int i = 0; i<m.get_dim_data(dim); ++i)
			{
				range[dim] = Range(i);
				m.loop(range, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
				{
					int index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != dim)
							index += dims[i] * result.get_dim_acc(i);
					}
					//init max
					if (dims[dim] == 0)
					{
						result[index] = m[m.composeIndex(dims)];
					}
					else
					{
						if (result[index] < m[m.composeIndex(dims)])
							result[index] = m[m.composeIndex(dims)];
					}
				});
			}
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


		}
	}
}


#endif // !CATOOL_MAINTOOLBOX_DATA_DESCRIPTIVESTATISTICS_H