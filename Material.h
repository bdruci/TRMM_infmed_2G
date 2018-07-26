#ifndef __MATERIAL_H__
#define __MATERIAL_H__

#include <iostream>
#include <vector>
#include <stack>
#include "InfSlab.h"
#include "Particle.h"
#include "functions.h"
#include <memory>

using std::vector;
using std::stack;
using std::shared_ptr;
using std::make_shared;

typedef shared_ptr<Particle> P_ptr;

class Material
//A class containing the material cross section to be used inside transport.
//Also contains methods to determine what happens to a particle after a collision
{
   public:
      //Constructor
      Material(int, vector<double>&, vector<double>&, vector<double>&, vector< vector<double> >&, vector<double>&, double, vector<double>&);
      
      //Variables
      int num_groups; //number of energy groups
      vector<double> sigt, sigc, sigst, sigf, chi; //total xs, capture xs, total scatter xs, fission xs
      vector< vector<double> > sigs;  //Scatter matrix. sigs.at(i) = [ sigsi->1, sigsi->2, ..., sigsi->G]
      double nu_bar; //average number of neutrons created per fission

      //Methods
      bool collision(P_ptr, InfSlab&, stack<P_ptr>&);
      //PURPOSE: Handles the collision of a particle in a slab
      //MODIFIES: p, slab, pstack
      //RETURNS: true if particle was collided successfully, false if there was an error

      bool capture(P_ptr, InfSlab&, stack<P_ptr>&);
      //PURPOSE: Handles the capture of a particle
      //MODIFIES: p, pstack
      //RETURNS: true if particle was successfully captured, false if particle could not be captured

      bool scatter(P_ptr, InfSlab&, stack<P_ptr>&);
      //PURPOSE: Handles the scatter, updates tallies if successful
      //MODIFIES: p, slab
      //RETURNS: true if particle was successfully scattered, false if particle could not be scattered

      bool fission(P_ptr, InfSlab&, stack<P_ptr>&);
      //PURPOSE: Handles fission, updates tallies if successful. Kills particle, adds fission products to stack
      //MODIFIES: p, slab, pstack
      //RETURNS: false if not successful

};



#endif
