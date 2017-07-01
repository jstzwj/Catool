#include<iostream>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"
#include"MainToolbox\Mathematics\LinearAlgebra\LinearEquations.h"
#include"MainToolbox\Mathematics\RandomNumber\Rand.h"

using namespace catool::main_toolbox;
using namespace catool::main_toolbox::mathematics;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::audio;
int main()
{
	mtimes(rand(1000, 1000), rand(1000, 1000));
	//mtimes(eye(10000, 1000), eye(1000, 10000));
	system("pause");
	return 0;
}