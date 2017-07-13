#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H

#include<cmath>
#include<limits>
#include<utility>
#include"../../Types.h"
#include"Constants.h"
#include"../../Array.h"
namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			//using namespace ::ca;
			/*
			C = A + B adds arrays A and B and returns the result in C.
			C = plus(A,B) is an alternate way to execute A + B, but is rarely used.
			It enables operator overloading for classes.
			*/
			template<class T, class U>
			inline auto plus(const T& a, const U& b)-> decltype(a + b)
			{
				return a + b;
			}
			template<class T, class U>
			inline Array<T> plus(const Array<T>& a, const Array<U>& b)
			{
				if (a.get_dim() == b.get_dim())
				{
					Array<T> result(a);
					for (int i = 0; i < a.size(); ++i)
					{
						result[i] = a[i] + b[i];
					}
					return result;
				}
				else
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
			}
			template<class T, class U>
			inline Array<T> plus(const Array<T>& a, const U& b)
			{
				Array<T> result(a);
				for (auto &each : result)
				{
					each += b;
				}
				return result;
			}

			template<class T, class U>
			inline Array<T> plus(const U& a, const Array<T>& b)
			{
				Array<T> result(b);
				for (auto &each : result)
				{
					each += a;
				}
				return result;
			}

			/*
			C = +A returns array A and stores it in C.
			C = uplus(A) is an alternate way to execute +A, but is rarely used.
			It enables operator overloading for classes.
			*/
			inline double uplus(double a)
			{
				return a;
			}
			template<class T>
			inline Array<T> uplus(const Array<T>& a)
			{
				return a;
			}
			/*
			C = A - B subtracts array B from array A and returns the result in C.
			C = minus(A,B) is an alternate way to execute A - B, but is rarely used.
			It enables operator overloading for classes.
			*/
			template<class T, class U>
			inline auto minus(const T& a, const U& b)->decltype(a - b)
			{
				return a - b;
			}
			template<class T, class U>
			inline Array<T> minus(const Array<T>& a, const Array<U>& b)
			{
				if (a.get_dim() == b.get_dim())
				{
					Array<T> result(a);
					for (int i = 0; i < a.size(); ++i)
					{
						result[i] = a[i] - b[i];
					}
					return result;
				}
				else
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
			}
			template<class T, class U>
			inline Array<T> minus(const Array<T>& a, const U & b)
			{
				Array<T> result(a);
				for (auto &each : result)
				{
					each -= b;
				}
				return result;
			}
			template<class T, class U>
			inline Array<T> minus(const U & a, const Array<T>& b)
			{
				Array<T> result(b);
				for (auto &each : result)
				{
					each -= a;
				}
				return result;
			}
			/*
			C = -A negates the elements of A and stores the result in C.
			C = uminus(A) is an alternative way to execute -A, but is rarely used.
			It enables operator overloading for classes.
			*/
			inline double uminus(double a)
			{
				return -a;
			}
			template<class T>
			inline Array<T> uminus(const Array<T>& a)
			{
				Array<T> result(a);
				for (auto &each : result)
				{
					each = -each;
				}
				return result;
			}
			/*
			C = A.*B multiplies arrays A and B element by element and returns the result in C.
			C = times(A,B) is an alternate way to execute A.*B, but is rarely used.
			It enables operator overloading for classes.
			*/
			template<class T>
			inline Array<T> times(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result(a);
				if (a.get_dim() != b.get_dim())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = a[i] * b[i];
				}
				return result;
			}
			template<class T, class U>
			inline Array<T> times(const Array<T>& a, const U& b)
			{
				Array<T> result(a);
				for (int i = 0; i < result.size(); ++i)
				{
					result[i] *= b;
				}
				return result;
			}
			template<class T, class U>
			inline Array<T> times(const U& a, const Array<T>& b)
			{
				Array<T> result(b);
				for (unsigned int i = 0; i < result.size(); ++i)
				{
					result[i] *= a;
				}
				return result;
			}
			/*
			x = A./B divides each element of A by the corresponding element of B.
			*/
			template<class T>
			inline Array<T> rdivide(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result(a);
				if (a.get_dim() != b.get_dim())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = a[i] / b[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> rdivide(const Array<T>& a, const T & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = a[i] / b;
				}
				return result;
			}
			template<class T>
			inline Array<T> rdivide(const T &  a, const Array<T>& b)
			{
				Array<T> result(b);
				for (unsigned int i = 0; i < b.size(); ++i)
				{
					result[i] = a / b[i];
				}
				return result;
			}

			/*
			x = B.\A divides each element of A by the corresponding element of B.
			*/
			template<class T>
			inline Array<T> ldivide(const Array<T>& a, const Array<T>& b)
			{
				Array<T> result(a);
				if (a.get_dim() != b.get_dim())
					throw std::runtime_error("Matrix dimensions must agree.");
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = b[i] / a[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> ldivide(const Array<T>& a, const T & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = b / a[i];
				}
				return result;
			}
			template<class T>
			inline Array<T> ldivide(const T &  a, const Array<T>& b)
			{
				Array<T> result(b);
				for (unsigned int i = 0; i < b.size(); ++i)
				{
					result[i] = b[i] / a;
				}
				return result;
			}
			/*
			C = A.^B raises each element of A to the corresponding power in B.
			TODO:
			Calculate the roots of -1 to the 1/3 power.
			For negative base A and noninteger B, if abs(B) is less than 1, the power function returns the complex roots of A.
			Use the nthroot function to obtain the real roots.
			*/
			template<class T>
			inline Array<T> power(const Array<T>& a, const T & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = std::pow(a[i], b);
				}
				return result;
			}
			/*
			C = A*B is the matrix product of A and B.
			*/
			template<class T>
			Array<T> mtimes_normal(const Array<T>& a, const Array<T>& b)
			{
				if (a.dim_size() > 2 || b.dim_size() > 2)
				{
					throw std::runtime_error("Arguments must be 2 - D, or at least one argument must be scalar.Use TIMES(.*) for elementwise multiplication.");
				}
				if (a.get_dim_data(1) != b.get_dim_data(0))
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
				Array<T> result(a.get_dim_data(0), b.get_dim_data(1));
				//result.resize(a.rows()*b.cols());
				for (int i = 0; i < a.get_dim_data(0); ++i)
				{
					for (int j = 0; j < b.get_dim_data(1); ++j)
					{
						int des = j*a.get_dim_data(0) + i;
						for (int k = 0; k < b.get_dim_data(0); ++k)
						{
							result[des] += a[k*a.get_dim_data(0) + i] * b[j*b.get_dim_data(0) + k];
						}
					}
				}
				return result;
			}
			template<class T>
			Array<T> mtimes(const Array<T>& a, const Array<T>& b)
			{
				if (a.dim_size() > 2 || b.dim_size() > 2)
				{
					throw std::runtime_error("Arguments must be 2 - D, or at least one argument must be scalar.Use TIMES(.*) for elementwise multiplication.");
				}
				if (a.get_dim_data(1) != b.get_dim_data(0))
				{
					throw std::runtime_error("Matrix dimensions must agree.");
				}
				Array<T> result(a.get_dim_data(0), b.get_dim_data(1));
				//result.resize(a.rows()*b.cols());
				for (int i = 0; i < a.get_dim_data(0); ++i)//a row
				{
					for (int j = 0; j < a.get_dim_data(1); ++j)//a col
					{
						if (std::abs(a[j*a.get_dim_data(0) + i]) <= std::numeric_limits<T>::epsilon())
						{
							continue;
						}
						for (int k = 0; k < b.get_dim_data(1); ++k)//b col
						{
							result[k*a.get_dim_data(0) + i] += a[j*a.get_dim_data(0) + i] * b[k*b.get_dim_data(0) + j];
						}
					}
				}
				return result;
			}

			/*
			cumprod
			Cumulative product
			*/
			enum class CUMPROD_DIRECTION
			{
				DEFAULT,
				REVERSE
			};
			enum class CUMPROD_NANFLAG
			{
				OMITNAN,
				INCLUDENAN
			};

			inline void cumprod_impl(Array<double> & n,
				std::vector<int> &dims,
				int cur_dim,
				int cum_dim,
				CUMPROD_DIRECTION direction,
				CUMPROD_NANFLAG nanflag)
			{
				if (cur_dim < 0)
				{
					int sum_index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != cum_dim)
							sum_index += dims[i] * n.get_dim_acc(i);
					}
					double cum = 1;
					if (direction == CUMPROD_DIRECTION::DEFAULT)
					{
						for (int i = 0; i < n.get_dim_data(cum_dim); ++i)
						{
							if (n[i*n.get_dim_acc(cum_dim) + sum_index] != CATOOL_NAN ||
								nanflag != CUMPROD_NANFLAG::OMITNAN)
							{
								n[i*n.get_dim_acc(cum_dim) + sum_index] *= cum;
								cum = n[i*n.get_dim_acc(cum_dim) + sum_index];
							}
						}
					}
					else if (direction == CUMPROD_DIRECTION::REVERSE)
					{
						for (int i = n.get_dim_data(cum_dim) - 1; i >= 0; --i)
						{
							if (n[i*n.get_dim_acc(cum_dim) + sum_index] != CATOOL_NAN ||
								nanflag != CUMPROD_NANFLAG::OMITNAN)
							{
								n[i*n.get_dim_acc(cum_dim) + sum_index] *= cum;
								cum = n[i*n.get_dim_acc(cum_dim) + sum_index];
							}
						}
					}
					else
					{
						throw std::runtime_error("Unknown CUMPROD_DIRECTION");
					}
				}
				else
				{
					if (cur_dim != cum_dim)
					{
						int &i = dims[cur_dim];
						for (i = 0; i < n.get_dim_data(cur_dim); ++i)
						{
							cumprod_impl(n, dims, cur_dim - 1, cum_dim, direction, nanflag);
						}
					}
					else
					{
						cumprod_impl(n, dims, cur_dim - 1, cum_dim, direction, nanflag);
					}
				}
			}

			inline Array<double> cumprod(const Array<double> & n,
				CUMPROD_DIRECTION direction = CUMPROD_DIRECTION::DEFAULT,
				CUMPROD_NANFLAG nanflag = CUMPROD_NANFLAG::INCLUDENAN)
			{
				Array<double> result(n);
				std::vector<int> dims;
				dims.resize(n.dim_size());
				cumprod_impl(result, dims, n.dim_size() - 1, n.dim_size() - 1, direction, nanflag);
				return result;
			}
			/*
			B = cumprod(A, dim)
			*/
			inline Array<double> cumprod(const Array<double> & n, int dim,
				CUMPROD_DIRECTION direction = CUMPROD_DIRECTION::DEFAULT,
				CUMPROD_NANFLAG nanflag = CUMPROD_NANFLAG::INCLUDENAN)
			{
				Array<double> result(n);
				std::vector<int> dims;
				dims.resize(n.dim_size());
				cumprod_impl(result, dims, n.dim_size() - 1, dim, direction, nanflag);
				return result;
			}

			/*
			cumsum	Cumulative sum
			*/
			enum class CUMSUM_DIRECTION
			{
				DEFAULT,
				REVERSE
			};
			enum class CUMSUM_NANFLAG
			{
				OMITNAN,
				INCLUDENAN
			};
			template<class T>
			void cumsum_impl(Array<T> & n,
				std::vector<int> &dims,
				int cur_dim,
				int sum_dim,
				CUMSUM_DIRECTION direction,
				CUMSUM_NANFLAG nanflag)
			{
				if (cur_dim < 0)
				{
					int sum_index = 0;
					for (unsigned int i = 0; i < dims.size(); ++i)
					{
						if (i != sum_dim)
							sum_index += dims[i] * n.get_dim_acc(i);
					}
					T sum = 0;
					if (direction == CUMSUM_DIRECTION::DEFAULT)
					{
						for (int i = 0; i < n.get_dim_data(sum_dim); ++i)
						{
							if (n[i*n.get_dim_acc(sum_dim) + sum_index] != CATOOL_NAN ||
								nanflag != CUMSUM_NANFLAG::OMITNAN)
							{
								n[i*n.get_dim_acc(sum_dim) + sum_index] += sum;
								sum = n[i*n.get_dim_acc(sum_dim) + sum_index];
							}
						}
					}
					else if (direction == CUMSUM_DIRECTION::REVERSE)
					{
						for (int i = n.get_dim_data(sum_dim) - 1; i >= 0; --i)
						{
							if (n[i*n.get_dim_acc(sum_dim) + sum_index] != CATOOL_NAN ||
								nanflag != CUMSUM_NANFLAG::OMITNAN)
							{
								n[i*n.get_dim_acc(sum_dim) + sum_index] += sum;
								sum = n[i*n.get_dim_acc(sum_dim) + sum_index];
							}
						}
					}
					else
					{
						throw std::runtime_error("Unknown CUMPROD_DIRECTION");
					}
				}
				else
				{
					if (cur_dim != sum_dim)
					{
						int &i = dims[cur_dim];
						for (i = 0; i < n.get_dim_data(cur_dim); ++i)
						{
							cumsum_impl(n, dims, cur_dim - 1, sum_dim, direction, nanflag);
						}
					}
					else
					{
						cumsum_impl(n, dims, cur_dim - 1, sum_dim, direction, nanflag);
					}
				}
			}
			template<class T>
			Array<T> cumsum(const Array<T> & n,
				CUMSUM_DIRECTION direction = CUMSUM_DIRECTION::DEFAULT,
				CUMSUM_NANFLAG nanflag = CUMSUM_NANFLAG::INCLUDENAN)
			{
				Array<T> result(n);
				std::vector<int> dims;
				dims.resize(n.dim_size());
				cumsum_impl(result, dims, n.dim_size() - 1, n.dim_size() - 1, direction, nanflag);
				return result;
			}
			/*
			B = cumsum(A, dim)
			*/
			template<class T>
			Array<T> cumsum(const Array<T> & n, int dim,
				CUMSUM_DIRECTION direction = CUMSUM_DIRECTION::DEFAULT,
				CUMSUM_NANFLAG nanflag = CUMSUM_NANFLAG::INCLUDENAN)
			{
				Array<T> result(n);
				std::vector<int> dims;
				dims.resize(n.dim_size());
				cumsum_impl(result, dims, n.dim_size() - 1, dim, direction, nanflag);
				return result;
			}

			/*
			Y = fix(X) rounds each element of X to the nearest integer toward zero.
			For positive X, the behavior of fix is the same as floor.
			For negative X, the behavior of fix is the same as ceil.
			*/
			template<class T>
			inline T fix(T x)
			{
				if (x > 0.0)
					return std::floor(x);
				else
					return std::ceil(x);
			}
			template<class T>
			inline Array<T> fix(const Array<T> & t)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = fix(each);
				return result;
			}
			/*
			floor
			Round toward negative infinity
			*/
			template<class T>
			inline T floor(T x)
			{
				return std::floor(x);
			}
			template<class T>
			inline Array<T> floor(const Array<T> & t)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = std::floor(each);
				return result;
			}
			/*
			ceil
			Round toward positive infinity
			*/
			inline double ceil(double x)
			{
				return std::ceil(x);
			}
			template<class T>
			inline Array<T> ceil(const Array<T> & t)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = std::ceil(each);
				return result;
			}
			/*
			round
			*/
			inline double round(double x)
			{
				return std::round(x);
			}
			template<class T>
			inline Array<T> round(const Array<T> & t)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = std::round(each);
				return result;
			}
			/*
			rem
			*/
			template<class T, class U>
			inline double rem(T a, U b)
			{
				return std::remainder(a, b);
			}
			template<class T, class U>
			inline Array<T> rem(const Array<T> & a, U b)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = std::remainder(each, b);
				return result;
			}
			/*
			mod
			*/
			template<class T, class U>
			inline double mod(T a, U b)
			{
				return std::modf(a, b);
			}
			template<class T, class U>
			inline Array<T> mod(const Array<T> & a, U b)
			{
				Array<T> result(t);
				for (auto & each : result)
					each = std::modf(each, b);
				return result;
			}

			/*
			rat:
			R = rat(X) returns the rational fraction approximation of X to within the default tolerance, 1e-6*norm(X(:),1). The approximation is a character array containing the truncated continued fractional expansion.
			R = rat(X,tol) approximates X to within the tolerance, tol.
			[N,D] = rat(___) returns two arrays, N and D, such that N./D approximates X, using any of the above syntaxes.
			3 + 1/(7 + 1/(16 + 1/(-294)))
			*/

			inline std::pair<double,double> rat(double x, double tol)
			{
				int n, d;
				double float_part = x;
				int stack[32], top = 0;

				while (true)
				{
					stack[top] = (int)round(float_part);
					++top;
					assert((top < 32) && "rat stack full.");

					n = 1;
					d = 0;
					for (int i = top - 1; i >= 0; --i)
					{
						int tmp = n;
						n = n*stack[i] + d;
						d = tmp;
					}
					double tmp = x - (double)n / d;
					if (tmp<tol&& tmp>-tol)
						break;
					float_part = 1.0 / (float_part - stack[top - 1]);
				}
				if (n < 0 && d < 0)
					return{ -n,-d };
				else
					return{ n,d };
			}

			inline std::pair<double, double> rat(double x)
			{
				return rat(x, 1e-6);
			}

			template<class T>
			std::pair<Array<double>,Array<double>> rat(const Array<T> & x,double tol=1e-6)
			{
				Array<double> n(x.get_dim()),d(x.get_dim());
				for (int i = 0; i < x.size();++i)
				{
					auto each_rst = rat(x[i], tol);
					n[i] = each_rst.first;
					d[i]= each_rst.second;
				}
				return {n,d};
			}
			/*
			S = rats(X) returns a character vector containing the rational approximations to the elements of X using the default length of 13.
			rats returns asterisks for elements that cannot be printed in the allotted space, but which are not negligible compared to the other elements in X.
			S = rats(X,strlen) returns a character vector of length strlen. The rational approximation uses a tolerance that is inversely proportional to the length.
			*/
			inline string rats(double x)
			{
				std::pair<double,double> result = rat(x);
				return std::to_string(result.first) + "/" + std::to_string(result.second);
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
