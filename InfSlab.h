#ifndef __INFSLAB_H__
#define __INFSLAB_H__


#include <vector>

using namespace std;


class InfSlab
//A class for keeping track of tallies in the infinite slab. Does not contain the cross sections. 
{
   public:
      //constructor
      InfSlab(int);

      //variables
      int num_groups, num_fissions;
      vector<double> length; //vector in energy groups for the total distance particles traveled in this slab 
      vector<double> time;  //" time particles travel "
      vector<double>           pColl; //probability of a collision in group g 
      vector<double>           pCap;
      vector< vector<double> > pScat; //probability of a scatter in group g to group g', GxG.(( p1->1, p2->1 ),( p2->1, p2->2)) in 2 groups
      vector<double>           pFiss; //probability of a fission in group g
	 vector<double>           pEmis; //probability that a fission causes an emission to group g

};



#endif
