#include "Transport.h"

Transport::Transport()
{
}

void Transport::run_transport(int num_hist, Material& material, Estimator& est)
{
   //Start Transport
   for(int i = 0; i < num_hist; i++)
   {
      Particle p1((int)round(Urand()), 0.0, fRand(-1.0,1.0));
      pstack.push(p1);
      
      while(!pstack.empty())
      {
         Particle cp = pstack.top(); //cp = current particle   
         while(cp.alive)
         {   
            //Calculate distance to collision
            double d2c = -1/material.sigt.at(cp.group)*log(Urand()); //d2c = distance to collision
       	
            //Move particle and tally
            cp.move(d2c);
            est.tally_move(cp.group, d2c, material.v.at(cp.group));

            //Collide particle (collision handles tallies)
            if(!material.collision(cp,pstack,est))
            {
               cout << "Error in collision. Terminating" << endl;
               exit(1);         	 
            }
         }
         pstack.pop();
      }
   }
   return;
}
