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
int main()
{
	//rot90
	{
		Array<double> test{ 1,4,7,2,5,8,3,6,9 };
		test.resize(3, 3);
		var_dump(rot90(test, 0));
		var_dump(rot90(test, 1));
		var_dump(rot90(test, 2));
		var_dump(rot90(test, 3));
	}

	system("pause");
	return 0;
}