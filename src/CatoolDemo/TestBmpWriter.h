#pragma once
#include<iostream>
#include<ctime>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Data\StandardFile\Images\Image.h"
#include"MainToolbox\Mathematics\RandomNumber\Rand.h"

using namespace catool::main_toolbox;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::images;
using namespace catool::main_toolbox::mathematics;

inline void TestBmpWrite()
{
	//write a noise bmp
	std::string path;
	std::cout << "Please input the path of bmp file." << std::endl;
	std::cin >> path;
	imwrite(rand<double>(400, 400), path.c_str());

}