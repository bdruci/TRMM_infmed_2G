#ifndef __PARTICLE_H__
#define __PARTICLE_H__

#include <iostream>

class Particle
{
   public:
      Particle(int, double, double);
            
      Particle(const Particle&);
      int group;
      double x, mu;
      bool alive;

      bool move(double); //moves the particle a set distance
      void print_state(); //prints the state of the particle
};

#endif
