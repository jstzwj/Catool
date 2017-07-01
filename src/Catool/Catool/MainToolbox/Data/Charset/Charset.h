#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_CHARSET
#define CATOOL_MAINTOOLBOX_DATA_CHARSET

#include <cstddef>


namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			template <typename T>
			class Charset 
			{
			public:
				using CharType = T;

				static const char* getName() { return "Abstract charset."; }

				static char32_t decode(const T*& p, const T* q) { return 0; }
				static bool encode(T*& p, T* q, char32_t codepoint) { return false; }

			};
		}
	}
}





#endif // !CATOOL_MAINTOOLBOX_DATA_CHARSET
