#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <stack>
#include <memory> 
#include "Particle.h"
#include "Estimator.h"
#include "Material.h"
#include "functions.h"
#include "Transport.h"

using namespace std;

int main()
{ 
   //Problem parameters
   int num_groups = 2;

  
   int num_hist;
   cout << "Number of histories: ";
   cin >> num_hist;
   
     
   //Create material
   vector<double> Sigt, Sigc, Sigf, Sigs1, Sigs2, Sigst, chi, v; 
   Sigt.push_back(1.0);
   Sigt.push_back(1.0);
   Sigc.push_back(0.3);
   Sigc.push_back(0.4);
   Sigs1.push_back(0.1); //1->1
   Sigs1.push_back(0.6); //1->2
   Sigs2.push_back(0.1); //2->1
   Sigs2.push_back(0.5); //2->2
   Sigst.push_back(Sigs1.at(0) + Sigs1.at(1));
   Sigst.push_back(Sigs2.at(0) + Sigs2.at(1));   
   Sigf.push_back(0.0);
   Sigf.push_back(0.0);
   chi.push_back(1.0);
   chi.push_back(0.0);
   v.push_back(2.0);
   v.push_back(0.1);
   
   double nu_bar = 2.3;

   vector< vector<double> > Sigs;
   Sigs.push_back(Sigs1);
   Sigs.push_back(Sigs2);
   
   Material material(num_groups, v, Sigt, Sigc, Sigst, Sigs, Sigf, nu_bar, chi);
   
   //Create slab
   Estimator est(num_groups, num_hist, nu_bar); //TODO: Change name of InfSlab to estimator
   
   Transport transport;

   transport.run_transport(num_hist, material, est);

   cout << "Transport completed." << endl;
   cout << endl;

   est.end_tally();
   est.output();

   return 0;
}
