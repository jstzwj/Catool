#include<iostream>
#include<cassert>
#include"Types.h"
#include"MainToolbox\Mathematics\ElementaryMath\Arithmetic.h"

using namespace catool;
using namespace catool::fundamentals;
int main()
{
	Array<int> abc{ 1,2,3,4,5 };
	Array<int> def{ 4,5,-4,0,6 };
	var_dump(main_toolbox::mathematics::plus(def, abc));

	system("pause");
	return 0;
}