#ifndef __DISTRIBUTION_H__
#define __DISTRIBUTION_H__

#include <iostream>
#include <vector>
#include "Random.h"
#include "Catch.h"

using std::vector;

class Distribution
{
   public:
      Distribution(){}; //just so it can be used as a class variable
      Distribution(vector<double>& pdf); //If already normalized
      Distribution(vector<double>& values, double norm); //If not yet normalized. example: list of cross sections

      int sample(); //samples the distribution, returns the index 

   private:
      int num_elements;
      vector<double> cdf;


      
};


#endif