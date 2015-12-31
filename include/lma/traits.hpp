#pragma once

#include "exceptions.hpp"
#include <string>
#include <typeinfo>
#include <type_traits>

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
   
  struct Adl{};

  template<typename> struct Type {};

  template<typename Float> using EnableIfIsFloating = typename std::enable_if<std::is_floating_point<Float>::value>::type*;
}
