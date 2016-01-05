#pragma once

#include <tuple>

namespace lma
{
	template<typename X> struct IsSame
	{
		template<typename Y> struct Compare
		{
			using type = std::is_same<X,Y>;
		};
	};

	template<int I, typename Tuple, typename Pred>
	constexpr auto __find(Tuple& tuple, Pred, std::true_type)
	{
		return std::get<I-1>(tuple);
	}

	template<int I, typename Tuple, typename Pred>
	constexpr auto __find(Tuple& tuple, Pred pred, std::false_type)
	{
		using Current = typename std::tuple_element<I,Tuple>::type;
		using Result = typename Pred::template Compare<Current>::type;
		return __find<I+1>(tuple,pred,Result{});
	}


	template<typename Tuple, typename Pred>
	constexpr auto find(Tuple& tuple, Pred pred)
	{
		return __find<0>(tuple,pred, std::false_type{});
	}

	template<typename> struct first_element;


	template<typename X> struct FindByFirst
	{
		template<typename Y> struct Compare
		{
			using type = typename std::is_same<X,typename first_element<Y>::type>::type;
		};
	};

	template<typename F>
  constexpr auto find_by_first_element(auto& tuple)
  {
    return __find<0>(tuple,FindByFirst<F>{});
  }

}