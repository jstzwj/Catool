#include<iostream>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Mathematics\ElementaryMath\Array.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"
#include"MainToolbox\Mathematics\LinearAlgebra\LinearEquations.h"
using namespace catool::main_toolbox;
using namespace catool::main_toolbox::mathematics;
int main()
{
	Array<int> abc{ 1,2,3,4,5 };
	Array<double> rty{ 4.6,5.0,-4.1,0.0,6.9 };
	Array<int> def{ 4,5,-4,0,6 };
	//var_dump(main_toolbox::mathematics::plus(def, abc));
	//var_dump(main_toolbox::mathematics::mtimes(main_toolbox::fundamentals::ones(5,1), main_toolbox::fundamentals::ones(1, 5)));
	//var_dump(main_toolbox::fundamentals::rand(5,6,7,8));
	//var_dump(main_toolbox::fundamentals::eye({3,6}));
	//var_dump(main_toolbox::fundamentals::zeros(5,6,2));
	//var_dump(main_toolbox::fundamentals::diag(main_toolbox::fundamentals::zeros(3, 4),0));
	//var_dump(main_toolbox::fundamentals::diag(main_toolbox::fundamentals::eye(3, 4),0));
	//var_dump(main_toolbox::fundamentals::blkdiag(abc, def,abc));
	//var_dump(fix(times(rand(3, 4), 10)));
	//var_dump(inv(times(eye(4,4),4)));
	Array<double> test{2,-1,0,-1,2,-1,0,-1,2};
	test.resize(3,3);
	var_dump(inv(test));
	system("pause");
	return 0;
}