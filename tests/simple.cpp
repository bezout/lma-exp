int main()
{
  
/*
  test_static(LM<double>{nb_iteration,1.});
  test_dynamic(LM<double>{nb_iteration,1.});
  test_static(LM<float>{nb_iteration,1.f});
  test_dynamic(LM<float>{nb_iteration,1.f});
  
  test_static(LMN<double>{nb_iteration,1.});
  test_dynamic(LMN<double>{nb_iteration,1.});
  test_static(LMN<float>{nb_iteration,1.f});
  test_dynamic(LMN<float>{nb_iteration,1.f});
*/

}

// float,double
// dynamic,static
// LM,LMN


/*
 *  PLAN :
 *   TOUT FAIRE EN DENSE
 *   avec n/m statique ou dynamique
 *   1 : n instances d'1 type d'erreur pour 1 instance d'1 type de paramètre
 *   2 : n instances d'1 type d'erreur pour m instances d'1 type de paramètre
 *   3 : n[...] instances de N types d'erreur pour m instances d'1 type de paramètre
 *   4 : n[...] instances de N types d'erreur pour m[...] instances de M types de paramètre
 * 
 *   PUIS EN EPARSE
 * 
 * 
 * update_policy ?
 */

// reset && time g++-5 simple_lma.cpp -std=c++1y -I/home/datta/develop/root/include/eigen3 -isystem/home/datta/develop/root/include/eigen3 -lboost_system -lboost_chrono && ./a.out
