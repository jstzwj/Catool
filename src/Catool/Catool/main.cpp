#include<iostream>
#include<cassert>
#include"Types.h"
#include"MainToolbox.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"

using namespace catool;
int main()
{
	vector<int> abc{ 1,2,3,4,5 };
	vector<int> def{ 4,5,-4,0,6 };
	var_dump(main_toolbox::mathematics::plus(def, abc));
	
	system("pause");
	return 0;
}