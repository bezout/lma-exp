#pragma once

#include "lma/predef.hpp"

// PROBLEM DEFINITION

static const int rosenbrock_nb_iteration = 2;

struct Parameters{ double x,y;};

inline std::ostream& operator<<(std::ostream& o, const Parameters& p) { return o << "Parameters(" << p.x << "," << p.y << ")"; }

struct Rosenbrock
{
  double sigma;
  bool operator()(const Parameters& p, double& r) const
  {
    auto& x = p.x;
    auto& y = p.y;
    r = (1.0 - x) * (1.0 - x) + 100.0 * (y - x * x) * (y - x * x);
    r *= sigma;
    return true;
  }

  void analytical(const Parameters& p, auto mat) const
  {
    //resize(mat,2);
    auto& x = p.x;
    auto& y = p.y;
    mat(0,0) = -2.0 * (1.0 - x) - 200.0 * (y - x * x) * 2.0 * x;
    mat(0,1) = 200.0 * (y - x * x);
    mat *= sigma;
  }
};

//constexpr int size(const auto&) { return -1 ;}

namespace lma
{
  void apply_increment(Parameters& parameters, const auto* delta)
  {
    //static_assert( size(Type<Parameters>{}) == 2 , "size(Type<Parameters>{})==2");
    parameters.x += delta[0];
    parameters.y += delta[1];
  }

  constexpr int size(Type<Parameters>) { return 2; }
  constexpr int size(Type<double>) { return 1; }

  template<> struct Name<Parameters> { static std::string name() { return "Parameters"; } };
  template<> struct Name<Rosenbrock> { static std::string name() { return "Rosenbrock"; } };
  
  /*
  template<> struct DDL<Parameters,2>
  {
    void update_parameters(Parameters& parameters, const auto* delta)
    {
      parameters.x += delta[0];
      parameters.y += delta[1];
    }
  };*/
}
