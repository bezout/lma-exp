#include "rosenbrock.hpp"

#include "lma/solver.hpp"

#include "lma/for_each_combinaison.hpp"
#include "config.hpp"

using namespace lma;

using Result = std::pair<std::string,double>;

Result test_dynamic(auto lm, auto verbose)
{
  std::string name_algo = name<decltype(lm)>();
  std::cout << color.bold() << " === TEST DYNAMIC : " << name_algo << " \t === " << color.reset() << std::endl;
  Parameters parameters {0.9,0.9};
  return 
  {
    name_algo,
    Solver<Rosenbrock>()
    .add(Rosenbrock{1},&parameters)
    .add(Rosenbrock{2},&parameters)
    .add(Rosenbrock{3},&parameters)
    .solve(lm,verbose)
    .final_cost
  };
}

Result test_static(auto lm, auto verbose)
{
  std::string name_algo = name<decltype(lm)>();
  std::cout << color.bold() << " === TEST STATIC  : " << name_algo << " \t === " << color.reset() << std::endl;
  Parameters parameters {0.9,0.9};
  return
  {
    name_algo,
    Solver<Rosenbrock>::SetNbInstanceOfFunctors<3>::type::SetNbInstanceOfParameters<1>::type()
    .add(Rosenbrock{1},&parameters)
    .add(Rosenbrock{2},&parameters)
    .add(Rosenbrock{3},&parameters)
    .solve(lm,verbose)
    .final_cost
  };
}

template<typename ... Options> void launch_tests(auto back_inserter, Options ... options)
{
  back_inserter = test_dynamic(options...);
  back_inserter++;
  back_inserter = test_static(options...);
  back_inserter ++;
}

template<template<typename> typename Policy, typename Float, typename Verbose>
void call_solver(Type<Policy<Float>>, Verbose verbose, auto back_inserter)
{
  launch_tests(back_inserter, Policy<Float>{rosenbrock_nb_iteration,Float(1.)},verbose);
}


struct StaticCall
{
 StaticCall()
 {
  std::vector<Result> results;
  for_each_combinaison(CONFIGS{},
     [&results](auto verbose, auto lm, auto flt)
     {
      using LM = typename decltype(lm)::template SetFloating<decltype(flt)>::type;
      call_solver(Type<LM>{},verbose, std::back_inserter(results));
     });
  for(auto& r : results)
    std::cout << r.first << "\t: " << r.second << std::endl;


  double threshold = 0.00001;

  struct LMA_TEST : std::runtime_error { LMA_TEST() : std::runtime_error("Threshold Exceeded") {} };

  if(results.size() > 1)
  for(size_t i = 0 ; i < results.size()-1 ; ++i)
  {
    if (std::abs(results[i].second - results[i+1].second) > threshold)
      throw LMA_TEST{};
  }
 }
} static_call;

