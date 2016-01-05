#pragma once

namespace lma
{
  template<int I> struct Int{};

  struct Functor {};
  struct Functors {};
  struct Options {};

  template<typename ... L> struct First { };
  template<typename F, typename ... L> struct First<F,L...> { using type = F; };
}