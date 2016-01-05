#include "rosenbrock.hpp"

#include "lma/solver.hpp"

using namespace lma;

int main()
{
  Parameters parameters {0.9,0.9};
  Solver<Functors(Rosenbrock)>()
    .add(Rosenbrock{1},&parameters)
    .add(Rosenbrock{2},&parameters)
    .add(Rosenbrock{3},&parameters)
    .solve(LMN<double>{5,1.},Verbose{});
}