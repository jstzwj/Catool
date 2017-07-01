#include<iostream>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"
#include"MainToolbox\Mathematics\LinearAlgebra\LinearEquations.h"
#include"MainToolbox\Complex.h"
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
	Array<int> abc{ 1,2,3 };
	Array<double> rty{ 4.6,5.0,-4.1,0.0,6.9 };
	Array<int> def{ 1,2,3,4,5 };
	//var_dump(plus(def, abc));
	//var_dump(main_toolbox::mathematics::mtimes(main_toolbox::fundamentals::ones(5,1), main_toolbox::fundamentals::ones(1, 5)));
	//var_dump(rand(5,6,7,8));
	//var_dump(randn(5, 6));
	//var_dump(eye({3,6}));
	//var_dump(main_toolbox::fundamentals::zeros(5,6,2));
	//var_dump(main_toolbox::fundamentals::diag(main_toolbox::fundamentals::zeros(3, 4),0));
	//var_dump(main_toolbox::fundamentals::diag(main_toolbox::fundamentals::eye(3, 4),0));
	//var_dump(blkdiag(abc, def,abc));
	//var_dump(fix(times(rand(3, 4), 10)));
	//var_dump(inv(times(eye(4,4),4)));
	/*{
		Array<double> test{ 2,-1,0,-1,2,-1,0,-1,2 };
		test.resize(3, 3);
		var_dump(inv(test));
	}*/
	//var_dump(sign(Complex(1,2)));
	//var_dump(inv(ones(2, 2)));
	//var_dump(cumprod(times(ones(2,2,2),2),0));
	//var_dump(logspace(1,5,7));
	/*{
		var_dump(std::get<0>(meshgrid(abc, def)));
		var_dump(std::get<1>(meshgrid(abc, def)));
	}*/
	/*{
		var_dump(std::get<0>(meshgrid(abc, def, abc)));
		var_dump(std::get<1>(meshgrid(abc, def, abc)));
		var_dump(std::get<2>(meshgrid(abc, def, abc)));
	}*/
	//var_dump(transpose(abc).isMatrix());
	//mtimes(rand(1000, 1000), rand(1000, 1000));
	//mtimes(eye(10000, 1000), eye(1000, 10000));
	/*{
		var_dump(std::get<0>(lu(eye(2,2))));
		var_dump(std::get<1>(lu(eye(2, 2))));
	}*/
	//var_dump(cumsum(Array<double>({1,2,3,4,5})));

	//make noise
	/*{
		Array<float> audio_data = times(rand(44100*60, 2),1000);
		audiowrite("test.wav", audio_data);
	}*/
	
	//read music
	/*{
		auto trace = audioread("ghyjn.wav");
		std::cout << std::get<0>(trace).size() << std::endl;
		std::cout << std::get<1>(trace) << std::endl;
	}
*/
	system("pause");
	return 0;
}