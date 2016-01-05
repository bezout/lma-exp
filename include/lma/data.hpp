#pragma once

#include "container.hpp"
#include <map>
#include <set>
#include <boost/function.hpp>
#include "tag.hpp"
#include "container.hpp"
#include "ct-analysis.hpp"


namespace lma
{

  //template<typename ...> struct Data;

  template<typename Functor/*, typename Option*/> struct Data
  {
    using InfoFunctor = AnalyseFunctor<Functor>;
    using Residual = typename InfoFunctor::Residual;
    using Parameters = typename InfoFunctor::Parameters;
    
    static constexpr int NbInstanceOfFunctor = -1;//NbInstanceOfFunctor_;
    static constexpr int NbInstanceOfParameters = -1;//NbInstanceOfParameters_;

    static constexpr size_t DDL = size(Type<Parameters>{});
    static constexpr size_t ErreurSize = size(Type<Residual>{});
    
    Container<std::pair<Functor,Parameters*>,NbInstanceOfFunctor> functors;
    
    
    int total_parameters() const { return parameters.size() * DDL; }
    int total_errors() const { return functors.size() * ErreurSize; }
    
    Container<Parameters*,NbInstanceOfParameters> parameters;
    Container<Parameters,NbInstanceOfParameters> save_parameters;
    
    std::set<Parameters*> parameters_set;

    void add(const Functor& f, Parameters* p)
    {
      functors.push_back(std::make_pair(f,p));
      
      
      //TODO ADD F & P
      if (find(parameters_set.begin(),parameters_set.end(),p)==parameters_set.end())
      {
        parameters_set.insert(p);
        parameters.push_back(p);
      }
    }
    
    void update()
    {
      parameters_set.clear();
      //TODO MAJ GRAPHE DE DONNEES
    }
    
    void update_parameters(const auto& delta)
    {
      for(size_t i = 0 ; i < parameters.size() ; ++i)
      {
        apply_increment(*parameters[i],delta.template segment<DDL>(i*DDL).data());
      }
    }
    
    void save()
    {
      save_parameters.resize(parameters.size());
      for(size_t i = 0 ; i < parameters.size() ; ++ i)
        save_parameters[i] = *parameters[i];
    }

    void restore()
    {
      for(size_t i = 0 ; i < parameters.size() ; ++ i)
        *parameters[i] = save_parameters[i];
    }
    
    void call_analytical(auto& jacobians) const
    {
      for(size_t i = 0 ; i < functors.size() ; ++i)
        functors[i].first.analytical(*functors[i].second,jacobians.block(i,0,ErreurSize,DDL));
    }
    
    template<typename CastResidual>
    int compute_error(auto& errors, const Type<CastResidual>&) const
    {
      int success = 0;
      for(size_t i = 0 ; i < functors.size() ; ++i)
        success += functors[i].first(*functors[i].second,CastResidual(errors[i]).data());
      return success;
    }
  };


  // template<typename ... F, typename ... O>
  // struct Datas<Functors(F...), Options(O...)>
  // {
  //   Containers<F...> containers;
  // };
}
