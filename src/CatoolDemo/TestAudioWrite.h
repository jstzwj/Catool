#include<iostream>
#include<ctime>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"
#include"MainToolbox\Mathematics\RandomNumber\Rand.h"
#include"MainToolbox\Data\StandardFile\Audio\Wav.h"
#include"MainToolbox\Data\StandardFile\Audio\Audio.h"

using namespace catool::main_toolbox;
using namespace catool::main_toolbox::mathematics;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::audio;
inline void TestAudioWrite()
{
	//read music
	std::string path;
	std::cout << "Please input the path of audio file to create a noise audio." << std::endl;
	std::cin >> path;
	Array<float> audio_data = times(rand<float>(44100 * 60, 2), 1000);
	audiowrite(path.c_str(), audio_data);

	system("pause");
}