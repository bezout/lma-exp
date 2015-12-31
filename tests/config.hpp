#pragma once

namespace lma
{
  using LM_POLICIES = brigand::list<LM<float>,LMN<float>>;

  using FLOATING_POINT = brigand::list<float,double>;

  using VERBOSES = brigand::list<DefaultVerbose,Verbose>;//,VerboseNormalEquation>;

  using CONFIGS = brigand::list<VERBOSES,LM_POLICIES,FLOATING_POINT>;
}
