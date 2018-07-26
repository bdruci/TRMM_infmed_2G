#include "InfSlab.h"

InfSlab::InfSlab(int num_groupsi): num_groups(num_groupsi)
{
      num_fissions = 0;
      for(int i = 0; i < num_groups; i++)
      {
         length.push_back(0);
         time.push_back(0);
         pColl.push_back(0);		
         pFiss.push_back(0);
         pCap.push_back(0);
         pEmis.push_back(0);
         vector<double> scattemp;
         for(int j = 0; j < num_groups; j++)
         {
            scattemp.push_back(0);
         }				   
         pScat.push_back(scattemp);
      }
}
