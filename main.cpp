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
   int num_groups = 4;

  
   int num_hist;
   cout << "Number of histories: ";
   cin >> num_hist;
   
     
   //Create material
   vector<double> Sigt, Sigc, Sigf, Sigs1, Sigs2, Sigs3, Sigs4, Sigst, chi, v, nu; 

   Sigt.push_back(1.0);
   Sigt.push_back(1.0);
   Sigt.push_back(1.0);
   Sigt.push_back(1.0);

   Sigc.push_back(0.4);
   Sigc.push_back(0.4);
   Sigc.push_back(0.4);
   Sigc.push_back(0.6);


   Sigs1.push_back(0.1); //1->1
   Sigs1.push_back(0.4); //1->2
   Sigs1.push_back(0.0); //1->3
   Sigs1.push_back(0.0); //1->4

   Sigs2.push_back(0.0); //2->1
   Sigs2.push_back(0.1); //2->2
   Sigs2.push_back(0.4); //2->3
   Sigs2.push_back(0.0); //2->4

   Sigs3.push_back(0.0); //3->1
   Sigs3.push_back(0.0); //3->2
   Sigs3.push_back(0.1); //3->3
   Sigs3.push_back(0.4); //3->4

   Sigs4.push_back(0.0); //4->1
   Sigs4.push_back(0.0); //4->2
   Sigs4.push_back(0.0); //4->3
   Sigs4.push_back(0.1); //4->4

   Sigst.push_back(Sigs1.at(0) + Sigs1.at(1) + Sigs1.at(2) + Sigs1.at(3));
   Sigst.push_back(Sigs2.at(0) + Sigs2.at(1) + Sigs2.at(2) + Sigs2.at(3));
   Sigst.push_back(Sigs3.at(0) + Sigs3.at(1) + Sigs3.at(2) + Sigs3.at(3));
   Sigst.push_back(Sigs4.at(0) + Sigs4.at(1) + Sigs4.at(2) + Sigs4.at(3));

   Sigf.push_back(0.1);
   Sigf.push_back(0.1);
   Sigf.push_back(0.1);
   Sigf.push_back(0.3);

   chi.push_back(1.0);
   chi.push_back(0.0);
   chi.push_back(0.0);
   chi.push_back(0.0);

   v.push_back(1.0);
   v.push_back(0.1);
   v.push_back(0.01);
   v.push_back(0.001);

   nu.push_back(0.0); //TODO: make this a proper distribution for neutrons
   nu.push_back(0.0);
   nu.push_back(0.5);
   nu.push_back(0.5);
   double nu_bar = 2.5;

   vector< vector<double> > Sigs;
   Sigs.push_back(Sigs1);
   Sigs.push_back(Sigs2);
   Sigs.push_back(Sigs3);
   Sigs.push_back(Sigs4);
   
   Material material(num_groups, v, Sigt, Sigc, Sigst, Sigs, Sigf, nu, nu_bar, chi);
   
   //Create estimator
   Estimator est(num_groups, num_hist, nu_bar); 
   
   Transport transport;

   transport.run_transport(num_hist, material, est);

   cout << "Transport completed." << endl;
   cout << endl;

   est.end_tally();
   est.output();

   return 0;
}