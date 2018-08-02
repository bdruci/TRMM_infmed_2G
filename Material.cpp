#include "Material.h"

Material::Material(int num_groupsi, vector<double>& vi, vector<double>& sigti, vector<double>& sigci, vector<double>& sigsti, vector< vector<double> >& sigsi, vector<double>& sigfi, double nu_bari, vector<double>& chii): num_groups(num_groupsi), v(vi), sigt(sigti), sigc(sigci), sigst(sigsti), sigs(sigsi), nu_bar(nu_bari), sigf(sigfi), chi(chii)
{
   //CREATE CDF FOR REACTION SELECTION
   //


   //CREATE CDF FOR SCATTER
   for(int i = 0; i < num_groups; i++)
   {
	  double total = sigst.at(i);
	  double sum = 0;
	  vector<double> current_vector; 
	  for(int j = 0; j < num_groups; j++)
	  {
		 sum += sigs.at(i).at(j);
		 current_vector.push_back(sum / total);
	  }       
	  if(1.0 == Approx(sum / total)) //SET FINAL VALUE EQUAL TO 1, UNLESS THERE IS NO SCATTERING
	  {
		 current_vector.at(num_groups-1) = 1.0;
	  }
	  else if(total != 0.0)
	  {
		 cerr << "Scatter Cross Sections not configured properly.";
		 cerr << "Each row of Sigs must add up to the corresponding element of sigst" << endl;
		 exit(1);
	  }
	  scatter_cdf.push_back(current_vector); 
   }
}


bool Material::collision(Particle& p, stack<Particle>& pstack, Estimator& est)
{
   double randNum = fRand(0.0,1.0);
   if(randNum < (sigc.at(p.group) / sigt.at(p.group)))
   {
        if(capture(p, pstack, est))
           return true;
        else
        {
           cout << "Error in Capture. Exiting." << endl;
           exit(1);
        }
   }
   else if(randNum < ((sigc.at(p.group) + sigst.at(p.group)) / sigt.at(p.group)))
   {
        if(scatter(p, pstack, est))
           return true;
        else
        {
           cout << "Error in Scatter. Exiting." << endl;
           exit(1);
        }
   }
   else 
   {
        if(fission(p, pstack, est))
           return true;
        else
        {
           cout << "Error in Fission. Exiting." << endl;
           exit(1);
        }
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
   int g = p.group; //makes notation easier

   vector<double> sigsg = sigs.at(g);
   int dest_group = 0;
   double r = Urand();
   double total = 0;
   for( ; dest_group < num_groups ; dest_group++)
   {
      if(r < scatter_cdf.at(g).at(dest_group))
      {
         break;
      }
   }

   if(dest_group == num_groups)
      return false;
   
   est.tally_scatter(p.group, dest_group);
   p.group = dest_group;
   return true;
}

//REDO:
bool Material::fission(Particle& p, stack<Particle>& pstack, Estimator& est)
{
   //Check to see if particle is alive
   if(!p.alive)
      return false;
   
   //select number of particles to be created 
   int num_neutrons = (int)(nu_bar + Urand()); //TODO: MAKE INTO A PDF

   //Kill initial particle
   est.tally_fission(p.group);
   p.alive = false;

   //add new particles to the stack
   for(int i = 0; i < num_neutrons; i++) //TODO: CDF, COPY CONSTRUCTOR
   {
      double mu = fRand(-1.0,1.0); //isotropic
      int dest_group = -1;
      double total = 0;
      double r = fRand(0.0,1.0);
      for(int j = 0; j < num_groups; j++)
      {
         if((r > total) && ( r < (total + chi.at(j)) ) )
         {
            dest_group = j;
            break;
         }
         else
         {
            total += chi.at(j);
         }
      }
      if(dest_group < 0 || dest_group >= num_groups)
      {
         cout << "group destination not found" << endl;
         return false;
      }
      pstack.push(Particle(dest_group, p.x, mu));
      est.tally_emission(dest_group);
   }
   
   return true;
}
























