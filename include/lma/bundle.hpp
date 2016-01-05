#pragma once

#include "data.hpp"
#include "tuple_traits.hpp"

namespace lma
{

  template<typename> struct FunctorToContainer;
  template<typename F, int Dimension> struct FunctorToContainer<Functor(F,Int<Dimension>)>
  {
    using InfoFunctor = AnalyseFunctor<F>;
    using Residual = typename InfoFunctor::Residual;
    using Parameters = typename InfoFunctor::Parameters;

    using Tuple = std::tuple<Functor,Parameters*>;
    using type = Container<Tuple,Dimension>;
  };
  
  // F = Functor(Rosenbrock,Int<-1>)
  template<class F> using ToContainer = typename FunctorToContainer<F>::type;

	template<typename ... Functors>
	struct Bundle
	{
    //using Tuple = std::tuple< typename CreateContainer<P>::type... >;
    using FunctorsTuple = std::tuple< ToContainer<Functors>... >;

    FunctorsTuple functors_tuple;

    Bundle()
    {
      //std::cout << name<FunctorsTuple>() << std::endl;
    }

    

    template<typename F, typename P>
    Bundle& add(const F& f, P* parameters)
    {
      find_by_first_element<F>(functors_tuple).add(std::make_tuple(f,parameters));
      return *this;
    }
	};
}

/*

List of functors -> List of parameters
                 -> List of relations


*/