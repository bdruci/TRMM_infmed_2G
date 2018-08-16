#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <limits>

#include "Catch.h"
#include "Transport.h"

TEST_CASE( "Transport (pure absorber)", "[Transport]" )
{
   int num_groups = 2;
   
   Transport transport;

   int group = 0;
   double x = 1.0;
   double mu = 0.5;
   
   for(int i = 0; i < 100; i++)
   { 
      transport.pstack.push(Particle(group,x,mu));
   }
   

   Estimator est(num_groups, 1, 2.3); 

   vector<double> sigt, sigc, sigf, sigst, chi, v, nu;
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
 
   nu.push_back(0.0);
   nu.push_back(1.0);

   Material theMaterial(num_groups,v, sigt, sigc, sigst, sigs, sigf, nu, nu_bar, chi);

 

   // test detects that the particle stack is empty
   SECTION( " the transport routine runs until the particle stack is empty " )
   {
       transport.run_transport(1, theMaterial, est);
       REQUIRE( transport.pstack.size() == 0 );
   } 


   
}
