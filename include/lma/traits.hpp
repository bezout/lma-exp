#pragma once

#include "exceptions.hpp"
#include <string>
#include <typeinfo>
#include <type_traits>
#include <iostream>

namespace lma
{
  struct clement_type{};
  inline void clement(clement_type){}

  template<typename T, typename Enable = void> struct Name
  {
    static std::string name() { return typeid(T).name();}
  };

  template<typename T> std::string name()
  {
    return Name<T>::name();
  }
   
  template<> struct Name<float> { static std::string name() { return "float";} };
  template<> struct Name<double> { static std::string name() { return "double";} };
  template<> struct Name<int> { static std::string name() { return "int";} };
  template<> struct Name<char> { static std::string name() { return "char";} };

   
  struct Adl{};

  template<typename> struct Type {};

  template<typename Float>
  using EnableIfIsFloating = typename std::enable_if<std::is_floating_point<Float>::value>::type*;

  // template<template<typename ...> typename A, typename ... B> struct Name<A<B...>>
  // {
  //   static std::string name() { return lma::name<B>() ... + ","; }
  // };
}
