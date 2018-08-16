#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>

#include "Catch.h"
#include "Estimator.h"

TEST_CASE( "Estimator", "[Estimator]" )
{
   int num_groups = 2;
   int num_hist = 10;
   double nu_bar = 2.3;


   Estimator est(num_groups, num_hist, nu_bar);

   // test detects that the estimator is properly tallying distance
   SECTION( " the estimator properly tallies a moved particle's distance " )
   {
       est.tally_move(0,1.0,1.0);
       REQUIRE(Approx(est.length.at(0)) == 1.0);
   } 

   // test detects that the estimator is properly tallying time
   SECTION( " the estimator properly tallies a moved particle's distance " )
   {
       est.tally_move(0,1.0,0.1);
       REQUIRE(Approx(est.time.at(0)) == 10.0);
   } 
}
