#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
#define CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H

#include<cmath>
#include<limits>
#include<utility>
#include"../../../Version.h"
#include"../../Types.h"
#include"Constants.h"
#include"../../Array.h"

#ifdef CATOOL_ENABLE_SSE
//#include <emmintrin.h>
#include <intrin.h>
#endif // CATOOL_ENABLE_SSE

#define KC 64
#define MC 64

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
			template<class T, class U>
			inline Array<T> rdivide(const Array<T>& a, const Array<U>& b)
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
			template<class T, class U>
			inline Array<T> rdivide(const Array<T>& a, const U & b)
			{
				Array<T> result(a);
				for (int i = 0; i < a.size(); ++i)
				{
					result[i] = a[i] / b;
				}
				return result;
			}
			template<class T, class U>
			inline Array<T> rdivide(const T &  a, const Array<U>& b)
			{
				Array<T> result(b);
				for (int i = 0; i < b.size(); ++i)
				{
					result[i] = a / b[i];
				}
				return result;
			}

			/*
			x = B.\A divides each element of A by the corresponding element of B.
			*/
			template<class T, class U>
			inline Array<T> ldivide(const Array<T>& a, const Array<U>& b)
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
			template<class T, class U>
			inline Array<T> ldivide(const Array<T>& a, const U & b)
			{
				Array<T> result(a);
				for (unsigned int i = 0; i < a.size(); ++i)
				{
					result[i] = b / a[i];
				}
				return result;
			}
			template<class T, class U>
			inline Array<T> ldivide(const T &  a, const Array<U>& b)
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
			Array<T> mtimes_slow(const Array<T>& a, const Array<T>& b)
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
			Array<T> mtimes_impl_small(const Array<T>& a, const Array<T>& b)
			{
				int a_d0 = a.get_dim_data(0), a_d1 = a.get_dim_data(1);
				int b_d0 = b.get_dim_data(0), b_d1 = b.get_dim_data(1);
				Array<T> result(a_d0, b_d1);
				for (int i = 0; i < b_d1; ++i)//b col
				{
					const T * p_b = &b[i*b_d0];
					for (int j = 0; j < b_d0; ++j)//b row
					{
						T * p_des = &result[i*a_d0];
						const T* p_a = &a[j*a_d0];
						T b_tmp = *p_b++;

						for (int k = 0; k < a_d0; ++k)//a row
							(*p_des++) += (*p_a++) * b_tmp;
					}
				}
				return result;
			}
#if defined CATOOL_ENABLE_AVX
			Array<double> mtimes_impl_small(const Array<double>& a, const Array<double>& b)
			{
				int a_d0 = a.get_dim_data(0), a_d1 = a.get_dim_data(1);
				int b_d0 = b.get_dim_data(0), b_d1 = b.get_dim_data(1);
				Array<double> result(a_d0, b_d1);
				for (int i = 0; i < b_d1; ++i)//b col
				{
					const double * p_b = &b[i*b_d0];
					for (int j = 0; j < b_d0; ++j)//b row
					{
						double * p_des = &result[i*a_d0];
						const double* p_a = &a[j*a_d0];
						double b_tmp = *p_b++;

						__m256d b_mm = _mm256_set1_pd(b_tmp);

						int k = 0;
						for (; k < a_d0 - 1; k += 4)//a row
						{
							__m256d a_mm = _mm256_load_pd(p_a);
							__m256d rst_mm = _mm256_load_pd(p_des);

							rst_mm = _mm256_add_pd(_mm256_mul_pd(a_mm, b_mm), rst_mm);

							_mm256_store_pd(p_des, rst_mm);
							p_des += 4;
							p_a += 4;
						}
						for (; k < a_d0; ++k)//a row
						{
							(*p_des++) += (*p_a++) * b_tmp;
						}
					}
				}
				return result;
			}
			Array<float> mtimes_impl_small(const Array<float>& a, const Array<float>& b)
			{
				int a_d0 = a.get_dim_data(0), a_d1 = a.get_dim_data(1);
				int b_d0 = b.get_dim_data(0), b_d1 = b.get_dim_data(1);
				Array<float> result(a_d0, b_d1);
				for (int i = 0; i < b_d1; ++i)//b col
				{
					const float * p_b = &b[i*b_d0];
					for (int j = 0; j < b_d0; ++j)//b row
					{
						float * p_des = &result[i*a_d0];
						const float* p_a = &a[j*a_d0];
						float b_tmp = *p_b++;

						__m256 b_mm = _mm256_set1_ps(b_tmp);
						int k = 0;
						for (; k < a_d0 - 3; k += 8)//a row
						{
							__m256 a_mm = _mm256_load_ps(p_a);
							__m256 rst_mm = _mm256_load_ps(p_des);

							rst_mm = _mm256_add_ps(_mm256_mul_ps(a_mm, b_mm), rst_mm);

							_mm256_store_ps(p_des, rst_mm);
							p_des += 8;
							p_a += 8;
						}
						for (; k < a_d0; ++k)//a row
						{
							(*p_des++) += (*p_a++) * b_tmp;
						}
					}
				}
				return result;
			}
