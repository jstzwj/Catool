#pragma once
#ifndef CATOOL_MAINTOOLBOX_DATA_UTF32CHARSET
#define CATOOL_MAINTOOLBOX_DATA_UTF32CHARSET

namespace catool
{
	namespace main_toolbox
	{
		namespace data
		{
			template <typename T>
			class UTF32Charset {
			public:
				using CharType = T;

				static const char* getName() { return "UTF-32"; }

				static char32_t decode(const T*& begin, const T* end)
				{
					if (begin == end)
						return 0xFFFFFFFF;
					char32_t codepoint = *begin++;
					if (codepoint <= 0x10FFFF && (codepoint < 0xD800||codepoint>0xDFFF))
						return codepoint;
					else 
						return 0xFFFD;
				}
				static bool encode(T*& begin, T* end, char32_t codepoint)
				{
					if (begin == end)
						return false;
					if (codepoint <= 0x10FFFF &&(codepoint < 0xD800 || codepoint>0xDFFF))
						*begin++ = codepoint;
					else 
						*begin++ = 0xFFFD;
					return true;
				}

			};
		}
	}
}





#endif // !CATOOL_MAINTOOLBOX_DATA_UTF32CHARSET
