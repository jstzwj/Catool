#include<iostream>
#include<ctime>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Data\StandardFile\Audio\Wav.h"
#include"MainToolbox\Data\StandardFile\Audio\Audio.h"


using namespace catool::main_toolbox;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::audio;
inline void TestAudioRead()
{
	//read music
	std::string path;
	std::cout << "Please input the path of audio file." << std::endl;
	std::cin >> path;
	auto trace = audioread(path.c_str());
	disp(std::get<0>(trace));
	disp(std::get<1>(trace));
	
	system("pause");
}