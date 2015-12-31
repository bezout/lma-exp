#pragma once

#include <brigand/brigand.hpp>
#include <iostream>

namespace brigand
{
  using stop_ = std::false_type;
  using continue_ = std::true_type;

  brigand::size_t<0> zero {};
  brigand::size_t<1> one {};

  template<typename ... T> transform<list<T...>,type_<_1>> remove_type(T...) { return {}; }
  template<typename V, V v1, V v2> std::integral_constant<V,v1+v2> plus_(std::integral_constant<V,v1>, std::integral_constant<V,v2>) { return {}; }

  template<typename V, V v> std::true_type equal_(std::integral_constant<V,v>, std::integral_constant<V,v>) { return {}; }
  template<typename V, V v1, V v2> std::false_type equal_(std::integral_constant<V,v1>, std::integral_constant<V,v2>) { return {}; }

  template<typename V, V v> std::false_type not_equal_(std::integral_constant<V,v>, std::integral_constant<V,v>) { return {}; }
  template<typename V, V v1, V v2> std::true_type not_equal_(std::integral_constant<V,v1>, std::integral_constant<V,v2>) { return {}; }

  template<typename L, typename I> brigand::at<L,I> at_(L, I) { return {}; }
  void for_each(auto L, auto f) { brigand::for_each<decltype(L)>(f); }

  template<typename ... L> brigand::size_t<brigand::size<brigand::list<L...>>::value> size_(brigand::list<L...>) { return {};}
  template<typename ... L> brigand::list<L...> list_(L...) { return {};}
  template<typename ... T> void expand(auto f, list<T...>) { f(T{}...); }
}

namespace lma
{
  void repeat(auto f, auto, auto, std::false_type, auto ... t)
  {
    brigand::expand(f,brigand::remove_type(t...));
  }

  void repeat(auto f, auto lists, auto i, std::true_type, auto ... n_uplets)
  {
    brigand::for_each(at_(lists,i),[&](auto type)
    {
      repeat(f,lists,brigand::plus_(i,brigand::one),brigand::not_equal_(brigand::plus_(i,brigand::one),brigand::size_(lists)),n_uplets...,type);
    });
  }

  void for_each_combinaison(auto lists, auto f)
  {
    repeat(f,lists,brigand::zero,brigand::not_equal_(brigand::one,brigand::size_(lists)));
  };
}
