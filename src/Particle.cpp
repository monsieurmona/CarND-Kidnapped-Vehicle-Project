/*
 *  Author: Mario Lüder
 */
#include <iostream>
#include <random>

#include "Particle.hpp"


Particle::Particle()
{
   // don't initialize on purpose
   // as we don't want to waste time
}

Particle::Particle(double x, double y, double heading)
   : m_x(x)
   , m_y(y)
   , m_heading(heading)
   , m_weight(1.0)
{
}

void Particle::set(const double x, const double y, const double heading, const double weight)
{
   m_x = x;
   m_y = y;
   m_heading = heading;
   m_weight = weight;
}

void Particle::print() const
{
   using namespace std;
   cout << "Particle: x:" << m_x << " y:" << m_y << " h:" << m_heading << " w:" << m_weight;
}
