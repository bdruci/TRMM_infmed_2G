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
   
   shared_ptr<Particle> theParticle = make_shared<Particle>(group, x, mu);   
   
   stack< shared_ptr<Particle> > pstack;
   
   pstack.push(theParticle);   

   InfSlab slab(num_groups); 

   vector<double> sigt, sigc, sigf, sigst, chi;
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

   vector<double> sigs1, sigs2;
   
   sigs1.push_back(0.0);
   sigs1.push_back(0.0);
   sigs2.push_back(0.0);
   sigs2.push_back(0.0);

   sigs.push_back(sigs1);
   sigs.push_back(sigs2);

   Material theMaterial(num_groups, sigt, sigc, sigst, sigs, sigf, nu_bar, chi);
   
   
   
   // test detects that the particle is dead
   SECTION( " fast neutrons in a pure absorber are killed after a collision " )
   {
       theMaterial.collision(theParticle, slab, pstack);
       REQUIRE( theParticle->alive == false );
   } 

   // test detects that the particle is dead
   SECTION( " slow neutrons in a pure absorber absorb " )
   {
      theParticle->group = 1;
      theMaterial.collision(theParticle, slab, pstack);
      REQUIRE( theParticle->alive == false );
   }

}
