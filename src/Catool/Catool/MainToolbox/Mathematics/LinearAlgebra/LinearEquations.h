#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H
#define CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H

#include <limits>
#include<tuple>
#include<cmath>
#include"../ElementaryMath/Array.h"

namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			/*
			Y = inv(X)
			Matrix inverse
			use Gaussian elimination method
			*/
			Array<double> inv(Array<double> m)
			{
				//inverse: A must be a square matrix
				if (!(m.dim_size() == 2 && m.get_dim_data(0) == m.get_dim_data(1)))
				{
					throw std::runtime_error("inverse: A must be a square matrix");
				}
				int m_sz = m.get_dim_data(0);
				Array<double> result = eye<double>(m_sz, m_sz);
				for (int i = 0; i < m_sz; ++i)
				{
					double scale = m[i*m_sz + i];
					//warning
					if (std::abs(scale) < std::numeric_limits<double>::epsilon())
						throw "warning: matrix singular to machine precision.";
					//Unitized row
					for (int j = 0; j < m_sz; ++j)
					{
						m[j*m_sz + i] /= scale;
						result[j*m_sz + i] /= scale;
					}
					//Elementary row transformation
					for (int j = 0; j < m_sz; ++j)
					{
						if (j != i)
						{
							double scale_each = m[i*m_sz + j] / m[i*m_sz + i];
							for (int k = 0; k < m_sz; ++k)
							{
								m[k*m_sz + j] = m[k*m_sz + j] - scale_each*m[k*m_sz + i];
								result[k*m_sz + j] = result[k*m_sz + j] - scale_each*result[k*m_sz + i];
							}
						}
					}
				}
				return result;
			}
			/*
			lu
			LU matrix factorization
			*/
			inline std::tuple<Array<double>, Array<double>> lu(const Array<double> &m)
			{
				if (m.dim_size() > 2)
					throw std::runtime_error("error: lu not defined for N-D objects");
				Array<double> l, u(m);
				l = eye(u.get_dim_data(0), u.get_dim_data(0));
				for (int i = 0; i < u.get_dim_data(0);++i)
				{
					for (int j = i+1; j < u.get_dim_data(0);++j)
					{
						double scale = u[i*u.get_dim_data(0) + j] / u[i*u.get_dim_data(0) + i];
						for (int k = 0; k < u.get_dim_data(1);++k)
						{
							u[k*u.get_dim_data(0) + j] += u[k*u.get_dim_data(0) + i] * (-scale);
							l[i*u.get_dim_data(0) + j] = scale;
						}
					}
				}
				return std::make_tuple(l,u);
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H
