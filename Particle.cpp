#include "Particle.h" 

Particle::Particle(int groupi, double xi, double mui): group(groupi), x(xi), mu(mui), alive(true) {}

Particle::Particle(const Particle& old_p)
{
   x = old_p.x;
   mu = old_p.mu;
   group = old_p.group;
   alive = old_p.alive;
}
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
