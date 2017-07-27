#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H
#define CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H

#include <limits>
#include<tuple>
#include<algorithm>
#include<numeric>
#include<cmath>
#include"../../../Version.h"
#include"../../Array.h"

namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			double highPrecisionSqrt(double x)
			{
				if (x == 0) return 0;
				double result = x;
				double lastValue;
				do 
				{
					lastValue = result;
					result = (result+ x/ result)*0.5;
				} while (std::abs(result - lastValue) > 1e-18);
				return result;
			}
			/*
			norm	Vector and matrix norms
			*/
			template<class T>
			T norm(const Array<T> &a)
			{
				T sum=T();
				for (const auto& each:a)
				{
					sum += each*each;
				}
				return std::sqrt(sum);
			}
			template<class T>
			T norm(const Array<T> &m,int dim)
			{
				Array<T> result;
				std::vector<int> dims = m.get_dim();
				dims[dim] = 1;
				result.resize(dims);

				m.dimloop(dim, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
				{
					int rst_index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != dim)
							rst_index += dims[i] * result.get_dim_acc(i);
					}
					int index = m.composeIndex(dims);
					int acc = m.get_dim_acc(dim);
					int len = m.get_dim_data(dim);

					T sum = T();

					for (int i=0;i<len;++i)
					{
						T tmp = m[index+acc*i];
						sum += tmp*tmp;
					}
					result[rst_index] = std::sqrt(sum);
				});
				return result;
			}
			/*
			hess
			Hessenberg form of matrix
			*/
			template<class T>
			Array<T> hess(const Array<T> & m)
			{
				Array<T> rst(m);
				int d0 = m.get_dim_data(0), d1 = m.get_dim_data(1);
				int cur_row = d0-1;
				for (int i = d1-1; i >= 0;--i)//col
				{
					for (int j=i-2;j>=0;--j)
					{
						double scale = rst[d0*j+ cur_row] / rst[d0*i+ cur_row];
						rst.addCol(-scale, i, j);
					}
					--cur_row;
				}
				return rst;
			}
			/*
			qr
			Orthogonal-triangular decomposition
			*/
			template<class T>
			T norm2(const Array<T> & m)
			{
				T sum = T();
				for (const auto& each : m)
				{
					sum += each*each;
				};
				return sum;
			}
			template<class T> 
			std::tuple<Array<T>, Array<T>> qr(const Array<T> &m)
			{
				int d0 = m.get_dim_data(0);
				Array<T> r(m);
				Array<T> q=eye<T>(d0,d0);
				//std::vector<Array<T>> h_vec;
				Array<T> eye_mat=eye<T>(d0, d0);
				Array<T> alpha;
				
				for (int i=0;i<d0;++i)
				{
					std::cout << i << " ";
					alpha.resize(d0);
					//copy alpha
					for (int j=0;j<i;++j)
					{
						alpha[j] = 0;
					}
					for (int j=i;j<d0;++j)
					{
						alpha[j] = r[i*d0+j];
					}
					T a = norm(alpha);

					Array<T> e;
					e.resize(d0);
					e[i] = 1;

					Array<T> tmp = minus(alpha, times(a, e));
					Array<T> omega;
					if (std::abs(norm2(tmp)) <= std::numeric_limits<T>::epsilon())
						omega = tmp;
					else
						omega = rdivide(tmp, norm(tmp));
					Array<T> H = minus(eye_mat, times(2, mtimes(omega, transpose(omega))));
					q = mtimes(q, H);
					r = mtimes(H, r);
				}
				return {q,r};
			}
			/*
			eig
			*/
			template<class T>
			std::tuple<Array<T>, Array<T>> eig(const Array<T>& m)
			{
				Array<T> tmp(m);
				
				T last;
				do
				{
					last = tmp[0];
					std::tuple<Array<T>, Array<T>> qr_rst = qr(tmp);
					tmp = mtimes(std::get<1>(qr_rst),std::get<0>(qr_rst));
				}while (std::abs(last - tmp[0]) > std::numeric_limits<T>::epsilon());

				return{tmp,tmp};
			}
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
								m.swapRow(i, k);
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
					return m;
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
				Array<T> result=eye<T>();
				Array<T> tmp(A);
				int time = n;
				while (time!=0)
				{
					if (time % 2 == 1) result = result*tmp;
					tmp = mtimes(tmp, tmp);
					time /= 2;
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
			/*
			planerot
			Givens plane rotation
			*/
			template<class T>
			std::tuple<Array<T>, Array<T>> planerot(const Array<T> & m)
			{

			}
			/*
			dot
			*/
			template<class T>
			T dot(const Array<T> &a, const Array<T> &b, int dim = 0)
			{
				if (a.get_dim()!=b.get_dim())
				{
					throw std::runtime_error("Error using dot A and B must be same size.");
				}

				Array<T> result;
				std::vector<int> dims = m.get_dim();
				dims[dim] = 1;
				result.resize(dims);

				a.dimloop(dim, [&result,&a,&b, &dim](const Array<T>& m, const std::vector<int>&dims)
				{
					int rst_index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != dim)
							rst_index += dims[i] * result.get_dim_acc(i);
					}
					int index = m.composeIndex(dims);
					int acc = m.get_dim_acc(dim);
					int len = m.get_dim_data(dim);
					for (int i=0;i<len;++i)
					{
						result[rst_index] += a[index+i*acc]* b[index + i*acc];
					}
				});
				return result;
			}
			/*
			cross
			*/
			template<class T>
			T cross(const Array<T> &a, const Array<T> &b, int dim = 0)
			{
				if (a.get_dim_data(dim) !=3|| b.get_dim_data(dim)!=3)
				{
					throw std::runtime_error("Error using cross A and B must be of length 3 in the dimension in which the cross product is taken.");
				}
				Array<T> result;
				std::vector<int> dims = m.get_dim();
				dims[dim] = 3;
				result.resize(dims);

				a.dimloop(dim, [&result, &a, &b, &dim](const Array<T>& m, const std::vector<int>&dims)
				{
					int rst_index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != dim)
							rst_index += dims[i] * result.get_dim_acc(i);
					}
					int index = m.composeIndex(dims);
					int acc = m.get_dim_acc(dim);
					int len = m.get_dim_data(dim);
					
					result[rst_index + 0 * result.get_dim_data(dim)] = 
						-a[index + 2 * acc] * b[index + 1 * acc]+ a[index + 1 * acc] * b[index + 2 * acc];
					result[rst_index + 1 * result.get_dim_data(dim)] = 
						-a[index + 2 * acc] * b[index + 0 * acc] + a[index + 0 * acc] * b[index + 2 * acc];
					result[rst_index + 2 * result.get_dim_data(dim)] = 
						-a[index + 1 * acc] * b[index + 0 * acc] + a[index + 0 * acc] * b[index + 1 * acc];
				});
				return result;
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATICS_LINEARALGEBRA_LINEAREQUATIONS_H
