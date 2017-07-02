#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_WAV
#define CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_WAV

#include<memory>
#include<type_traits>
#include<utility>
#include <cstddef>
#include<cstdio>
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
				enum RiffBlockType { UNKNOWN, HEADER, FORMAT, FACT, DATA };

				struct RIFF_header
				{
					char szRiffID[4];  // 'R','I','F','F'
					uint32_t dwRiffSize;
					char szRiffFormat[4]; // 'W','A','V','E'
				};

				enum FORMAT_TAG
				{
					WAVE_FORMAT_PCM = 1
				};

				struct WAVE_format
				{
					uint16_t wFormatTag;
					uint16_t wChannels;
					uint32_t dwSamplesPerSec;
					uint32_t dwAvgBytesPerSec;
					uint16_t wBlockAlign;
					uint16_t wBitsPerSample;
				};

				struct FMT_block
				{
					char  szFmtID[4]; // 'f','m','t',' '
					uint32_t  dwFmtSize;
					WAVE_format wavFormat;
				};

				struct FACT_block
				{
					char  szFactID[4]; // 'f','a','c','t'
					uint32_t  dwFactSize;
				};

				struct DATA_block
				{
					char szDataID[4]; // 'd','a','t','a'
					uint32_t dwDataSize;
				};

				struct Data_chunk_16d
				{
					uint16_t data_left;
					uint16_t data_rght;
				};
				struct Data_chunk_16s
				{
					uint16_t data1;
					uint16_t data2;
				};

				class WaveWriter
				{
				public:
					using StreamType = stream::OutputStream<char>;
					std::unique_ptr<StreamType> data_source;

					template<class T>
					WaveWriter(T &&stream)
						:data_source(new T(std::forward<T>(stream))) {}
					template<class SampleType>
					void write(const Array<SampleType>& audio, int samplesPerSec = 44100)
					{
						//write riff header
						data_source->write("RIFF", 4);
						stream::OutputWrapper<uint32_t>::write(*data_source, audio.size()*sizeof(SampleType) + 44 - 8);
						data_source->write("WAVE", 4);

						//write format block
						data_source->write("fmt ", 4);
						stream::OutputWrapper<uint32_t>::write(*data_source, 16);
						stream::OutputWrapper<uint16_t>::write(*data_source, FORMAT_TAG::WAVE_FORMAT_PCM);
						stream::OutputWrapper<uint16_t>::write(*data_source, audio.get_dim_data(1));
						stream::OutputWrapper<uint32_t>::write(*data_source, samplesPerSec);
						stream::OutputWrapper<uint32_t>::write(*data_source, sizeof(SampleType)*audio.get_dim_data(1)*samplesPerSec);
						stream::OutputWrapper<uint16_t>::write(*data_source, sizeof(SampleType)*audio.get_dim_data(1));
						stream::OutputWrapper<uint16_t>::write(*data_source, sizeof(SampleType) * 8);

						//write data block
						data_source->write("data", 4);
						stream::OutputWrapper<uint32_t>::write(*data_source, audio.size()*sizeof(SampleType));
						//write data
						if (audio.dim_size() == 1)
						{
							for (int i = 0; i < audio.get_dim_data(0); ++i)
							{
								stream::OutputWrapper<SampleType>::write(*data_source, audio[i]);
							}
						}
						else
						{
							for (int i = 0; i < audio.get_dim_data(0); ++i)
							{
								stream::OutputWrapper<SampleType>::write(*data_source, audio[i]);
								stream::OutputWrapper<SampleType>::write(*data_source, audio[audio.get_dim_data(0) + i]);
							}
						}
					}
				};

				class WaveReader
				{
				public:
					using StreamType = stream::InputStream<char>;
					std::unique_ptr<StreamType> data_source;

					template<class T>
					WaveReader(T &&stream)
						:data_source(new T(std::forward<T>(stream))) {}

					std::tuple<Array<uint16_t>, int> read()
					{
						Array<uint16_t> result;
						//Read Riff header
						RIFF_header header;
						data_source->read(header.szRiffID, sizeof(header.szRiffID));
						if (memcmp(header.szRiffID, "RIFF", 4) == 0)
						{
							header.dwRiffSize = stream::InputWrapper<uint32_t>::read(*data_source);
							data_source->read(header.szRiffFormat, sizeof(header.szRiffFormat));
							if (memcmp(header.szRiffFormat, "WAVE", 4) != 0)
							{
								throw std::exception("Can not use WaveReader to read the file.");
							}
						}
						else
						{
							throw std::exception("Wave file header can not be found.");
						}

						//Read riff format
						FMT_block format;
						WAVE_format wave_format;
						data_source->read(format.szFmtID, sizeof(format.szFmtID));
						if (memcmp(format.szFmtID, "fmt ", 4) == 0)
						{
							format.dwFmtSize = stream::InputWrapper<uint32_t>::read(*data_source);
							//Read wave format
							wave_format.wFormatTag = stream::InputWrapper<uint16_t>::read(*data_source);
							if (wave_format.wFormatTag != FORMAT_TAG::WAVE_FORMAT_PCM)
							{
								throw std::exception("Do not support the wave format.");
							}
							wave_format.wChannels = stream::InputWrapper<uint16_t>::read(*data_source);
							wave_format.dwSamplesPerSec = stream::InputWrapper<uint32_t>::read(*data_source);
							wave_format.dwAvgBytesPerSec = stream::InputWrapper<uint32_t>::read(*data_source);
							wave_format.wBlockAlign = stream::InputWrapper<uint16_t>::read(*data_source);
							wave_format.wBitsPerSample = stream::InputWrapper<uint16_t>::read(*data_source);
							data_source->seek(format.dwFmtSize - sizeof(wave_format), StreamType::PosType::Current);
						}
						else
						{
							throw std::exception("Wave file format can not be found.");
						}
						//Read fact and data blocks
						FACT_block fact;
						data_source->read(fact.szFactID, 4);
						if (memcmp(fact.szFactID, "fact", 4) == 0)
						{
							//TODO
							data_source->seek(sizeof(FACT_block) - sizeof(fact.szFactID), StreamType::PosType::Current);
						}
						else
						{
							data_source->seek(-4, StreamType::PosType::Current);
						}
						DATA_block data;
						data_source->read(data.szDataID, 4);
						if (memcmp(data.szDataID, "data", 4) == 0)
						{
							data.dwDataSize = stream::InputWrapper<uint32_t>::read(*data_source);
						}
						else
						{
							throw std::exception("Unknown block type.");
						}

						if (wave_format.wChannels == 1)
						{
							result.resize(data.dwDataSize / wave_format.wBitsPerSample * 8);
						}
						else
						{
							result.resize(2, data.dwDataSize / wave_format.wBitsPerSample * 4);
						}
						uint32_t blockAlign = wave_format.wChannels*wave_format.wBitsPerSample;
						if (wave_format.wChannels == 2)
						{
							if (wave_format.wBitsPerSample == 16)
							{
								for (uint32_t i = 0; i < data.dwDataSize / blockAlign; ++i)
								{
									result[i] = stream::InputWrapper<uint16_t>::read(*data_source);
									result[result.get_dim_data(0) + i] = stream::InputWrapper<uint16_t>::read(*data_source);
								}
							}
							else
							{
								for (uint32_t i = 0; i < data.dwDataSize / blockAlign; ++i)
								{
									result[i] = stream::InputWrapper<uint8_t>::read(*data_source);
									result[result.get_dim_data(0) + i] = stream::InputWrapper<uint8_t>::read(*data_source);
								}
							}
						}
						else
						{
							if (wave_format.wBitsPerSample == 16)
							{
								for (uint32_t i = 0; i < data.dwDataSize / blockAlign; ++i)
								{
									result[i] = stream::InputWrapper<uint16_t>::read(*data_source);
								}
							}
							else
							{
								for (uint32_t i = 0; i < data.dwDataSize / blockAlign; ++i)
								{
									result[i] = stream::InputWrapper<uint8_t>::read(*data_source);
								}
							}
						}
						return std::make_tuple(result, wave_format.dwSamplesPerSec);
					}
				};
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_WAV
