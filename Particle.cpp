#include "Particle.h" 

Particle::Particle(int groupi, double xi, double mui): group(groupi), x(xi), mu(mui), alive(true) {}

bool Particle::move(double distance)
{
   if(alive)
   {
      x += distance * mu;
      return true;
   }
   return false;
}

void Particle::print_state()
{
   std::cout << "Alive: " << alive << ", x: " << x << ", mu: " << mu << ", group: " << group << std::endl;
}
