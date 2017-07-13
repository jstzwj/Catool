#pragma once
#ifndef CATOOL_MAINTOOLBOX_SPARSEMATRIX_H
#define CATOOL_MAINTOOLBOX_SPARSEMATRIX_H

#include<vector>
#include<map>
#include<utility>
#include<stdexcept>
#include<cstdint>

#include"Array.h"

namespace catool
{
	namespace main_toolbox
	{
		class SparseKey
		{
		public:
			SparseKey() :row(), col() {}
			SparseKey(int row_,int col_) :row(row_), col(col_) {}
			int row;
			int col;
		};
		template<class T>
		class SparseMatrix
		{
		private:
			int row;
			int col;
			std::vector<std::pair<SparseKey, T>> data;
		public:
			using EntryType = std::pair<uint64_t, T>;
			using IndexType = uint64_t;
			using KeyType = SparseKey;
			using ValueType = T;

			SparseMatrix() noexcept {}
			SparseMatrix(int row_,int col_) noexcept
			{
				if (row_ < 0)row = 0;
				else row = row_;
				if (col_ < 0)col = 0;
				else col = col_;
			}
			SparseMatrix(const std::vector<int> &dims) noexcept
				:dim(dims) {}
			template<class ...K>
			SparseMatrix(K ...arg)
			{
				MatrixConstructor(arg...);
			}
			template<typename T1, typename... T2>
			void MatrixConstructor(T1 p, T2... arg)
			{
				if (p < 0)p = 0;
				dim.push_back(p);
				MatrixConstructor(arg...);
			}
			void MatrixConstructor() {}

			SparseMatrix(std::initializer_list<T> list)
			{
				dim.push_back(1);
				dim.push_back(list.size());

				for (unsigned int i = 0; i < list.size(); ++i)
				{
					data.push_back(EntryType(i, list[i]));
				}
			}

			template<class U>
			explicit SparseMatrix(const SparseMatrix<U>& other)
				:dim(other.get_dim()), data(other.begin(), other.end()) {}

			SparseMatrix(const SparseMatrix<T>& other)
				: dim(other.get_dim()), data(other.begin(), other.end()) {}

			//using iterator = std::vector<T>::iterator;
			//using const_iterator = std::vector<T>::const_iterator;

			T& operator[](uint64_t n)
			{
				for (auto& each_entry : data)
				{
					if (each_entry.first == n)
						return each_entry.second;
				}
				data.push_back(EntryType(n, T()));
				return data.back();
			}
			int size() const { return data.size(); }
			/*void resize(int size) { data.resize(size); }*/
			std::vector<int> & get_dim() { return dim; }
			const std::vector<int> & get_dim() const { return dim; }
			std::vector<T> & get_data() { return data; }
			const std::vector<T> & get_data() const { return data; }

			int dim_size()const { return dim.size(); }
			int get_dim_data(int n) const
			{
				if (n >= static_cast<int>(dim.size()))
					return 1;
				else
					return dim[n];
			}
			int get_dim_acc(int n)const
			{
				int acc = 1;
				for (int i = 0; i < n; ++i)
				{
					acc *= dim[i];
				}
				return acc;
			}
			template<typename T1, typename... T2>
			void resize(T1 p, T2... arg)
			{
				dim.clear();
				dim.push_back(p);
				resize_impl(arg...);
			}
			template<typename T1, typename... T2>
			void resize_impl(T1 p, T2... arg)
			{
				dim.push_back(p);
				resize_impl(arg...);
			}
			void resize_impl() {}

			void resize(const std::vector<int> & sz)
			{
				dim = sz;
			}

			void resize(const Array<int> & sz)
			{
				if (sz.dim_size() > 2)
				{
					throw std::runtime_error("the size array shall be one dimension array.");
				}
				dim = sz.get_data();
			}

			bool isMatrix()const
			{
				int count = 0;
				for (unsigned int i = 0; i < dim.size(); ++i)
				{
					if (dim[i] > 1)
					{
						count++;
						if (count >= 2)
							return true;
					}
				}
				return false;
			}
			bool isVector()const
			{
				int count = 0;
				for (unsigned int i = 0; i < dim.size(); ++i)
				{
					if (dim[i] > 1)
					{
						count++;
						if (count >= 2)
							return false;
					}
				}
				return true;
			}
			bool isRow()const
			{
				for (unsigned int i = 0; i < dim.size(); ++i)
					if (i != 1 && dim[i] != 1)return false;
				return true;
			}
			bool isCol()const
			{
				for (unsigned int i = 0; i < dim.size(); ++i)
					if (i != 0 && dim[i] != 1)return false;
				return true;
			}
			bool isEmpty()const
			{
				if (dim.size() == 0)return true;
				for (unsigned int i = 0; i < dim.size(); ++i)
					if (dim[i] == 0)return true;
				return true;
			}
		};



		/*
		spalloc
		Allocate space for sparse matrix
		*/
		template<class T = int>
		SparseMatrix<T> spalloc(int m, int n,uint64_t nz)
		{
			SparseMatrix<T> rst(m, n);
			rst.get_data().reserve(nz);
			return rst;
		}


		/*
		speye
		Sparse identity matrix
		S = speye(m,n)
		S = speye([m n])
		S = speye(n)
		S = speye
		*/
		template<class T=int>
		SparseMatrix<T> speye(int m,int n)
		{
			SparseMatrix<T> rst(m,n);
			int min_dim = m > n ? n : m;
			for (int i = 0; i < min_dim;++i)
			{
				rst[i*m + i] = 1;
			}
			return rst;
		}
		template<class T = int>
		SparseMatrix<T> speye(int n)
		{
			SparseMatrix<T> rst(n, n);
			for (int i = 0; i < min_dim; ++i)
			{
				rst[i*n + i] = 1;
			}
			return rst;
		}
		/*
		sparse

		Create sparse matrixcollapse all in page
		Syntax
		S = sparse(A)
		S = sparse(m,n)
		S = sparse(i,j,v)
		S = sparse(i,j,v,m,n)
		S = sparse(i,j,v,m,n,nz)
		
		*/
		template<class T>
		SparseMatrix<T> sparse(const Array<T>& a)
		{
			if (n.dim_size() > 2)
				throw std::runtime_error("error: sparse not defined for N-D objects");
			SparseMatrix<T> rst(a.get_dim_data(0), a.get_dim_data(1));
			for (int i = 0; i < a.get_dim_data(0); ++i)
			{
				for (int j = 0; j < a.get_dim_data(1);++j)
				{

				}
			}
			return rst;
		}

	}
}

#endif // !CATOOL_MAINTOOLBOX_SPARSEMATRIX_H
