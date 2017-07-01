#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_BMP_H
#define CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_BMP_H

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


namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			namespace images
			{
				struct tag_BitMapFileHeader
				{
					uint16_t bfType;
					uint32_t bfSize;
					uint16_t bfReserved1;
					uint16_t bfReserved2;
					uint32_t bfOffBits;
				};



			}
		}
	}
}

#endif //CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_BMP_H