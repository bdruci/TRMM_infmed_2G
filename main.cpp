#include <iostream>
#include <vector>
#include <stdlib.h>
#include <cmath>
#include <stack>
#include <memory> 
#include "Particle.h"
#include "InfSlab.h"
#include "Material.h"
#include "functions.h"

using namespace std;

typedef shared_ptr<Particle> P_ptr;

int main()
{
   //seed random num generator
   srand(1.0);
   
   //Problem parameters
   int numGroups = 2;

  
   int num_hist;
   cout << "Number of histories: ";
   cin >> num_hist;
   
     
   //Create material
   vector<double> Sigt, Sigc, Sigf, Sigs1, Sigs2, Sigst, chi; 
   Sigt.push_back(1.0);
   Sigt.push_back(1.0);
   Sigc.push_back(0.3);
   Sigc.push_back(0.4);
   Sigs1.push_back(0.2); //1->1
   Sigs1.push_back(0.4); //1->2
   Sigs2.push_back(0.0); //2->1
   Sigs2.push_back(0.3); //2->2
   Sigst.push_back(Sigs1.at(0) + Sigs1.at(1));
   Sigst.push_back(Sigs2.at(0) + Sigs2.at(1));   
   Sigf.push_back(0.1);
   Sigf.push_back(0.3);
   chi.push_back(1.0);
   chi.push_back(0.0);
   
   double nu_bar = 2.3;

   vector< vector<double> > Sigs;
   Sigs.push_back(Sigs1);
   Sigs.push_back(Sigs2);
   
   Material material(numGroups, Sigt, Sigc, Sigst, Sigs, Sigf, nu_bar, chi);
   
   //Create slab
   InfSlab slab(numGroups);
   
   //create particle stack 
   stack<P_ptr> pstack;
    
   //Start Transport
   for(int i = 0; i < num_hist; i++)
   {
      P_ptr p1 = make_shared<Particle>(0, 0.0, fRand(-1.0,1.0));
      pstack.push(p1);
      
      while(!pstack.empty())
      {
         P_ptr cp = pstack.top(); //cp = current particle         

         //Calculate distance to collision
         double d2c = -1/material.sigt.at(cp->group)*log(fRand(0.0,1.0)); //d2c = distance to collision
       	
         //Move particle and tally
         cp->move(d2c);
         slab.length.at(cp->group) += d2c;
         slab.time.at(cp->group)   += d2c; 
         //Collide particle (collision handles tallies)
         if(!material.collision(cp,slab,pstack))
         {
            cout << "Error in collision. Terminating" << endl;
            exit(1);         	 
         }
      }
   }
   
   cout << "Transport completed." << endl;
  
   cout << endl;

   cout << "RESULTS:" << endl; 
   for(int i = 0; i < numGroups; i++)
   {
      slab.time.at(i) /= num_hist;    
      slab.pColl.at(i) /= num_hist;
      slab.pFiss.at(i) /= num_hist;
      slab.pFiss.at(i) *= nu_bar;
      slab.pEmis.at(i) /= slab.num_fissions * nu_bar; 
      for(int j = 0; j < numGroups; j++)
      {
         slab.pScat.at(i).at(j) /= num_hist;
      }
   }
   cout << endl;
   cout << "vSigt:" << endl;
   for(int i = 0 ; i < numGroups; i++)
   {
      cout << "G" << i+1 << ": " << slab.pColl.at(i) / slab.time.at(i) << endl;
   }

   cout << endl;

   cout << "vgSigs:" << endl;
   for(int i = 0 ; i < numGroups; i++)
   {
      for(int j = 0; j < numGroups; j++)
      {
         cout << "G" << i+1 << "->" << j+1 << ": " << slab.pScat.at(i).at(j) / slab.time.at(i) << endl;
      }
   }

   cout << endl;

   cout << "nuvSigf:" << endl;
   for(int i = 0 ; i < numGroups; i++)
   {
      cout << "G" << i+1 << ": " << slab.pFiss.at(i) / slab.time.at(i) << endl;
   }
 
   cout << endl;

   cout << "chi:" << endl;
   for(int i = 0 ; i < numGroups; i++)
   {
      cout << "G" << i+1 << ": " << slab.pEmis.at(i) << endl;
   }

   cout << endl;

   cout << "Sigr: " << endl;
   for(int i = 0 ; i < numGroups; i++)
   {
      cout << "G" << i+1 << ": " << ( slab.pColl.at(i) - slab.pScat.at(i).at(i) ) / slab.time.at(i) << endl;
   }
   
  
   return 0;
}
