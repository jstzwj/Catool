#pragma once
#ifndef CATOOL_MAINTOOLBOX_GRAPHICS_GNUPLOTS
#define CATOOL_MAINTOOLBOX_GRAPHICS_GNUPLOTS

#include <cstdio>
#include<cstring>
namespace catool
{
	namespace main_toolbox
	{
		namespace graphics
		{
			int callplot(const char * cmd)
			{
				std::FILE* gp;

#ifdef WIN32
				gp = _popen("gnuplot -persist", "w");
#elif _WIN32
				gp = _popen("gnuplot -persist", "w");
#elif _WIN64
				gp = _popen("gnuplot -persist", "w");
#else
				gp = popen("gnuplot -persist", "w");
#endif

				if (gp == NULL)
					return -1;
				std::fprintf(gp, "%s/n",cmd);
				std::fflush(gp);
				//fprintf(gp, cmd);
				/*fprintf(gp, "set isosample 100/n");
				fprintf(gp, "min=-1/n");
				fprintf(gp, "max=1/n");
				fprintf(gp, "pi=3.141592/n");
				fprintf(gp, "set hidden3d/n");
				fprintf(gp, "set pm3d/n");
				fprintf(gp, "set contour/n");
				fprintf(gp, "splot [min:max] [min:max] x*x+2*y*y-0.3*cos(3*pi*x)-0.4*cos(4*pi*y)+0.7/n");
				fprintf(gp, "pause -1/n");*/

#ifdef WIN32
				_pclose(gp);
#elif _WIN32
				_pclose(gp);
#elif _WIN64
				_pclose(gp);
#else
				pclose(gp);
#endif
				return 0;
			}
		}
	}
}
#endif // !CATOOL_MAINTOOLBOX_GRAPHICS_GNUPLOTS