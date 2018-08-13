#include "Material.h"

Material::Material(int num_groupsi, vector<double>& vi, vector<double>& sigti, vector<double>& sigci, vector<double>& sigsti, vector< vector<double> >& sigsi, vector<double>& sigfi, vector<double>& nui, double nu_bari, vector<double>& chii): num_groups(num_groupsi), v(vi), sigt(sigti), sigc(sigci), sigst(sigsti), sigs(sigsi), nu(nui), nu_bar(nu_bari), sigf(sigfi), chi(chii)
{
   //CREATE CDFs FOR REACTION SELECTION, SCATTER, CHI AND NU
   for(int i = 0; i < num_groups; i++)
   {
      vector<double> rxn_xs;
      rxn_xs.push_back(sigc.at(i));
      rxn_xs.push_back(sigst.at(i));
      rxn_xs.push_back(sigf.at(i));
      reaction_dist.push_back(Distribution(rxn_xs,sigt.at(i)));

      scatter_dist.push_back(Distribution(sigs.at(i),sigst.at(i))); 
   }
   
   chi_dist = Distribution(chi);
   nu_dist  = Distribution(nu); 
}


bool Material::collision(Particle& p, stack<Particle>& pstack, Estimator& est)
{
   int index = reaction_dist.at(p.group).sample();
   if(index == 0)
   {
        if(capture(p, pstack, est))
           return true;
        else
        {
           cout << "Error in Capture. Exiting." << endl;
           exit(1);
        }
   }
   else if(index == 1)
   {
        if(scatter(p, pstack, est))
           return true;
        else
        {
           cout << "Error in Scatter. Exiting." << endl;
           exit(1);
        }
   }
   else if(index == 2)
   {
        if(fission(p, pstack, est))
           return true;
        else
        {
           cout << "Error in Fission. Exiting." << endl;
           exit(1);
        }
   }
   else
   {
      cerr << "Error in Material::Collision. Index not found. Index was " << index << "." << endl;
      cerr << "Exiting..." << endl;
      exit(1);
   }
}

bool Material::capture(Particle& p, stack<Particle>& pstack, Estimator& est)
{
   if(!p.alive)
      return false;
   else
   {
      est.tally_capture(p.group);
      p.alive = 0;
      return true;   
   }

}

bool Material::scatter(Particle& p, stack<Particle>& pstack, Estimator& est)
{
   if(!p.alive)
      return false;
   
   //scatter the angle isotropically
   p.mu = fRand(-1.0,1.0);
   

   //select destination energy
   int dest_group = scatter_dist.at(p.group).sample();

   if(dest_group >= num_groups || dest_group < 0)
      return false;
   
   est.tally_scatter(p.group, dest_group);
   p.group = dest_group;
   return true;
}

bool Material::fission(Particle& p, stack<Particle>& pstack, Estimator& est)
{
   //Check to see if particle is alive
   if(!p.alive)
      return false;
   
   est.tally_fission(p.group);

   //select number of particles to be created 
   int num_neutrons = nu_dist.sample();

   if(num_neutrons == 0)
   {
      p.alive == false; 
      return true;
   }

   //remove initial particle
   pstack.pop();
 

   //add new particles to the stack
   for(int i = 0; i < num_neutrons-1; i++) //use the already made particle as last fission particle
   {
      Particle new_p = p;

      //find destination group, pick random direction isotropically
      new_p.group = chi_dist.sample();
      new_p.mu = fRand(-1.0, 1.0);
      
      est.tally_emission(new_p.group);
      
      pstack.push(new_p); 
   }

   //find destination group, pick random direction isotropically
   p.group = chi_dist.sample();
   p.mu = fRand(-1.0, 1.0);
      
   est.tally_emission(p.group);
      
   pstack.push(p);
   return true;
}
























