#include<iostream>
#include<ctime>
#include<cassert>
#include"MainToolbox\Types.h"
#include"MainToolbox\Array.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"
#include"MainToolbox\Mathematics\LinearAlgebra\LinearEquations.h"
#include"MainToolbox\Mathematics\ElementaryMath\ExponentsLogarithms.h"
#include"MainToolbox\Complex.h"
#include"MainToolbox\Mathematics\RandomNumber\Rand.h"
#include"MainToolbox\Data\Endian.h"
#include"MainToolbox\Data\StandardFile\Audio\Wav.h"
#include"MainToolbox\Data\StandardFile\Audio\Audio.h"
#include"MainToolbox\Graphics\Gnuplot.h"
#include"MainToolbox\Data\DescriptiveStatistics.h"

using namespace catool::main_toolbox;
using namespace catool::main_toolbox::mathematics;
using namespace catool::main_toolbox::data;
using namespace catool::main_toolbox::data::stream;
using namespace catool::main_toolbox::data::audio;
using namespace catool::main_toolbox::graphics;
int main()
{
	Array<int> abc{ 1,2,3,6,8 };
	Array<double> rty{ 4.6,5.0,-4.1,0.0,6.9 };
	Array<int> def{ 1,2,3,4,5 };
	//var_dump(plus(def, abc));
	//var_dump(mtimes(ones(5,1), ones(1, 5)));
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
}*/
//read and write
/*try {
	auto trace = audioread("ghyjn.wav");
	std::cout << std::get<0>(trace).size() << std::endl;
	std::cout << std::get<1>(trace) << std::endl;
	auto rand_matrix = rand(std::get<0>(trace).get_dim_data(0), 2);
	auto scaled_rand = times(rand_matrix, 100);
	auto result = plus(scaled_rand, std::get<0>(trace));
	audiowrite("test.wav", result);
}
catch (std::exception e)
{
	std::cout << e.what();
}*/

//{
//	Array<double> test{ 1,4,7,2,5,8,3,6,9 };
//	Array<double> test2{ 0,-3,6 };
//	test.resize(3, 3);
//	test2.resize(3, 1);

//	//var_dump(mldivide(test,test2));
//	var_dump(inv(test));
//}

//rot90
/*{
	Array<double> test{ 1,4,7,2,5,8,3,6,9 };
	test.resize(3, 3);
	var_dump(rot90(test, 0));
	var_dump(rot90(test, 1));
	var_dump(rot90(test, 2));
	var_dump(rot90(test, 3));
}*/
//callplot("plot [-3.14:3.14] sin(x)\n");
//rat
/*{
	auto nd = rat(rty, 1e-6);
	var_dump(nd.first);
	var_dump(nd.second);
}*/
//rank, trace and pinv

//{
	//var_dump(pinv(def));
	//Array<double> tst{ 1.0,1.0,1.0,2.0,2.0,2,3,3,3,4,4,5 };
	//tst.resize(3,4);
	//var_dump(trace(tst));
	//var_dump(rank(tst));
//}

//disp
//disp(def);

//nextpow2
//disp(nextpow2(1023));
//disp(def);
//mtimes(ones<int>(1000, 1000), ones<int>(1000, 1000));
//mtimes(zeros<double>(1000, 1000), zeros<double>(1000, 1000));
//var_dump(pinv(ones<double>(4,4)));
//subArray
//{
//	std::vector<Range> ran = def.getFullLoop();
//	ran[1] = Range(0, 2);
//	var_dump(def.subArray(ran));
//}
//cat
//var_dump(cat(0,abc, def,abc));


//min
//{
//	Array<double> tst{ 1.0,1.0,1.0,2.0,2.0,2,3,3,3,4,4,5 };
//	tst.resize(3,4);
//	var_dump(max(tst,1));
//}


//sum
//{
//		Array<double> tst{ 1.0,1.0,1.0,2.0,2.0,2,3,3,3,4,4,5 };
//		tst.resize(3,4);
//		var_dump(prod(tst,1));
//}
//movsum
//{
//			Array<double> tst{ 1.0,1.0,1.0,2.0,2.0,2,3,3,3,4,4,5 };
//			tst.resize(3,4);
//			var_dump(movsum(tst,1,1,1));
//}
//diff
//{
//	Array<double> tst{ 1.0,1.0,1.0,2.0,2.0,2,3,3,3,4,4,5 };
//	tst.resize(3, 4);
//	var_dump(diff(tst, 1, 0));
//}
//sort
//{
//		Array<int> tst{ 1,5,7,2,4,5,7,3,9,0,4,2 };
//		tst.resize(3, 4);
//		var_dump(tst);
//		var_dump(sort(tst, 1));
//}

//var_dump(shiftdim(ones(2,3,4),-2));
//var_dump(mean(abc,1));

clock_t strt = clock();
mtimes(ones<float>(1000, 1000), ones<float>(1000, 1000));
//var_dump(mtimes(transpose(abc),def));
clock_t nd = clock();
std::cout << nd - strt << std::endl;
	system("pause");
	return 0;
}