#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_AUDIO_H
#define CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_AUDIO_H

#include<memory>
#include<type_traits>
#include<utility>
#include<string>
#include <cstddef>
#include<cstdio>
#include<cstring>
#include"Wav.h"
#include"../../Stream/FileInputStream.h"
#include"../../Stream/FileOutputStream.h"
#include"../../../Array.h"


namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			namespace audio
			{
				template<class SampleType= float>
				std::tuple<Array<SampleType>, int> audioread(const char *path, int samples = 44100)
				{
					std::FILE * file = nullptr;
#ifdef _MSC_VER
					fopen_s(&file,path, "rb");
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
					if (split_pos==-1)
					{
						throw std::runtime_error("Unknown audio type.");
					}
					type = p.substr(split_pos+1, p.length() - split_pos);

					std::tuple<Array<uint16_t>, int> audio_data;

					if (type=="wav")
					{
						stream::FileInputStream stream(file);
						WaveReader reader(std::move(stream));
						audio_data = reader.read();
					}
					else
					{
						throw std::runtime_error("Unknown audio type.");
					}
					std::fclose(file);
					return audio_data;
				}
				template<class SampleType = float>
				void audiowrite(const char *path, const Array<SampleType>& y, int samples = 44100)
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
						throw std::runtime_error("Unknown audio type.");
					}
					type = p.substr(split_pos+1, p.length() - split_pos);

					if (type == "wav")
					{
						stream::FileOutputStream stream(file);
						WaveWriter writer(std::move(stream));
						writer.write(y, samples);
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
#endif //CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_AUDIO_H