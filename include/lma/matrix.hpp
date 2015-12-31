#pragma once

#include "block.hpp"
//#include "container.hpp"
//#include <Eigen/Cholesky>
//#include <Eigen/Dense>


namespace lma
{
  
  template<typename Block, int Dimension> struct CreateMatrix
  {
    using Matrix = Eigen::Matrix<typename Block::Scalar,Eigen::Dynamic,Eigen::Dynamic>;
  };

  template<int Dimension> struct CreateMatrix<float,Dimension>
  {
    using Matrix = Eigen::Matrix<float,Eigen::Dynamic,Eigen::Dynamic>;
  };
  
  template<int Dimension> struct CreateMatrix<double,Dimension>
  {
    using Matrix = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic>;
  };

  template<typename Block, int Dimension>
  using Matrix = typename CreateMatrix<Block,Dimension>::Matrix;
  
  template<typename Block, int Dimension> struct CreateVector
  {
    using Vector = Eigen::Matrix<typename Block::Scalar,Eigen::Dynamic,1>;
  };
  
  template<int Dimension> struct CreateVector<float,Dimension>
  {
    using Vector = Eigen::Matrix<float,Eigen::Dynamic,1>;
  };

  template<int Dimension> struct CreateVector<double,Dimension>
  {
    using Vector = Eigen::Matrix<double,Eigen::Dynamic,1>;
  };

  template<typename Block, int Dimension>
  using Vector = typename CreateVector<Block,Dimension>::Vector;
  
  template<typename Mat, typename Float>
  Mat& damping(Mat& mat, const Float& lambda)
  {
    for(int i = 0 ; i < mat.cols() ; ++i)
      mat(i,i) += lambda;
    return mat;
  }
 
  
  template<typename Matrix, typename Vector>
  constexpr Vector llt(Matrix u, Vector x, int size)
  {
    for(int i = 0 ; i < size ; ++i)
    {
      for(int k = 0 ; k < i ; ++k)
        u(i,i) -= u(k,i) * u(k,i);
      
      assert(u(i,i)>0);
      if (u(i,i)<=0) throw ZeroOrInfiniteError("LLT");
      u(i,i) = std::sqrt(u(i,i));
      
      for(int j = i + 1; j < size ; ++j)
      {
        for(int k = 0 ; k < i ; ++k)
          u(i,j) -= u(k,i) * u(k,j);
        u(i,j) /= u(i,i);
      }
    }

    for(int j = 0 ; j < size; ++j)
    {
      for(int i = 0 ; i < j ; ++i)
        x[j] -= u(i,j) * x[i];
      x[j] /= u(j,j);
    }
    
    for(int j = size - 1 ; j >=0  ; --j)
    {
      for(int i = j+1 ; i < size ; ++i)
        x[j] -= u(j,i) * x[i];
      x[j] /= u(j,j);
    }
    return x;
  }
  
}
