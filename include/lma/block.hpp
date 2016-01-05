#pragma once

#include "traits.hpp"
#include <Eigen/Core>


namespace lma
{
  template<typename Float, int I, int J> struct CreateBlock
  {
    using Block = Eigen::Matrix<Float,I,J>;
  };
  
  
  template<typename Float> struct CreateBlock<Float,1,1>
  {
    using Block = Float;
  };
  
  /*
  template<typename Float, int J> struct CreateBlock<Float,0,J>
  {
    using Block = Eigen::Matrix<Float,Eigen::Dynamic,J>;
  };
  
  template<typename Float, int I> struct CreateBlock<Float,I,0>
  {
    using Block = Eigen::Matrix<Float,I,Eigen::Dynamic>;
  };
  
  template<typename Float> struct CreateBlock<Float,0,0>
  {
    using Block = Eigen::Matrix<Float,Eigen::Dynamic,Eigen::Dynamic>;
  };
  */
  
  template<typename Float, int I, int J> 
  using Block = typename CreateBlock<Float,I,J>::Block;
  

  template<typename Float>
  Float squared_norm(const Float& value, EnableIfIsFloating<Float> = 0) { return value * value ; }


  template<typename Float, int I, int J>
  Float squared_norm(const Eigen::Matrix<Float,I,J>& mat) { return mat.squaredNorm() ; }

  template<typename Float, int I, int J>
  constexpr int cols(const Eigen::Matrix<Float,I,J>& mat)
  {
    return J;
  }
  
  template<typename Float, int I, int J>
  constexpr int rows(const Eigen::Matrix<Float,I,J>& mat)
  {
    return I;
  }
  
  template<typename Float, int I>
  int cols(const Eigen::Matrix<Float,I,Eigen::Dynamic>& mat)
  {
    return mat.cols();
  }
  
  template<typename Float, int J>
  int rows(const Eigen::Matrix<Float,Eigen::Dynamic,J>& mat)
  {
    return mat.rows();
  }
  
  template<typename Float, int I, int J>
  void disp_size(const Eigen::Matrix<Float,I,J>& mat, std::string name)
  {
    std::cout << " Size of " << name << " : " << rows(mat) << ", " << cols(mat) << std::endl;
  }
  
  template<typename Float>
  void disp_size(const Float&, std::string name)//, EnableIfIsFloating<Float>=0)
  {
    std::cout << " Size of " << name << " : 1 " << std::endl;
  }
  
  template<typename Float, int I, int J>
  struct Name<Eigen::Matrix<Float,I,J>>
  {
    static std::string name()
    {
      return std::string("Eigen::Matrix<") + lma::name<Float>() + "," + (I==-1?"Dynamic":std::to_string(I)) + "," + (J==-1?"Dynamic":std::to_string(J)) + ">";
    }
  };

}


namespace lma
{
  constexpr auto pow(const auto& value, int i)
  {
    return (i==0) ? value : value * pow(value,i-1);
  }
}
