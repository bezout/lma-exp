
#include "rosenbrock.hpp"
#include "test_functors.hpp"

static_assert( 
	std::is_same<
				FunctorToParameters<F1,F2,rosenbrock>,
				...
			>,"");