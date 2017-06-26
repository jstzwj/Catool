#pragma once
#pragma once
#ifndef CATOOL_MAINTOOLBOX_MATHEMATICS_RANDOMNUMBER_RAND_H
#define CATOOL_MAINTOOLBOX_MATHEMATICS_RANDOMNUMBER_RAND_H

#include<cmath>
#include"../ElementaryMath/Array.h"

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
			inline double rand()
			{
				return ((double)std::rand() / RAND_MAX);
			}
			inline Array<double> rand(int n)
			{
				Array<double> result(n, n);
				for (auto& each : result)
					each = (double)std::rand() / RAND_MAX;
				return result;
			}
			template<typename T1, typename... T2>
			Array<double> rand(T1 p, T2... arg)
			{
				Array<double> result;
				result.resize(p, arg...);
				for (auto& each : result)
					each = (double)std::rand() / RAND_MAX;
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
			inline Array<double> randi(int max,int n)
			{
				Array<double> result(n, n);
				for (auto& each : result)
					each = ((double)std::rand() / RAND_MAX)*max;
				return result;
			}
			template<typename T1, typename... T2>
			inline Array<double> randi(int max,T1 p, T2... arg)
			{
				Array<double> result;
				result.resize(p, arg...);
				for (auto& each : result)
					each = ((double)std::rand() / RAND_MAX)*max;
				return result;
			}
			inline Array<double> randi(int max,const Array<int> & sz)
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
			enum RANG_TYPE {SHUFFLE,DEFAULT};
			[[noreturn]]inline void rng(unsigned int seed)
			{
				std::srand(seed);
			}

			[[noreturn]]inline void rng(RANG_TYPE type)
			{
				if (type== RANG_TYPE::SHUFFLE)
				{
					std::srand(static_cast<unsigned int>(std::time(nullptr)));
				}
				else
				{
					throw std::runtime_error("Unknown rang type.");
				}
			}


		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_MATHEMATICS_RANDOMNUMBER_RAND_H
