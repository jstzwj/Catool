#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_IMAGE_H
#define CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_IMAGE_H

#include<memory>
#include<type_traits>
#include<utility>
#include<string>
#include <cstddef>
#include<cstdio>
#include<cstring>
#include"../../Stream/FileInputStream.h"
#include"../../Stream/FileOutputStream.h"
#include"../../../Array.h"
#include"Bmp.h"

namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			namespace images
			{
				template<class T = double>
				Array<T> imread(const char *path)
				{
					std::FILE * file = nullptr;
#ifdef _MSC_VER
					fopen_s(&file, path, "rb");
#else
					file = std::fopen(path, "rb");
#endif // _MSC_VER

					if (file == nullptr)
					{
						throw std::runtime_error("fail to open file.");
					}
					std::string p(path);
					std::string type;
					int split_pos = p.find_last_of('.');
					if (split_pos == -1)
					{
						throw std::runtime_error("Unknown image type.");
					}
					type = p.substr(split_pos + 1, p.length() - split_pos);

					Array<T> image_data;

					if (type == "bmp")
					{
						stream::FileInputStream stream(file);
						BmpReader reader(std::move(stream));
						image_data = reader.read<T>(path);
					}
					else
					{
						throw std::runtime_error("Unknown audio type.");
					}
					std::fclose(file);
					return image_data;
				}
				template<class T>
				void imwrite(const Array<T>& img, const char * path)
				{
					std::FILE * file = nullptr;
#ifdef _MSC_VER
					fopen_s(&file, path, "wb");
#else
					file = std::fopen(path, "wb");
#endif // _MSC_VER
					if (file == nullptr)
					{
						throw std::runtime_error("fail to open file.");
					}

					std::string p(path);
					std::string type;
					int split_pos = p.find_last_of('.');
					if (split_pos == -1)
					{
						throw std::runtime_error("Unknown image type.");
					}
					type = p.substr(split_pos + 1, p.length() - split_pos);

					if (type == "bmp")
					{
						stream::FileOutputStream stream(file);
						BmpWriter writer(std::move(stream));
						writer.write(img);
					}
					else
					{
						throw std::runtime_error("Unknown audio type.");
					}
					std::fclose(file);
				}
			}
		}
	}
}

#endif //CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_IMAGE_H