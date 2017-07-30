#pragma once
#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATICS_RANDOMNUMBER_RAND_H
#define CATOOL_MAINTOOLBOX_MATHEMATICS_RANDOMNUMBER_RAND_H

#include<cmath>
#include"../../Array.h"

namespace catool
{
	namespace main_toolbox
	{
		namespace mathematics
		{
			/*
			rand
			Uniformly distributed random numbers
			*/
			template<class T=double>
			inline T rand()
			{
				return ((float)std::rand() / RAND_MAX);
			}
			template<class T = double>
			inline Array<T> rand(int n)
			{
				Array<T> result(n, n);
				for (auto& each : result)
					each = (float)std::rand() / RAND_MAX;
				return result;
			}
			template<typename T=double,typename T1, typename... T2>
			Array<T> rand(T1 p, T2... arg)
			{
				Array<T> result;
				result.resize(p, arg...);
				for (auto& each : result)
					each = (float)std::rand() / RAND_MAX;
				return result;
			}
			inline Array<double> rand(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<double> result;
				result.get_dim() = sz.get_data();
				result.resize_from_dim();
				for (auto& each : result)
					each = (double)std::rand() / RAND_MAX;
				return result;
			}
			/*
			randn
			Normally distributed random numbers
			*/
			const int NSUM = 25;
			inline double randn()
			{
				double x = 0;
				int i;
				for (i = 0; i < NSUM; i++)
				{
					x += (double)std::rand() / RAND_MAX;
				}

				x -= NSUM / 2.0;
				x /= std::sqrt(NSUM / 12.0);

				return x;
			}
			inline Array<double> randn(int n)
			{
				Array<double> result(n, n);
				for (auto& each : result)
					each = randn();
				return result;
			}
			template<typename T1, typename... T2>
			inline Array<double> randn(T1 p, T2... arg)
			{
				Array<double> result;
				result.resize(p, arg...);
				for (auto& each : result)
					each = randn();
				return result;
			}
			inline Array<double> randn(const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<double> result;
				result.resize(sz);
				for (auto& each : result)
					each = randn();
				return result;
			}
			/*
			randi
			Uniformly distributed pseudorandom integers
			*/
			inline double randi(int max)
			{
				return ((double)std::rand() / RAND_MAX)*max;
			}
			inline Array<int> randi(int max, int n)
			{
				Array<int> result(n, n);
				for (auto& each : result)
					each = (int)((double)std::rand() / RAND_MAX)*max;
				return result;
			}
			template<typename T1, typename... T2>
			inline Array<int> randi(int max, T1 p, T2... arg)
			{
				Array<int> result;
				result.resize(p, arg...);
				for (auto& each : result)
					each = (int)((double)std::rand() / RAND_MAX)*max;
				return result;
			}
			inline Array<double> randi(int max, const Array<int> & sz)
			{
				if (sz.dim_size() != 1)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				Array<double> result;
				result.resize(sz);
				for (auto& each : result)
					each = ((double)std::rand() / RAND_MAX)*max;
				return result;
			}
			/*
			rng
			Control random number generation
			*/
			enum class RANG_TYPE { SHUFFLE, DEFAULT };
			[[noreturn]]inline void rng(unsigned int seed)
			{
				std::srand(seed);
			}

			[[noreturn]]inline void rng(RANG_TYPE type)
			{
				if (type == RANG_TYPE::SHUFFLE)
				{
					std::srand(static_cast<unsigned int>(std::time(nullptr)));
				}
				else
				{
					throw std::runtime_error("Unknown rang type.");
				}
			}
			/*
			RandStream
			TODO
			*/
			enum class RandGenType {};
			enum class RandParam { Seed, NormalTransform };
			class RandStream
			{
			public:
				//RandStream(RandGenType gentype, RandParam name,int value);
			};
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATICS_RANDOMNUMBER_RAND_H
