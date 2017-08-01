#pragma once
#ifndef CATOOL_MAINTOOLBOX_SPARSEMATRIX_H
#define CATOOL_MAINTOOLBOX_SPARSEMATRIX_H

#include<vector>
#include<map>
#include<utility>
#include<stdexcept>
#include<limits>
#include<cstdint>
#include<cmath>

#include"Array.h"

namespace catool
{
	namespace main_toolbox
	{
		class SparseKey
		{
		public:
			SparseKey() :row(), col() {}
			SparseKey(int row_, int col_) :row(row_), col(col_) {}
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

			SparseMatrix(int row_ = 1, int col_ = 1) noexcept
			{
				if (row_ < 0)row = 0;
				else row = row_;
				if (col_ < 0)col = 0;
				else col = col_;
			}

			SparseMatrix(std::initializer_list<T> list)
			{
				row = 1;
				col = list.size();

				for (unsigned int i = 0; i < list.size(); ++i)
				{
					data.push_back(EntryType(i, list[i]));
				}
			}

			template<class U>
			explicit SparseMatrix(const SparseMatrix<U>& other)
				:row(other.row), col(other.col), data(other.begin(), other.end()) {}

			SparseMatrix(const SparseMatrix<T>& other)
				:row(other.row), col(other.col), data(other.begin(), other.end()) {}

			//using iterator = std::vector<T>::iterator;
			//using const_iterator = std::vector<T>::const_iterator;

			T& operator[](uint64_t n)
			{
				for (auto& each_entry : data)
				{
					if (each_entry.first.row + each_entry.first.col*row == n)
						return each_entry.second;
				}
				data.push_back(EntryType(n, T()));
				return data.back();
			}

			T& at(int row_, int col_)
			{
				for (auto& each_entry : data)
				{
					if (each_entry.first.row == row_&&each_entry.first.col == col_)
						return each_entry.second;
				}
				data.push_back(EntryType(SparseKey(row_, col_), T()));
				return data.back();
			}

			bool contain(int row_, int col_)
			{
				for (auto& each_entry : data)
				{
					if (each_entry.first.row == row_&&each_entry.first.col == col_)
						return true;
				}
				return false;
			}

			IndexType data_size() const { return data.size(); }
			IndexType size() const { return row*col; }
			int row()const { return row; }
			int col()const { return col; }

			void resize(int row_, int col_)
			{
				row = row_;
				col = col_;
			}

			/*bool isMatrix()const
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
			*/
		};

		/*
		spalloc
		Allocate space for sparse matrix
		*/
		template<class T = int>
		SparseMatrix<T> spalloc(int m, int n, uint64_t nz)
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
		template<class T = int>
		SparseMatrix<T> speye(int m, int n)
		{
			SparseMatrix<T> rst(m, n);
			int min_dim = m > n ? n : m;
			for (int i = 0; i < min_dim; ++i)
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
				for (int j = 0; j < a.get_dim_data(1); ++j)
				{
					rst.at(i, j) = a[j*a.get_dim_data(0) + i];
				}
			}
			return rst;
		}
		template<class T>
		SparseMatrix<T> sparse(const Array<T>& a, double & compressed_percent)
		{
			if (n.dim_size() > 2)
				throw std::runtime_error("error: sparse not defined for N-D objects");
			SparseMatrix<T> rst(a.get_dim_data(0), a.get_dim_data(1));
			for (int i = 0; i < a.get_dim_data(0); ++i)
			{
				for (int j = 0; j < a.get_dim_data(1); ++j)
				{
					if (std::abs(a[j*a.get_dim_data(0) + i]) >= std::numeric_limits<double>::epsilon())
						rst.at(i, j) = a[j*a.get_dim_data(0) + i];
				}
			}
			compressed_percent = (double)rst.data_size() / a.size();
			return rst;
		}
		template<class T>
		SparseMatrix<T> sparse(int m, int n)
		{
			return SparseMatrix<T>(m, n);
		}

		/*
		nnz
		Number of nonzero matrix elements
		*/
		template<class T>
		uint64_t nnz(const SparseMatrix<T> & m)
		{
			return m.size() - m.data_size();
		}
	}
}

#endif // !CATOOL_MAINTOOLBOX_SPARSEMATRIX_H
