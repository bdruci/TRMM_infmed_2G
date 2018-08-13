#include "Distribution.h"


Distribution::Distribution(vector<double>& pdf) //ASSUMES ALREADY NORMALIZED
{
   num_elements = pdf.size();
   
   double sum = 0;
   for(int i = 0; i < num_elements; i++)
   {
      sum += pdf.at(i);
      cdf.push_back(sum);
      if(Approx(sum) == 1.0) //in case theres a zero distribution
      {
         cdf.at(i) = 1.0;
      } 
   }
}

Distribution::Distribution(vector<double>& values, double norm)
{
   num_elements = values.size();
   
   double sum = 0;
   for(int i = 0; i < num_elements; i++)
   {
      sum += values.at(i) / norm;
      cdf.push_back(sum);
      if(Approx(sum) == 1.0) //in case theres a zero distribution
      {
         cdf.at(i) = 1.0;
      } 
   }
}

int Distribution::sample()
{
   double r = Urand();

   for(int i = 0; i < num_elements; i++)
   {
      if(r < cdf.at(i))
         return i;
   }
}