#elif defined CATOOL_ENABLE_SSE
			Array<double> mtimes_impl_small(const Array<double>& a, const Array<double>& b)
			{
				int a_d0 = a.get_dim_data(0), a_d1 = a.get_dim_data(1);
				int b_d0 = b.get_dim_data(0), b_d1 = b.get_dim_data(1);
				Array<double> result(a_d0, b_d1);
				for (int i = 0; i < b_d1; ++i)//b col
				{
					const double * p_b = &b[i*b_d0];
					for (int j = 0; j < b_d0; ++j)//b row
					{
						double * p_des = &result[i*a_d0];
						const double* p_a = &a[j*a_d0];
						double b_tmp = *p_b++;

						__m128d b_mm = _mm_set1_pd(b_tmp);

						int k = 0;
						for (; k < a_d0 - 1; k += 2)//a row
						{
							__m128d a_mm = _mm_load_pd(p_a);
							__m128d rst_mm = _mm_load_pd(p_des);

							rst_mm = _mm_add_pd(_mm_mul_pd(a_mm, b_mm), rst_mm);

							_mm_store_pd(p_des, rst_mm);
							p_des += 2;
							p_a += 2;
						}
						for (; k < a_d0; ++k)//a row
						{
							(*p_des++) += (*p_a++) * b_tmp;
						}
					}
				}
				return result;
			}
			Array<float> mtimes_impl_small(const Array<float>& a, const Array<float>& b)
			{
				int a_d0 = a.get_dim_data(0), a_d1 = a.get_dim_data(1);
				int b_d0 = b.get_dim_data(0), b_d1 = b.get_dim_data(1);
				Array<float> result(a_d0, b_d1);
				for (int i = 0; i < b_d1; ++i)//b col
				{
					const float * p_b = &b[i*b_d0];
					for (int j = 0; j < b_d0; ++j)//b row
					{
						float * p_des = &result[i*a_d0];
						const float* p_a = &a[j*a_d0];
						float b_tmp = *p_b++;

						__m128 b_mm = _mm_set1_ps(b_tmp);
						int k = 0;
						for (; k < a_d0 - 3; k += 4)//a row
						{
							__m128 a_mm = _mm_load_ps(p_a);
							__m128 rst_mm = _mm_load_ps(p_des);

							rst_mm = _mm_add_ps(_mm_mul_ps(a_mm, b_mm), rst_mm);

							_mm_store_ps(p_des, rst_mm);
							p_des += 4;
							p_a += 4;
						}
						for (; k < a_d0; ++k)//a row
						{
							(*p_des++) += (*p_a++) * b_tmp;
						}
					}
				}
				return result;
			}
#endif // CATOOL_ENABLE_SSE

			template<class T>
			void mtimes_micro_4x4(int p, T * rst, int rst_d0, const T* a, int a_d0, const T* b, int b_d0)
			{
				for (int k = 0; k < p; ++k)
				{
					for (int j = 0; j < 4; ++j)// b col
					{
						const T* p_a = &a[k * a_d0];
						T * p_rst = &rst[j * rst_d0];
						T p_b = b[k + j*b_d0];

						//rst[i + j * rst_d0] += a[i + k * a_d0] * b[k + j*b_d0];
						(*p_rst++) += (*p_a++)*p_b;
						(*p_rst++) += (*p_a++)*p_b;
						(*p_rst++) += (*p_a++)*p_b;
						(*p_rst++) += (*p_a++)*p_b;
					}
				}
			}

