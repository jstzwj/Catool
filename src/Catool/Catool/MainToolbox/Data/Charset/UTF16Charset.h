#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_UTF16CHARSET
#define CATOOL_MAINTOOLBOX_DATA_UTF16CHARSET

namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			template <typename T>
			class UTF16Charset {
			public:
				using CharType = T;

				static const char* getName() { return "UTF-16"; }

				static char32_t decode(const T*& p, const T* q) { return 0; }
				static bool encode(T*& p, T* q, char32_t codepoint) { return false; }
			};
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_DATA_UTF16CHARSET
