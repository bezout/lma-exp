#pragma once

namespace lma
{
  template<typename From, typename To> struct CastResidual
  {
    From& original;
    To temporary;
    To& data() { return temporary; }
    ~CastResidual() { original = From(temporary) ; }
    CastResidual(From& original_):original(original_) {}
  };

  template<typename From> struct CastResidual<From,From>
  {
    From& original;
    From& data() { return original; }
    CastResidual(From& original_):original(original_) {}
  };
}