#if defined CATOOL_ENABLE_AVX
			inline void mtimes_micro_4x4(int p, double * rst, int rst_d0, const double* a, int a_d0, const double* b, int b_d0)
			{
				for (int k = 0; k < p; ++k)
				{
					//float * p_rst = &rst[0 * rst_d0];
					double p_b;

					__m256d a_mm, b_mm, rst_mm;

					a_mm = _mm256_load_pd(&a[k * a_d0]);

					//0 col
					p_b = b[k + 0 * b_d0];
					b_mm = _mm256_set1_pd(p_b);
					rst_mm = _mm256_load_pd(&rst[0 * rst_d0]);
					rst_mm = _mm256_add_pd(rst_mm, _mm256_mul_pd(a_mm, b_mm));
					_mm256_store_pd(&rst[0 * rst_d0], rst_mm);

					//1 col
					p_b = b[k + 1 * b_d0];
					b_mm = _mm256_set1_pd(p_b);
					rst_mm = _mm256_load_pd(&rst[1 * rst_d0]);
					rst_mm = _mm256_add_pd(rst_mm, _mm256_mul_pd(a_mm, b_mm));
					_mm256_store_pd(&rst[1 * rst_d0], rst_mm);

					//2 col
					p_b = b[k + 2 * b_d0];
					b_mm = _mm256_set1_pd(p_b);
					rst_mm = _mm256_load_pd(&rst[2 * rst_d0]);
					rst_mm = _mm256_add_pd(rst_mm, _mm256_mul_pd(a_mm, b_mm));
					_mm256_store_pd(&rst[2 * rst_d0], rst_mm);

					//3 col
					p_b = b[k + 3 * b_d0];
					b_mm = _mm256_set1_pd(p_b);
					rst_mm = _mm256_load_pd(&rst[3 * rst_d0]);
					rst_mm = _mm256_add_pd(rst_mm, _mm256_mul_pd(a_mm, b_mm));
					_mm256_store_pd(&rst[3 * rst_d0], rst_mm);
				}
			}

#elif defined CATOOL_ENABLE_SSE
			inline void mtimes_micro_4x4(int p, float * rst, int rst_d0, const float* a, int a_d0, const float* b, int b_d0)
			{
				for (int k = 0; k < p; ++k)
				{
					//float * p_rst = &rst[0 * rst_d0];
					float p_b;

					__m128 a_mm, b_mm, rst_mm;

					a_mm = _mm_load_ps(&a[k * a_d0]);

					//0 col
					p_b = b[k + 0 * b_d0];
					b_mm = _mm_set1_ps(p_b);
					rst_mm = _mm_load_ps(&rst[0 * rst_d0]);
					rst_mm = _mm_add_ss(rst_mm, _mm_mul_ss(a_mm, b_mm));
					_mm_store_ps(&rst[0 * rst_d0], rst_mm);

					//1 col
					p_b = b[k + 1 * b_d0];
					b_mm = _mm_set1_ps(p_b);
					rst_mm = _mm_load_ps(&rst[1 * rst_d0]);
					rst_mm = _mm_add_ss(rst_mm, _mm_mul_ss(a_mm, b_mm));
					_mm_store_ps(&rst[1 * rst_d0], rst_mm);

					//2 col
					p_b = b[k + 2 * b_d0];
					b_mm = _mm_set1_ps(p_b);
					rst_mm = _mm_load_ps(&rst[2 * rst_d0]);
					rst_mm = _mm_add_ss(rst_mm, _mm_mul_ss(a_mm, b_mm));
					_mm_store_ps(&rst[2 * rst_d0], rst_mm);

					//3 col
					p_b = b[k + 3 * b_d0];
					b_mm = _mm_set1_ps(p_b);
					rst_mm = _mm_load_ps(&rst[3 * rst_d0]);
					rst_mm = _mm_add_ss(rst_mm, _mm_mul_ss(a_mm, b_mm));
					_mm_store_ps(&rst[3 * rst_d0], rst_mm);
				}
			}
