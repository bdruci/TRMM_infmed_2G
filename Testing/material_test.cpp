#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>

#include "Catch.h"
#include "Material.h"

TEST_CASE( "Material (pure absorber)", "[Material]" )
{
   int num_groups = 2;

   int group = 0;
   double x = 1.0;
   double mu = 0.5;
   
   Particle theParticle(group, x, mu);   
   
   stack<Particle> pstack;
   
   pstack.push(theParticle);   

   Estimator est(num_groups, 1, 2.3); 

   vector<double> sigt, sigc, sigf, sigst, chi, v;
   vector< vector<double> > sigs; 
   double nu_bar = 2.3;

   sigt.push_back(1.0);
   sigt.push_back(1.0);

   sigc.push_back(1.0);
   sigc.push_back(1.0);

   sigst.push_back(0.0);
   sigst.push_back(0.0);

   sigf.push_back(0.0);
   sigf.push_back(0.0);

   chi.push_back(1.0);
   chi.push_back(0.0);

   v.push_back(1.0);
   v.push_back(1.0);

   vector<double> sigs1, sigs2;
   
   sigs1.push_back(0.0);
   sigs1.push_back(0.0);
   sigs2.push_back(0.0);
   sigs2.push_back(0.0);

   sigs.push_back(sigs1);
   sigs.push_back(sigs2);

   Material theMaterial(num_groups,v, sigt, sigc, sigst, sigs, sigf, nu_bar, chi);
   
   
   
   // test detects that the particle is dead
   SECTION( " fast neutrons in a pure absorber are killed after a collision " )
   {
       theMaterial.collision(theParticle, pstack, est);
       REQUIRE( theParticle.alive == false );
   } 

   // test detects that the particle is dead
   SECTION( " slow neutrons in a pure absorber absorb " )
   {
      theParticle.group = 1;
      theMaterial.collision(theParticle, pstack, est);
      REQUIRE( theParticle.alive == false );
   }

}
