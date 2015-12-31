#pragma once

#include "exceptions.hpp"
#include <string>
#include <typeinfo>
#include <type_traits>

namespace lma
{
  struct clement_type{};
  inline void clement(clement_type){}

  template<class T, class Enable = void> struct Name
  {
    static std::string name() { return typeid(T).name();}
  };

  template<class T> std::string name()
  {
    return Name<T>::name();
  }
   
  template<> struct Name<float> { static std::string name() { return "float";} };
  template<> struct Name<double> { static std::string name() { return "double";} };
   
  struct Adl{};

  template<class> struct Type {};

  template<class Float> using EnableIfIsFloating = typename std::enable_if<std::is_floating_point<Float>::value>::type*;
}
