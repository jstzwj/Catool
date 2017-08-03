#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_COORDINATSYSTEM_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_COORDINATSYSTEM_H


#include<tuple>
#include<stdexcept>
#include<cmath>

#include"../../Array.h"

namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			/*cart2pol	Transform Cartesian coordinates to polar or cylindrical*/
			template<class T>
			std::tuple<T, T> cart2pol(T x, T y)
			{
				T theta, rho;
				theta = std::atan2(y, x);
				rho = std::sqrt(x * x+ y * y);
				return{ theta,rho };
			}
			template<class T>
			std::tuple<T, T, T > cart2pol(T x, T y,T z)
			{
				T theta, rho;
				theta = std::atan2(y, x);
				rho = std::sqrt(x * x + y * y);
				return{ theta,rho,z};
			}
			template<class T>
			std::tuple<Array<T>,Array<T>> cart2pol(const Array<T>& x, const Array<T>& y)
			{
				Array<T> theta, rho;
				if (x.size()!=y.size())
				{
					throw std::runtime_error("error: cart2pol: X, Y must be numeric arrays of the same size, or scalar");
				}
				theta.resize(x.size());
				rho.resize(x.size());
				for (int i = 0; i < x.size();++i)
				{
					theta[i] = std::atan2(y[i],x[i]);
					rho[i] = std::sqrt(x[i]* x[i] + y[i]* y[i]);
				}
				return{ theta,rho };
			}
			template<class T>
			std::tuple<Array<T>, Array<T>, Array<T>> cart2pol(const Array<T>& x, const Array<T>& y,const Array<T> & z)
			{
				Array<T> theta, rho;
				if (x.size() != y.size())
				{
					throw std::runtime_error("error: cart2pol: X, Y must be numeric arrays of the same size, or scalar");
				}
				theta.resize(x.size());
				rho.resize(x.size());
				for (int i = 0; i < x.size(); ++i)
				{
					theta[i] = std::atan2(y[i], x[i]);
					rho[i] = std::sqrt(x[i] * x[i] + y[i] * y[i]);
				}
				return{ theta,rho,z };
			}
			/*cart2sph	Transform Cartesian coordinates to spherical*/

			/*pol2cart	Transform polar or cylindrical coordinates to Cartesian*/
			template<class T>
			std::tuple<T, T> pol2cart(T theta, T rho)
			{
				T x, y;
				x = rho*std::cos(theta);
				y = rho*std::sin(theta);
				return{ x,y };
			}
			template<class T>
			std::tuple<T, T,T> pol2cart(T theta, T rho,T z)
			{
				T x, y;
				x = rho*std::cos(theta);
				y = rho*std::sin(theta);
				return{ x,y,z };
			}
			template<class T>
			std::tuple<Array<T>, Array<T>> pol2cart(const Array<T>& theta, const Array<T>& rho)
			{
				Array<T> x, y;
				if (theta.size() != rho.size())
				{
					throw std::runtime_error("error: pol2cart: theta, rho must be numeric arrays of the same size, or scalar");
				}
				x.resize(theta.size());
				y.resize(theta.size());
				for (int i = 0; i < theta.size(); ++i)
				{
					x[i] = rho[i]*std::cos(theta[i]);
					y[i] = rho[i]*std::sin(theta[i]);
				}
				return{ x,y };
			}
			template<class T>
			std::tuple<Array<T>, Array<T>, Array<T>> pol2cart(const Array<T>& theta, const Array<T>& rho, const Array<T>& z)
			{
				Array<T> x, y;
				if (theta.size() != rho.size())
				{
					throw std::runtime_error("error: pol2cart: theta, rho must be numeric arrays of the same size, or scalar");
				}
				x.resize(theta.size());
				y.resize(theta.size());
				for (int i = 0; i < theta.size(); ++i)
				{
					x[i] = rho[i] * std::cos(theta[i]);
					y[i] = rho[i] * std::sin(theta[i]);
				}
				return{ x,y,z};
			}
			/*sph2cart	Transform spherical coordinates to Cartesian*/

		}
	}
	
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_COORDINATSYSTEM_H
