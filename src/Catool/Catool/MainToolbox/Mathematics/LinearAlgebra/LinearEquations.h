#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H
#define CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H

#include <limits>
#include<tuple>
#include<cmath>
#include"../../../Version.h"
#include"../../Array.h"

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
					{
#ifdef CATOOL_ENABLE_WARNING
						throw "warning: matrix singular to machine precision.";
#endif // CATOOL_ENABLE_WARNING
					}

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

			inline void swapRow(Array<double> &m, int a, int b)
			{
				if (m.dim_size() > 2)
					throw std::runtime_error("error: swapRow not defined for N-D objects");
				for (int i = 0; i < m.get_dim_data(1); ++i)
				{
					std::swap(m[i*m.get_dim_data(0) + a], m[i*m.get_dim_data(0) + b]);
				}
			}

			inline int rank(const Array<double> &a)
			{
				if (a.dim_size() > 2)
					throw std::runtime_error("error: rank not defined for N-D objects");
				Array<double> m(a);
				int echelon_line = 0;
				int rank_rst = 0;
				//遍历行
				for (int i = 0; i < m.get_dim_data(0); ++i, ++echelon_line)
				{
					//已经形成阶梯型
					if (echelon_line >= m.get_dim_data(1))	break;
					//当前行阶梯线上为0
					while (std::abs(m[echelon_line*m.get_dim_data(0) + i]) < std::numeric_limits<double>::epsilon())
					{
						//遍历当前行下面所有行的阶梯线，找个不为零的行
						int k;
						for (k = i + 1; k < m.get_dim_data(0); ++k)
						{
							if (std::abs(m[echelon_line*m.get_dim_data(0) + k]) >= std::numeric_limits<double>::epsilon())
							{
								swapRow(m, i, k);
								break;
							}
						}
						//当前阶梯线所在列全是0......
						if (k == m.get_dim_data(0))
						{
							++echelon_line;
							//已经形成阶梯型
							if (echelon_line >= m.get_dim_data(1))	return rank_rst;
						}
					}
					++rank_rst;
					//目标行
					for (int j = i + 1; j < m.get_dim_data(0); ++j)
					{
						if (std::abs(m[echelon_line*m.get_dim_data(0) + j]) < std::numeric_limits<double>::epsilon())
							continue;
						double scale = m[echelon_line*m.get_dim_data(0) + j] / m[echelon_line*m.get_dim_data(0) + i];
						//两行相减
						for (int k = 0; k < m.get_dim_data(1); ++k)
						{
							m[k*m.get_dim_data(0) + j] += -scale*m[k*m.get_dim_data(0) + i];
						}
					}
				}
				return rank_rst;
			}

			/*
			pinv
			Moore - Penrose pseudoinverse of matrix
			*/
			inline Array<double> pinv(Array<double> m)
			{
				//满秩分解法 计算
				//计算矩阵秩
				int rnk = rank(m);
				Array<double> tran_m = transpose(m);
				if (rnk == m.get_dim_data(0))
				{
					//行满秩
					return mtimes(tran_m, inv(mtimes(m, tran_m)));
				}
				else if(rnk == m.get_dim_data(1))
				{
					//列满秩
					return mtimes(inv(mtimes(tran_m, m)), tran_m);
				}
				else
				{
					//不是行满秩也不是列满秩
					//化为hermite标准型
					//满秩分解
				}
			}

			/*
			mldivide, \
			Solve systems of linear equations Ax = B for x
			*/
			template<class T>
			Array<T> mldivide(const Array<T>& A, const Array<T>& B)
			{
				return mtimes(pinv(A), B);
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
				l = eye<double>(u.get_dim_data(0), u.get_dim_data(0));
				for (int i = 0; i < u.get_dim_data(0); ++i)
				{
					for (int j = i + 1; j < u.get_dim_data(0); ++j)
					{
						double scale = u[i*u.get_dim_data(0) + j] / u[i*u.get_dim_data(0) + i];
						for (int k = 0; k < u.get_dim_data(1); ++k)
						{
							u[k*u.get_dim_data(0) + j] += u[k*u.get_dim_data(0) + i] * (-scale);
							l[i*u.get_dim_data(0) + j] = scale;
						}
					}
				}
				return std::make_tuple(l, u);
			}
			/*
			mpower, ^
			Matrix power
			*/
			template<class T>
			Array<T> mpower(const Array<T>& A, int n)
			{
				Array<T> result(A);
				int time = 1;
				while (time * 2 < n)
				{
					result = mtimes(result, result);
					time *= 2;
				}
				while (time < n)
				{
					result = mtimes(result, A);
					time++;
				}
				return result;
			}
			/*
			isdiag
			Determine if matrix is diagonal
			*/
			template<class T>
			bool isdiag(const Array<T>& a)
			{
				if (a.dim_size() > 2)
				{
					throw std::runtime_error("Matrix must be 2-dimensional");
				}

				int m = a.get_dim_data(0);
				int n = a.get_dim_data(1);
				int min = m > n ? n : m;
				T result = T();
				for (int i = 0; i < a.get_dim_data(0); ++i)
				{
					for (int j = 0; j < a.get_dim_data(1); ++j)
					{
						if (i != j&&std::abs(a[j*a.get_dim_data(0) + i]) >= std::numeric_limits<double>::epsilon())
						{
							return false;
						}
					}
				}
				return true;
			}

			/*
			trace
			Sum of diagonal elements
			*/
			template<class T>
			T trace(const Array<T>& a)
			{
				if (a.dim_size() > 2)
				{
					throw std::runtime_error("Matrix must be 2-dimensional");
				}

				int m = a.get_dim_data(0);
				int n = a.get_dim_data(1);
				int min = m > n ? n : m;
				T result = T();
				for (int i = 0; i < min; ++i)
				{
					result += a[i*m + i];
				}
				return result;
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H
