#ifndef __TRANSPORT_H__
#define __TRANSPORT_H__


#include <iostream>
#include <vector>
#include <stack>
#include "Estimator.h"
#include "Particle.h"
#include "functions.h"
#include "Catch.h"
#include "Material.h"

class Transport
{
   public:
      //constructor
      Transport();

      //methods
      void run_transport(int num_hist, Material&, Estimator&);

      //variables
      stack<Particle> pstack; 


};

#endif