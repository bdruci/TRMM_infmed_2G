#include "Material.h"

Material::Material(int num_groupsi, vector<double>& sigti, vector<double>& sigci, vector<double>& sigsti, vector< vector<double> >& sigsi, vector<double>& sigfi, double nu_bari, vector<double>& chii): num_groups(num_groupsi), sigt(sigti), sigc(sigci), sigst(sigsti), sigs(sigsi), nu_bar(nu_bari), sigf(sigfi), chi(chii)
{
}


bool Material::collision(P_ptr p, InfSlab& slab, stack<P_ptr>& pstack)
{
   slab.pColl.at(p->group) += 1;
   
   double randNum = fRand(0.0,1.0);
   if(randNum < (sigc.at(p->group) / sigt.at(p->group)))
   {
        if(capture(p, slab, pstack))
           return true;
        else
        {
           cout << "Error in Capture. Exiting." << endl;
           exit(1);
        }
   }
   else if(randNum < ((sigc.at(p->group) + sigst.at(p->group)) / sigt.at(p->group)))
   {
        if(scatter(p, slab, pstack))
           return true;
        else
        {
           cout << "Error in Scatter. Exiting." << endl;
           exit(1);
        }
   }
   else 
   {
        if(fission(p, slab, pstack))
           return true;
        else
        {
           cout << "Error in Fission. Exiting." << endl;
           exit(1);
        }
   }
}

bool Material::capture(P_ptr p, InfSlab& slab, stack<P_ptr>& pstack)
{
   if(p->alive == false)
      return false;
   else
   {
      slab.pCap.at(p->group) += 1;
      p->alive = 0;
      pstack.pop();
      return true;   
   }

}

bool Material::scatter(P_ptr p, InfSlab& slab, stack<P_ptr>& pstack)
{
   if(!p->alive)
      return false;
   
   //scatter the angle isotropically
   p->mu = fRand(-1.0,1.0);
   

   //select destination energy
   int g = p->group; //makes notation easier

   vector<double> sigsg = sigs.at(g);
   int dest_group = -1;
   double r = sigst.at(g)*fRand(0.0, 1.0);
   double total = 0;
   for(int i = 0; i < num_groups; i++)
   {
      if(r > total && r < (total + sigsg.at(i)))
      {
         dest_group = i;
      }
      total = total + sigsg.at(i);
   }

   if(dest_group == -1)
      return false;
   
   slab.pScat.at(g).at(dest_group) += 1;
   p->group = dest_group;
   return true;
}

bool Material::fission(P_ptr p, InfSlab& slab, stack<P_ptr>& pstack)
{
   //Check to see if particle is alive
   if(!p->alive)
      return false;
   
   //select number of particles to be created 
   int num_neutrons = (int)(nu_bar + fRand(0.0, 1.0));

   //Kill initial particle
   slab.num_fissions += 1;
   slab.pFiss.at(p->group) += 1;
   p->alive = false;
   pstack.pop();

   //add new particles to the stack
   for(int i = 0; i < num_neutrons; i++)
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
      pstack.push(make_shared<Particle>(dest_group, p->x, mu));
      slab.pEmis.at(dest_group) += 1;
   }
   
   return true;
}
























