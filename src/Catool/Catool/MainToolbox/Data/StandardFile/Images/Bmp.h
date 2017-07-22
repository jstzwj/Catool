#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_BMP_H
#define CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_BMP_H

#include<memory>
#include<type_traits>
#include<utility>
#include<string>
#include<memory>
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
				struct tag_BITMAPINFOHEADER 
				{
					uint32_t biSize; //指定此结构体的长度，为40
					int32_t biWidth; //位图宽
					int32_t biHeight; //位图高
					uint16_t biPlanes; //平面数，为1
					uint16_t biBitCount; //采用颜色位数，可以是1，2，4，8，16，24，新的可以是32
					uint32_t biCompression; //压缩方式，可以是0，1，2，其中0表示不压缩
					uint32_t biSizeImage; //实际位图数据占用的字节数
					int32_t biXPelsPerMeter; //X方向分辨率
					int32_t biYPelsPerMeter; //Y方向分辨率
					uint32_t biClrUsed; //使用的颜色数，如果为0，则表示默认值(2^颜色位数)
					uint32_t biClrImportant; //重要颜色数，如果为0，则表示所有颜色都是重要的
				};

				struct tag_RGBQUAD 
				{
					uint8_t rgbBlue; //该颜色的蓝色分量
					uint8_t rgbGreen; //该颜色的绿色分量
					uint8_t rgbRed; //该颜色的红色分量
					uint8_t rgbReserved; //保留值
				};

				enum class BiCompression :int
				{
					BI_RGB=0,
					BI_RLE8=1,
					BI_BLE4=2,
					BI_BITFIELDS=3,
					BI_JPEG=4,
					BI_PNG=5
				};


				class BmpReader
				{
				public:

				};
				class BmpWriter
				{
				public:
					using StreamType = stream::OutputStream<char>;
					std::unique_ptr<StreamType> data_source;

					template<class T>
					BmpWriter(T &&stream)
						:data_source(new T(std::forward<T>(stream))) {}

					static uint8_t toFileType(double d)
					{
						double tmp=d*255;
						if (tmp > 255)
						{
							return 255;
						}
						else if (tmp < 0)
						{
							return 0;
						}
						else
						{
							return (uint8_t)tmp;
						}
					}
					static uint8_t toFileType(int d)
					{
						return (uint8_t)d;
					}
					template<class T>
					void write(const Array<T>& a)
					{
						int acc1 = a.get_dim_acc(1), acc2 = a.get_dim_acc(2);
						int d0 = a.get_dim_data(0), d1 = a.get_dim_data(1), d2 = a.get_dim_data(2);
						if (d2!=1&&d2!=3&&d2!=4)
						{
							throw std::runtime_error("error: imwrite: IMG 3rd dimension must be 1, 3, or 4");
						}
						//file header
						data_source->write("BM", 2);
						if(d2==1)
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1*3 + 14 + 40);//file size
						else
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1*d2 + 14 + 40);//file size
						stream::OutputWrapper<uint16_t>::write(*data_source, 0);//reserved
						stream::OutputWrapper<uint16_t>::write(*data_source, 0);//reserved
						stream::OutputWrapper<uint32_t>::write(*data_source, 14+40);//bytes before pic info

						//bitmap header
						stream::OutputWrapper<uint32_t>::write(*data_source, 40);//bitmap info header size
						stream::OutputWrapper<int32_t>::write(*data_source, a.get_dim_data(1));//width
						stream::OutputWrapper<int32_t>::write(*data_source, a.get_dim_data(0));//height
						stream::OutputWrapper<uint16_t>::write(*data_source, 1);//biplanes
						if (d2 == 1)
							stream::OutputWrapper<uint16_t>::write(*data_source, 24);//bitcount
						else
							stream::OutputWrapper<uint16_t>::write(*data_source, d2 * 8);//bitcount
						stream::OutputWrapper<uint32_t>::write(*data_source, (uint32_t)BiCompression::BI_RGB);//bicompression
						if (d2 == 1)
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1*3);//DWORD biSizeImage
						else
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1*d2);//DWORD biSizeImage
						stream::OutputWrapper<int32_t>::write(*data_source, 0);//x
						stream::OutputWrapper<int32_t>::write(*data_source, 0);//y
						stream::OutputWrapper<uint32_t>::write(*data_source, 0);//index number
						stream::OutputWrapper<uint32_t>::write(*data_source, 0);//index number
						//data
						if (d2 == 1)
						{
							for (int i = 0; i<d1; ++i)
							{
								for (int j = 0; j<d0; ++j)
								{
									stream::OutputWrapper<uint8_t>::write(*data_source, toFileType(a[i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source, toFileType(a[i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source, toFileType(a[i*acc1 + j]));
								}
							}
						}
						else if (d2 == 3)
						{
							for (int i = 0; i<d1; ++i)
							{
								for (int j = 0; j<d0; ++j)
								{
									stream::OutputWrapper<uint8_t>::write(*data_source, 
										toFileType(a[0 * acc2 + i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										toFileType(a[1 * acc2 + i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source, 
										toFileType(a[2 * acc2 + i*acc1 + j]));
								}
							}
						}
						else if (d2 == 4)
						{
							for (int i = 0; i<d1; ++i)
							{
								for (int j = 0; j<d0; ++j)
								{
									stream::OutputWrapper<uint8_t>::write(*data_source,
										toFileType(a[0 * acc2 + i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										toFileType(a[1 * acc2 + i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										toFileType(a[2 * acc2 + i*acc1 + j]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										toFileType(a[3 * acc2 + i*acc1 + j]));
								}
							}
						}
						else
						{
							throw std::runtime_error("error: imwrite: IMG 3rd dimension must be 1, 3, or 4");
						}
					}
				};


			}
		}
	}
}

#endif //CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_IMAGES_BMP_H