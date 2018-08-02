#include "Estimator.h"

Estimator::Estimator(int num_groupsi, int num_histi, double nu_bari): num_groups(num_groupsi), num_hist(num_histi), nu_bar(nu_bari)
{
      total_num_fissions = 0;
      for(int i = 0; i < num_groups; i++)
      {
         length.push_back(0);
         time.push_back(0);
         num_collisions.push_back(0);		
         num_captures.push_back(0);
         num_fissions.push_back(0);
         num_emissions.push_back(0);
         vector<double> scattemp;
         for(int j = 0; j < num_groups; j++)
         {
            scattemp.push_back(0);
         }				   
         num_scatters.push_back(scattemp);
      }
}

void Estimator::tally_move(int cur_group, double dist, double v)
{
   if(cur_group < 0 || cur_group >= num_groups)
   {
      cerr << "Error in Estimator::tally_move. Group must be an integer in [ 0,  ";
      cerr << num_groups << " )." << endl;
      cerr << "The group you submitted was " << cur_group << endl; 
      cerr << "Exiting..." << endl;
      exit(1);
   }
   if(dist <= 0 || v <= 0)
   {
      cerr << "Error in Estimator::tally_move. Distance and speed must be non-zero and positive." << endl;
      cerr << "Distance submitted: " << dist << ", Speed submitted: " << v << endl;
      cerr << "Exiting..." << endl;
      exit(1);
   }

   length.at(cur_group) += dist;
   time.at(cur_group)   += dist / v; 
   return;
}
  
void Estimator::tally_capture(int cur_group)
{
   if(cur_group < 0 || cur_group >= num_groups)
   {
      cerr << "Error in Estimator::tally_capture. Group must be an integer in [ 0,  ";
      cerr << num_groups << " )." << endl;
      cerr << "The group you submitted was " << cur_group << endl; 
      cerr << "Exiting..." << endl;
      exit(1);
   }
   
   num_collisions.at(cur_group) += 1;
   num_captures.at(cur_group)   += 1;
   return;
}

void Estimator::tally_scatter(int cur_group, int dest_group)
{
   if((cur_group < 0 || cur_group >= num_groups) || (dest_group < 0 || dest_group >= num_groups))
   {
      cerr << "Error in Estimator::tally_scatter. Group must be an integer in [ 0,  ";
      cerr << num_groups << " )." << endl;
      cerr << "The groups you submitted was cur_group: " << cur_group << ", dest_group: " << dest_group << endl; 
      cerr << "Exiting..." << endl;
      exit(1);
   }

   num_collisions.at(cur_group) += 1;
   num_scatters.at(cur_group).at(dest_group) += 1;
}

void Estimator::tally_fission(int cur_group)
{
   if(cur_group < 0 || cur_group >= num_groups)
   {
      cerr << "Error in Estimator::tally_fission. Group must be an integer in [ 0,  ";
      cerr << num_groups << " )." << endl;
      cerr << "The group you submitted was " << cur_group << endl; 
      cerr << "Exiting..." << endl;
      exit(1);
   }
   
   num_collisions.at(cur_group) += 1;
   num_fissions.at(cur_group) += 1;
}

void Estimator::tally_emission(int dest_group)
{
   if(dest_group < 0 || dest_group >= num_groups)
   {
      cerr << "Error in Estimator::tally_emission. Group must be an integer in [ 0,  ";
      cerr << num_groups << " )." << endl;
      cerr << "The group you submitted was " << dest_group << endl; 
      cerr << "Exiting..." << endl;
      exit(1);
   }

   num_emissions.at(dest_group) += 1;
   total_num_fissions += 1;
}

void Estimator::end_tally()
{
   for(int i = 0; i < num_groups; i++)
   {
      p_collision.push_back(num_collisions.at(i) / num_hist);
      nu_p_fission.push_back(num_fissions.at(i) * nu_bar / num_hist);
      p_emission.push_back(num_emissions.at(i) / total_num_fissions);
      inv_mean_time.push_back(num_hist / time.at(i));
      vector<double> temp;
      for(int j = 0; j < num_groups; j++)
      {
         temp.push_back(num_scatters.at(i).at(j) / num_hist);
      }
      p_scatter.push_back(temp);
   }

   for(int i = 0; i < num_groups; i++)
   {
      double imt = inv_mean_time.at(i);
      vSigt.push_back(p_collision.at(i) * imt);
      nu_vSigf.push_back(nu_p_fission.at(i) * imt);
      chi.push_back(p_emission.at(i));
      vector<double> temp;
      for(int j = 0; j < num_groups; j++)
      {
         temp.push_back(p_scatter.at(i).at(j) * imt);
      }
      vSigs.push_back(temp);
   }

   //CALC TRMM
   for(int i = 0; i < num_groups; i++)
   {
      vector<double> trmm_row;
      for(int j = 0; j < num_groups; j++)
      {
         trmm_row.push_back(nu_vSigf.at(i)*chi.at(j));
         trmm_row.at(j) += vSigs.at(i).at(j);
         if(i == j)
            trmm_row.at(j) -= vSigt.at(j);
      }    
      trmm.push_back(trmm_row);
   } 
}

void Estimator::output()
{
   cout << "vSigt:" << endl;
   for(int i = 0 ; i < num_groups; i++)
   {
      cout << "G" << i+1 << ": " << vSigt.at(i) << endl;
   }

   cout << endl;

   cout << "vgSigs:" << endl;
   for(int i = 0 ; i < num_groups; i++)
   {
      for(int j = 0; j < num_groups; j++)
      {
         cout << "G" << i+1 << "->" << j+1 << ": " << vSigs.at(i).at(j) << endl;
      }
   }

   cout << endl;

   cout << "nu_vSigf:" << endl;
   for(int i = 0 ; i < num_groups; i++)
   {
      cout << "G" << i+1 << ": " << nu_vSigf.at(i) << endl;
   }
 
   cout << endl;

   cout << "chi:" << endl;
   for(int i = 0 ; i < num_groups; i++)
   {
      cout << "G" << i+1 << ": " << chi.at(i) << endl;
   }

   cout << endl;

   cout << "TRMM:" << endl;
   for(int i = 0 ; i < num_groups; i++)
   {
      for(int j = 0; j < num_groups; j++)
      {
         cout << trmm.at(i).at(j) << " ";
      }
      cout << endl;
   }
}