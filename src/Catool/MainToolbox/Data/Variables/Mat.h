#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_VARIABLE_MAT_H
#define CATOOL_MAINTOOLBOX_DATA_VARIABLE_MAT_H

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<stdexcept>
#include<vector>

#include"../../Array.h"
namespace catool
{
	namespace main_toolbox
	{
		enum class FileTag { MAT, ASCII };

		template<class T>
		inline std::vector<Array<T>> load_mat(const char *c)
		{
			std::vector<Array<T>> rst;
			return rst;
		}

		template<class T>
		inline std::vector<Array<T>> load_ascii(const char *c)
		{
			std::string line;
			std::ifstream infile(c);
			if (infile.bad())
			{
				throw std::runtime_error("error:load_ascii:fail to open the file.");
			}

			std::vector<T> tmp;
			int row = 0;
			int col = 0;
			while (std::getline(infile, line))
			{
				std::stringstream ss(line);
				T val;
				while (ss >> val)
				{
					tmp.push_back(val);
					if (row == 0)	//count colum number of the first line
						++col;
				}
				++row;
			}

			Array<T> arry;
			arry.resize(row, col);
			for (int i = 0; i < row; ++i)
			{
				for (int j = 0; j < col; ++j)
				{
					arry[j*row + i] = tmp[i*col + j];
				}
			}
			std::vector<Array<T>> rst;
			rst.push_back(arry);
			return rst;
		}

		template<class T>
		inline std::vector<Array<T>> load(const char *c, FileTag tag)
		{
			if (tag == FileTag::MAT)
			{
				return load_mat<T>(c);
			}
			else if (tag == FileTag::ASCII)
			{
				return load_ascii<T>(c);
			}
			else
			{
				throw std::runtime_error("error load:unknown file type.");
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_DATA_VARIABLE_MAT_H
