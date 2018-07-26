#include "functions.h"

double fRand(double fMin, double fMax)
{
   double f = (double)rand() / RAND_MAX;
   return fMin + f*(fMax-fMin);
}

std::vector<double> vecSum(std::vector<double> v1, std::vector<double> v2)
{
   std::vector<double> v3;
   for(unsigned int i = 0; i < v1.size(); i++)
   {
      v3.push_back(v1.at(i) + v2.at(i));
   }
   return v3;
}
