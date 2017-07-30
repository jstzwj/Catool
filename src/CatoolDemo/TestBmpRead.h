#pragma once
#include<iostream>
#include<ctime>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Data\StandardFile\Images\Image.h"

using namespace catool::main_toolbox;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::images;

inline void TestBmpRead()
{
	//read bmp
	std::string path;
	std::cout << "Please input the path of bmp file." << std::endl;
	std::cin >> path;
	auto img = imread(path.c_str());
	disp(img);
	
}