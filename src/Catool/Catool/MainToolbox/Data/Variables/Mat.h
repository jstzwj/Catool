#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_VARIABLE_MAT_H
#define CATOOL_MAINTOOLBOX_DATA_VARIABLE_MAT_H

#include<iostream>
#include<stdexcept>
#include<vector>

#include"../../Array.h"
namespace catool
{
	namespace main_toolbox
	{
		enum class FileTag {MAT,ASCII};

		template<class T>
		inline std::vector<Array<T>> load_mat(const char *c)
		{

		}

		template<class T>
		inline std::vector<Array<T>> load_ascii(const char *c)
		{

		}

		template<class T>
		inline std::vector<Array<T>> load(const char *c,FileTag tag)
		{
			if (tag == FileTag::MAT)
			{
				return load_ma<T>t(c);
			}
			else if (tag== FileTag::ASCII)
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
