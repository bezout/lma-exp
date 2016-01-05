#include <lma/bundle.hpp>
#include "rosenbrock.hpp"
#include <brigand/brigand.hpp>
#include "test_functors.hpp"

using namespace lma;





int main()
{
	/*

	Parameters p;
	double d = 0;
	Bundle<Functor(Rosenbrock,Int<-1>),Functor(F1,Int<-1>),Functor(F2,Int<-1>)> bundle;
	bundle.add(F1{},&d).add(Rosenbrock{0},&p).add(F2{},&d);
	*/

	std::tuple<double,F1,F2,Rosenbrock> tuple;

	std::cout << " -> " << name<decltype(find(tuple,IsSame<double>{}))>() << std::endl;
	std::cout << " -> " << name<decltype(find(tuple,IsSame<F1>{}))>() << std::endl;
	std::cout << " -> " << name<decltype(find(tuple,IsSame<F2>{}))>() << std::endl;
	std::cout << " -> " << name<decltype(find(tuple,IsSame<Rosenbrock>{}))>() << std::endl;


	std::tuple<
							Container<std::tuple<F1,int,int>,-1>,
							Container<std::tuple<F2,int,int>,-1>,
							Container<std::tuple<Rosenbrock,int,int>,-1>
	> tuple2;

	std::cout << " -> " << name<decltype(find(tuple2,FindByFirst<F1>{}))>() << std::endl;
	std::cout << " -> " << name<decltype(find(tuple2,FindByFirst<F2>{}))>() << std::endl;
	std::cout << " -> " << name<decltype(find(tuple2,FindByFirst<Rosenbrock>{}))>() << std::endl;
	
}