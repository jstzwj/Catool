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
#include<cmath>
#include"../../Stream/FileInputStream.h"
#include"../../Stream/FileOutputStream.h"
#include"../../../Array.h"
#include"ImageDefinition.h"

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
					char bfType[2];
					uint32_t bfSize;
					uint16_t bfReserved1;
					uint16_t bfReserved2;
					uint32_t bfOffBits;
				};
				struct tag_BitmapInfoHeader
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

				struct tag_RGBQuad
				{
					uint8_t rgbBlue; //该颜色的蓝色分量
					uint8_t rgbGreen; //该颜色的绿色分量
					uint8_t rgbRed; //该颜色的红色分量
					uint8_t rgbReserved; //保留值
				};

				enum class BiCompression :int
				{
					BI_RGB = 0,
					BI_RLE8 = 1,
					BI_BLE4 = 2,
					BI_BITFIELDS = 3,
					BI_JPEG = 4,
					BI_PNG = 5
				};

				class BmpReader
				{
				public:
					using StreamType = stream::InputStream<char>;
					std::unique_ptr<StreamType> data_source;

					template<class T>
					BmpReader(T &&stream)
						:data_source(new T(std::forward<T>(stream))) {}

					template<class T = double>
					Array<T> read(const char *path)
					{
						//file header
						tag_BitMapFileHeader file_header;
						data_source->read(file_header.bfType, 2);
						file_header.bfSize = stream::InputWrapper<uint32_t>::read(*data_source);//file size
						file_header.bfReserved1 = stream::InputWrapper<uint16_t>::read(*data_source);//reserved
						file_header.bfReserved2 = stream::InputWrapper<uint16_t>::read(*data_source);//reserved
						file_header.bfOffBits = stream::InputWrapper<uint32_t>::read(*data_source);//bytes before pic info

						//bitmap header
						tag_BitmapInfoHeader bitmap_header;
						bitmap_header.biSize = stream::InputWrapper<uint32_t>::read(*data_source);//bitmap info header size
						bitmap_header.biWidth = stream::InputWrapper<int32_t>::read(*data_source);//width
						bitmap_header.biHeight = stream::InputWrapper<int32_t>::read(*data_source);//height
						bitmap_header.biPlanes = stream::InputWrapper<uint16_t>::read(*data_source);//biplanes
						bitmap_header.biBitCount = stream::InputWrapper<uint16_t>::read(*data_source);//bitcount
						bitmap_header.biCompression = stream::InputWrapper<uint32_t>::read(*data_source);//bicompression
						bitmap_header.biSizeImage = stream::InputWrapper<uint32_t>::read(*data_source);//DWORD biSizeImage
						bitmap_header.biXPelsPerMeter = stream::InputWrapper<int32_t>::read(*data_source);//x
						bitmap_header.biYPelsPerMeter = stream::InputWrapper<int32_t>::read(*data_source);//y
						bitmap_header.biClrUsed = stream::InputWrapper<uint32_t>::read(*data_source);//index number
						bitmap_header.biClrImportant = stream::InputWrapper<uint32_t>::read(*data_source);//index number

						//index
						std::vector<tag_RGBQuad> color_index;

						for (std::uint32_t i = 0; i < bitmap_header.biClrUsed; ++i)
						{
							tag_RGBQuad quad;
							quad.rgbBlue = stream::InputWrapper<uint8_t>::read(*data_source);
							quad.rgbGreen = stream::InputWrapper<uint8_t>::read(*data_source);
							quad.rgbRed = stream::InputWrapper<uint8_t>::read(*data_source);
							quad.rgbReserved = stream::InputWrapper<uint8_t>::read(*data_source);
							color_index.push_back(quad);
						}
						//data
						Array<T> rst;
						if (bitmap_header.biBitCount == 1)
						{
							rst.resize(bitmap_header.biHeight, bitmap_header.biWidth);
							int acc1 = rst.get_dim_acc(1), acc2 = rst.get_dim_acc(2);
							for (int i = 0; i < bitmap_header.biHeight; ++i)
							{
								for (int j = 0; j < bitmap_header.biWidth / 8; ++j)
								{
									uint8_t tmp = stream::InputWrapper<uint8_t>::read(*data_source);
									rst[(j * 8 + 0)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x80) >> 7);
									rst[(j * 8 + 1)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x40) >> 6);
									rst[(j * 8 + 2)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x20) >> 5);
									rst[(j * 8 + 3)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x10) >> 4);
									rst[(j * 8 + 4)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x08) >> 3);
									rst[(j * 8 + 5)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x04) >> 2);
									rst[(j * 8 + 6)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert((tmp & 0x02) >> 1);
									rst[(j * 8 + 7)*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(tmp & 0x01);
								}
								//padding
								int padding_size = 4 * (int)std::ceil(8 * bitmap_header.biWidth / 32.0);
								for (int j = 0; j < padding_size - bitmap_header.biWidth; ++j)
								{
									stream::InputWrapper<uint8_t>::read(*data_source);
								}
							}
						}
						else if (bitmap_header.biBitCount == 4)
						{
							rst.resize(bitmap_header.biHeight, bitmap_header.biWidth, 3);
							int acc1 = rst.get_dim_acc(1), acc2 = rst.get_dim_acc(2);
							for (int i = 0; i < bitmap_header.biHeight; ++i)
							{
								for (int j = 0; j < bitmap_header.biWidth / 2; ++j)
								{
									//bgr->rgb
									uint8_t tmp = stream::InputWrapper<uint8_t>::read(*data_source);
									uint8_t sample1 = (tmp & 0xf0) >> 4;
									uint8_t sample2 = tmp & 0x0f;
									double scale = 1.0;

									if (sample1 == 0x8)
									{
										scale = 0.75294117647058823529411764705882;
										rst[0 * acc2 + (j * 2 + 0)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert(1);
										rst[1 * acc2 + (j * 2 + 0)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert(1);
										rst[2 * acc2 + (j * 2 + 0)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert(1);
									}
									else
									{
										if ((sample1 & 0x8) >> 3)
											scale = 1.0;
										else
											scale = 0.50196078431372549019607843137255;
										rst[0 * acc2 + (j * 2 + 0)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert((sample1 & 0x1) >> 0);
										rst[1 * acc2 + (j * 2 + 0)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert((sample1 & 0x2) >> 1);
										rst[2 * acc2 + (j * 2 + 0)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert((sample1 & 0x4) >> 2);
									}

									if (sample2 == 0x8)
									{
										scale = 0.75294117647058823529411764705882;
										rst[0 * acc2 + (j * 2 + 1)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert(1);
										rst[1 * acc2 + (j * 2 + 1)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert(1);
										rst[2 * acc2 + (j * 2 + 1)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert(1);
									}
									else
									{
										if ((sample2 & 0x8) >> 3)
											scale = 1.0;
										else
											scale = 0.50196078431372549019607843137255;
										rst[0 * acc2 + (j * 2 + 1)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert((sample2 & 0x1) >> 0);
										rst[1 * acc2 + (j * 2 + 1)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert((sample2 & 0x2) >> 1);
										rst[2 * acc2 + (j * 2 + 1)*acc1 + i] = scale*ImageConvert<std::uint8_t, T>::convert((sample2 & 0x4) >> 2);
									}
								}
								//padding
								int padding_size = 4 * (int)std::ceil(8 * bitmap_header.biWidth / 32.0);
								for (int j = 0; j < padding_size - bitmap_header.biWidth; ++j)
								{
									stream::InputWrapper<uint8_t>::read(*data_source);
								}
							}
						}
						else if (bitmap_header.biBitCount == 1 * 8)
						{
							rst.resize(bitmap_header.biHeight, bitmap_header.biWidth, 1);
							int acc1 = rst.get_dim_acc(1), acc2 = rst.get_dim_acc(2);
							for (int i = 0; i < bitmap_header.biHeight; ++i)
							{
								for (int j = 0; j < bitmap_header.biWidth; ++j)
								{
									rst[j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
								}
								//padding
								int padding_size = 4 * (int)std::ceil(8 * bitmap_header.biWidth / 32.0);
								for (int j = 0; j < padding_size - bitmap_header.biWidth; ++j)
								{
									stream::InputWrapper<uint8_t>::read(*data_source);
								}
							}
						}
						else if (bitmap_header.biBitCount == 3 * 8)
						{
							rst.resize(bitmap_header.biHeight, bitmap_header.biWidth, 3);
							int acc1 = rst.get_dim_acc(1), acc2 = rst.get_dim_acc(2);
							for (int i = 0; i < bitmap_header.biHeight; ++i)
							{
								for (int j = 0; j < bitmap_header.biWidth; ++j)
								{
									//bgr->rgb
									rst[2 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
									rst[1 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
									rst[0 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
								}
								//padding
								int padding_size = 4 * (int)std::ceil(24 * bitmap_header.biWidth / 32.0);
								for (int j = 0; j < padding_size - bitmap_header.biWidth * 3; ++j)
								{
									stream::InputWrapper<uint8_t>::read(*data_source);
								}
							}
						}
						else if (bitmap_header.biBitCount == 4 * 8)
						{
							rst.resize(bitmap_header.biHeight, bitmap_header.biWidth, 4);
							int acc1 = rst.get_dim_acc(1), acc2 = rst.get_dim_acc(2);
							for (int i = 0; i < bitmap_header.biHeight; ++i)
							{
								for (int j = 0; j < bitmap_header.biWidth; ++j)
								{
									//bgr->rgb
									rst[2 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
									rst[1 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
									rst[0 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
									rst[3 * acc2 + j*acc1 + i] = ImageConvert<std::uint8_t, T>::convert(stream::InputWrapper<uint8_t>::read(*data_source));
								}
							}
						}
						else
						{
							throw std::runtime_error("error: imread: unknown file color depth.");
						}
						if (bitmap_header.biHeight > 0)
							flip_in_place(rst, 0);
						return rst;
					}
				};
				class BmpWriter
				{
				public:
					using StreamType = stream::OutputStream<char>;
					std::unique_ptr<StreamType> data_source;

					template<class T>
					BmpWriter(T &&stream)
						:data_source(new T(std::forward<T>(stream))) {}

					template<class T>
					void write(const Array<T>& a)
					{
						int acc1 = a.get_dim_acc(1), acc2 = a.get_dim_acc(2);
						int d0 = a.get_dim_data(0), d1 = a.get_dim_data(1), d2 = a.get_dim_data(2);
						if (d2 != 1 && d2 != 3 && d2 != 4)
						{
							throw std::runtime_error("error: imwrite: IMG 3rd dimension must be 1, 3, or 4");
						}
						//file header
						data_source->write("BM", 2);
						if (d2 == 1)
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1 * 3 + 14 + 40);//file size
						else
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1*d2 + 14 + 40);//file size
						stream::OutputWrapper<uint16_t>::write(*data_source, 0);//reserved
						stream::OutputWrapper<uint16_t>::write(*data_source, 0);//reserved
						stream::OutputWrapper<uint32_t>::write(*data_source, 14 + 40);//bytes before pic info

						//bitmap header
						stream::OutputWrapper<uint32_t>::write(*data_source, 40);//bitmap info header size
						stream::OutputWrapper<int32_t>::write(*data_source, a.get_dim_data(1));//width
						stream::OutputWrapper<int32_t>::write(*data_source, -a.get_dim_data(0));//height
						stream::OutputWrapper<uint16_t>::write(*data_source, 1);//biplanes
						if (d2 == 1)
							stream::OutputWrapper<uint16_t>::write(*data_source, 24);//bitcount
						else
							stream::OutputWrapper<uint16_t>::write(*data_source, d2 * 8);//bitcount
						stream::OutputWrapper<uint32_t>::write(*data_source, (uint32_t)BiCompression::BI_RGB);//bicompression
						if (d2 == 1)
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1 * 3);//DWORD biSizeImage
						else
							stream::OutputWrapper<uint32_t>::write(*data_source, d0*d1*d2);//DWORD biSizeImage
						stream::OutputWrapper<int32_t>::write(*data_source, 0);//x
						stream::OutputWrapper<int32_t>::write(*data_source, 0);//y
						stream::OutputWrapper<uint32_t>::write(*data_source, 0);//index number
						stream::OutputWrapper<uint32_t>::write(*data_source, 0);//index number
						//data
						if (d2 == 1)
						{
							for (int i = 0; i < d0; ++i)
							{
								for (int j = 0; j < d1; ++j)
								{
									stream::OutputWrapper<uint8_t>::write(*data_source, ImageConvert<T, std::uint8_t>::convert(a[j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source, ImageConvert<T, std::uint8_t>::convert(a[j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source, ImageConvert<T, std::uint8_t>::convert(a[j*acc1 + i]));
								}
								//padding
								int padding_size = 4 * (int)std::ceil(24 * d1 / 32.0);
								for (int j = 0; j < padding_size - d1 * 3; ++j)
								{
									stream::OutputWrapper<uint8_t>::write(*data_source, 0);
								}
							}
						}
						else if (d2 == 3)
						{
							for (int i = 0; i < d0; ++i)
							{
								for (int j = 0; j < d1; ++j)
								{
									//rgb ->bgr
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[2 * acc2 + j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[1 * acc2 + j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[0 * acc2 + j*acc1 + i]));
								}
								//padding
								int padding_size = 4 * (int)std::ceil(24 * d1 / 32.0);
								for (int j = 0; j < padding_size - d1 * 3; ++j)
								{
									stream::OutputWrapper<uint8_t>::write(*data_source, 0);
								}
							}
						}
						else if (d2 == 4)
						{
							for (int i = 0; i < d0; ++i)
							{
								for (int j = 0; j < d1; ++j)
								{
									//rgb->bgr
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[2 * acc2 + j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[1 * acc2 + j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[0 * acc2 + j*acc1 + i]));
									stream::OutputWrapper<uint8_t>::write(*data_source,
										ImageConvert<T, std::uint8_t>::convert(a[3 * acc2 + j*acc1 + i]));
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