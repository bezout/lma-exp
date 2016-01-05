#pragma once

#include <array>
#include <vector>
#include <Eigen/StdVector>// inclure que le fichier utile
#include "traits.hpp"
#include "tag.hpp"

#include "tuple_traits.hpp"


namespace lma
{
  template<typename T> using AlignedVector = std::vector<T,Eigen::aligned_allocator<T>>;
  
  template<typename F, int Dimension>
  struct Container
  {
    std::array<F,Dimension> data;
    int last = 0;
    void push_back(const F& f) { assert(last < Dimension); data[last] = f; ++last; }
    constexpr size_t size() const { return Dimension; }
    inline void resize(size_t) {}
    const F& operator[](size_t i) const { assert( i < size() ); return data[i]; }
    F& operator[](size_t i) { assert( i < size() ); return data[i]; }
  };
  
  template<typename F>
  struct Container<F,-1>
  {
    AlignedVector<F> data;
    void push_back(const F& f) { data.push_back(f); }
    size_t size() const { return data.size(); }
    void resize(size_t s) { data.resize(s); }
    const F& operator[](size_t i) const { assert( i < size() ); return data[i]; }
    F& operator[](size_t i) { assert( i < size() ); return data[i]; }
  };
  
  template<typename F, int Dimension> auto begin(const Container<F,Dimension>& container) { return container.data.begin(); }
  template<typename F, int Dimension> auto end(const Container<F,Dimension>& container) { return container.data.end(); }
  
  template<typename F, int Dimension> auto begin(Container<F,Dimension>& container) { return container.data.begin(); }
  template<typename F, int Dimension> auto end(Container<F,Dimension>& container) { return container.data.end(); }
  

  template<typename X, int I> struct first_element<Container<X,I>>
  {
    using type = typename std::tuple_element<0,X>::type;
  };

}
