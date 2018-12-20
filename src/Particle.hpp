/*
 *  Author: Mario Lüder
 */
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <random>

class Particle
{
public:
   Particle();
   Particle(const double x, const double y, const double heading);

   void set(const double x, const double y, const double heading, const double weight);

   void print() const;

   double m_x;
   double m_y;
   double m_heading;
   double m_weight;
};

#endif // PARTICLE_HPP
