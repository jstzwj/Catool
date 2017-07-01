#include<iostream>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"
#include"MainToolbox\Mathematics\RandomNumber\Rand.h"
#include"MainToolbox\Data\Endian.h"
#include"MainToolbox\Data\StandardFile\Audio\Wav.h"
#include"MainToolbox\Data\StandardFile\Audio\Audio.h"


using namespace catool::main_toolbox;
using namespace catool::main_toolbox::mathematics;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::audio;
int main()
{
	//make a 10 seconds noise 
	{
		Array<float> audio_data = times(rand(44100*60, 2),1000);
		audiowrite("test.wav", audio_data);
	}
	
	//read music data to a Nx2 matrix from a wave file 
	{
		auto trace = audioread("ghyjn.wav");
		std::cout << std::get<0>(trace).size() << std::endl;
		std::cout << std::get<1>(trace) << std::endl;
	}

	system("pause");
	return 0;
}