#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_AUDIODEFINITION_H
#define CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_AUDIODEFINITION_H

#include<limits>
#include<cstdint>


namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			namespace audio
			{

				template<class T, class U>
				class AudioConvert
				{
				public:
					static U convert(T val)
					{
						return static_cast<U>(val);
					}
				};
				template<>
				class AudioConvert<std::uint16_t,double>
				{
				public:
					static double convert(std::uint16_t val)
					{
						return static_cast<double>(val) / std::numeric_limits<std::uint16_t>::max();
					}
				};
				template<>
				class AudioConvert<std::uint16_t,float>
				{
				public:
					static float convert(std::uint16_t val)
					{
						return static_cast<float>(val) / std::numeric_limits<std::uint16_t>::max();
					}
				};


				template<>
				class AudioConvert<double,std::uint16_t>
				{
				public:
					static std::uint16_t convert(double val)
					{
						if (val > 1)
						{
							return static_cast<std::uint16_t>(1.0*std::numeric_limits<std::uint16_t>::max());
						}
						else if (val < 0)
						{
							return 0;
						}
						else
						{
							return static_cast<std::uint16_t>(val*std::numeric_limits<std::uint16_t>::max());
						}
					}
				};
				template<>
				class AudioConvert<float,std::uint16_t>
				{
				public:
					static std::uint16_t convert(float val)
					{
						if (val > 1)
						{
							return static_cast<std::uint16_t>(1.0*std::numeric_limits<std::uint16_t>::max());
						}
						else if (val < 0)
						{
							return 0;
						}
						else
						{
							return static_cast<std::uint16_t>(val*std::numeric_limits<std::uint16_t>::max());
						}
					}
				};
			}
		}
	}
}


#endif // !CATOOL_MAINTOOLBOX_DATA_STANDARDFILE_AUDIO_AUDIODEFINITION_H