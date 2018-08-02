#ifndef __ESTIMATOR_H__
#define __ESTIMATOR_H__

#include <iostream>
#include <vector>

using namespace std;


class Estimator
//A class for keeping track of tallies in the infinite slab. Does not contain the cross sections. 
{
   public:
      //constructor
      Estimator(int, int, double);

      //variables
      int num_groups, num_hist, nu_bar, total_num_fissions;
      vector<double> length, time, num_collisions, num_captures, num_fissions, num_emissions;
      vector< vector<double> > num_scatters;

      //methods
      void tally_move(int cur_group, double dist, double v); 
      void tally_capture(int cur_group);
      void tally_scatter(int cur_group, int dest_group);
      void tally_fission(int cur_group);
      void tally_emission(int dest_group);

      void end_tally();
      void output();

   private:
      vector<double> p_collision, nu_p_fission, p_emission, inv_mean_time;
      vector< vector<double> > p_scatter;
      vector<double> vSigt, nu_vSigf, chi;
      vector< vector<double> > vSigs;
};



#endif
