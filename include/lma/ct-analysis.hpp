#pragma once

namespace lma
{
  template<typename> struct AnalyseExtractFromType;
  
  template<typename Return, typename F, typename P, typename R> struct AnalyseExtractFromType< Return (F::*) (const P&, R&) const >
  {
    typedef P Parameters;
    typedef R Residual;
  };

  template<typename F> struct AnalyseFunctor : AnalyseExtractFromType<decltype(&F::operator())> {};
}
