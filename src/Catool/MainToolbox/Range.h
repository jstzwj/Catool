#pragma once
#ifndef CATOOL_MAINTOOLBOX_RANGE
#define CATOOL_MAINTOOLBOX_RANGE
#include<initializer_list>
namespace catool
{
	namespace main_toolbox
	{
		class Range
		{
		public:
			int begin;
			int end;
			int interval;
		public:
			Range(int val_)
				:begin(val_), end(val_ + 1), interval(1) {}
			Range(int begin_, int end_, int interval_ = 1)
				:begin(begin_), end(end_), interval(interval_) {}
		};
	}
}

#endif // !CATOOL_MAINTOOLBOX_RANGE