#endif // CATOOL_ENABLE_SSE
			//kc mc������4�ı���
			template<class T>
			inline void mtimes_block(T * rst, int rst_d0, const T* a, int a_d0, const T* b, int b_d0)
			{
				for (int i = 0; i < KC; i += 4)
				{
					T* p_rst = &rst[i*rst_d0];
					const T* p_a = &a[0 * a_d0];
					const T* p_b = &b[0 + i*b_d0];
					for (int j = 0; j < MC; j += 4)
					{
						//packing

						//mtimes_micro_4x4(b_d0, &rst[j + i*rst_d0], rst_d0, &a[j + 0 * a_d0], a_d0, &b[0 + i*b_d0], b_d0);
						mtimes_micro_4x4(b_d0, p_rst, rst_d0, p_a, a_d0, p_b, b_d0);
						p_a += 4;
						p_rst += 4;
					}
				}
			}

			template<class T>
			Array<T> mtimes_impl_large(const Array<T>& a, const Array<T>& b)
			{
				int a_d0 = a.get_dim_data(0), a_d1 = a.get_dim_data(1);
				int b_d0 = b.get_dim_data(0), b_d1 = b.get_dim_data(1);
				Array<T> result(a_d0, b_d1);
				int i, j;
				for (i = 0; i < b_d1 - KC + 1; i += KC)//c col
				{
					for (j = 0; j < a_d0 - MC + 1; j += MC)//c row
					{
						T * p_rst = &result[j + i*a_d0];
						const T *p_a = &a[j + 0 * a_d0];
						const T *p_b = &b[0 + i*b_d0];
						mtimes_block(p_rst, a_d0, p_a, a_d0, p_b, b_d0);
					}
					for (int k = 0; k < b_d0; ++k)
					{
						//for (int l=j;l<a_d0;++l)
						T* p_rst = &result[i*a_d0];
						const T* p_a = &a[k*a_d0];
						T tmp_b = b[k + i*b_d0];
						for (int l = j; l < a_d0; ++l)
						{
							//result[j + i*a_d0] += a[j + k*a_d0] * b[k + i*b_d0];
							(*p_rst++) = (*p_a++)*tmp_b;
						}
					}
				}
				for (; i < b_d1; ++i)
				{
					for (int k = 0; k < b_d0; ++k)
					{
						T* p_rst = &result[i*a_d0];
						const T* p_a = &a[k*a_d0];
						T tmp_b = b[k + i*b_d0];
						for (j = 0; j < a_d0; ++j)
						{
							//result[j + i*a_d0] += a[j + k*a_d0] * b[k + i*b_d0];
							(*p_rst++) = (*p_a++)*tmp_b;
						}
					}
				}
				return result;
			}

			template<class T>
			Array<T> copySubMatrix(const Array<T>& m, int dim0, int len0, int dim1, int len1)
			{
				Array<T> result(len0, len1);
				int m_d0 = m.get_dim_data(0);
				for (int i = 0; i < len1; ++i)
				{
					for (int j = 0; j < len0; ++j)
					{
						result[i*len0 + j] = m[(dim1 + i)*m_d0 + j + dim0];
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
				return mtimes_impl_small(a, b);
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
						if (i != (unsigned int)cum_dim)
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
			diff	Differences and Approximate Derivatives
			*/
			template<class T>
			Array<T> diff(const Array<T>& arry, int n = 1, int dim = 0)
			{
				Array<T> tmp_m(arry);
				if (n < 0)
					throw std::runtime_error("error: diff: order K must be non-negative");
				if (dim < 0 || dim >= arry.dim_size())
					throw std::runtime_error("error: diff: DIM must be a valid dimension");
				tmp_m.dimloop(dim, [&n, &dim](Array<T>& m, const std::vector<int>&dims)
				{
					std::vector<int> tmp_dims(dims);
					tmp_dims[dim] = 0;
					int index = m.composeIndex(tmp_dims);
					int acc = m.get_dim_acc(dim);
					int len = m.get_dim_data(dim);

					for (int i = 0; i < n; ++i)
						for (int &j = dims[dim]; j < len - i - 1; ++j)
							m[index + acc*j] = m[index + acc*(j + 1)] - m[index + acc*j];
				});
				std::vector<Range> sub_range = tmp_m.getFullLoop();
				sub_range[dim].end -= n;
				return tmp_m.subArray(sub_range);
			}
			/*
			movsum	Moving sum
			kb:С���귽��
			kf:�����귽��
			*/
			template<class T>
			Array<T> movsum(const Array<T>& m, int kb = 1, int kf = 1, int dim = 0)
			{
				Array<T> result(m.get_dim());
				m.dimloop(dim, [&result, &dim, &kb, &kf](const Array<T>& m, const std::vector<int>&dims)
				{
					std::vector<int> tmp_dims(dims);
					tmp_dims[dim] = 0;
					int index = m.composeIndex(tmp_dims);
					int acc = m.get_dim_acc(dim);
					int len = m.get_dim_data(dim);

					for (int &i = tmp_dims[dim]; i < len; ++i)
						for (int j = -kb; j <= kf; ++j)
							if (i + j >= 0 && i + j < len)
								result[result.composeIndex(tmp_dims)] += m[index + acc*(i + j)];
				});
				return result;
			}
			/*
			prod	Product of array elements
			*/
			template<class T>
			Array<T> prod(const Array<T>& m, int dim = 0)
			{
				Array<T> result;
				std::vector<int> dims = m.get_dim();
				dims[dim] = 1;
				result.resize(dims);
				result.fill(1);

				std::vector<Range> range = m.getFullLoop();
				for (int i = 0; i < m.get_dim_data(dim); ++i)
				{
					range[dim] = Range(i);
					m.loop(range, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
					{
						int index = 0;
						for (unsigned int i = 0; i < dims.size(); ++i)
						{
							if (i != dim)
								index += dims[i] * result.get_dim_acc(i);
						}
						result[index] *= m[m.composeIndex(dims)];
					});
				}
				return result;
			}
			/*
			sum	Sum of array elements
			*/
			template<class T>
			Array<T> sum(const Array<T>& m, int dim = 0)
			{
				Array<T> result;
				std::vector<int> dims = m.get_dim();
				dims[dim] = 1;
				result.resize(dims);

				std::vector<Range> range = m.getFullLoop();
				for (int i = 0; i < m.get_dim_data(dim); ++i)
				{
					range[dim] = Range(i);
					m.loop(range, [&result, &dim](const Array<T>& m, const std::vector<int>&dims)
					{
						int index = 0;
						for (unsigned int i = 0; i < dims.size(); ++i)
						{
							if (i != dim)
								index += dims[i] * result.get_dim_acc(i);
						}
						result[index] += m[m.composeIndex(dims)];
					});
				}
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
				Array<T> result(a);
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
				Array<T> result(a);
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

			inline std::pair<double, double> rat(double x, double tol)
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
			std::pair<Array<double>, Array<double>> rat(const Array<T> & x, double tol = 1e-6)
			{
				Array<double> n(x.get_dim()), d(x.get_dim());
				for (int i = 0; i < x.size(); ++i)
				{
					auto each_rst = rat(x[i], tol);
					n[i] = each_rst.first;
					d[i] = each_rst.second;
				}
				return{ n,d };
			}
			/*
			S = rats(X) returns a character vector containing the rational approximations to the elements of X using the default length of 13.
			rats returns asterisks for elements that cannot be printed in the allotted space, but which are not negligible compared to the other elements in X.
			S = rats(X,strlen) returns a character vector of length strlen. The rational approximation uses a tolerance that is inversely proportional to the length.
			*/
			inline string rats(double x)
			{
				std::pair<double, double> result = rat(x);
				return std::to_string(result.first) + "/" + std::to_string(result.second);
			}
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATIC_ELEMENTARYMATH_ARITHMETIC_H
