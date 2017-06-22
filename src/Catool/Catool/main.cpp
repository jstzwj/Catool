#include<iostream>
#include<cassert>
#include"MainToolbox.h"

int main()
{

	catool::vector<int> result = catool::main_toolbox::rat(3.1415926535897932384626433832795,1e-7);
	std::cout << result[0] << "	" << result[1] << std::endl;

	
	system("pause");
	return 0;
}