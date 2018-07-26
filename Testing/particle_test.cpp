#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>

#include "Catch.h"
#include "Particle.h"

TEST_CASE( "Particle", "[Particle]" )
{
   int group = 0;
   double x = 1.0;
   double mu = 0.5;
   
   Particle theParticle(group, x, mu);   

   // test properly moves the particle forwards
   SECTION( " move particle forward " )
   {
       theParticle.move(1.0);
       double result = 1.5;
       REQUIRE( theParticle.x == Approx( result ) );
   } 

   // test properly moves particle backwards
   SECTION( " move particle backward " )
   {
      theParticle.mu = -0.5;
      theParticle.move(1.0);
      double result = 0.5;
      REQUIRE( theParticle.x == Approx( result ) );
   }
}
     
