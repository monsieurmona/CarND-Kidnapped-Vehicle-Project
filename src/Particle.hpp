/*
 *  Author: Mario Lüder
 */
#ifndef PARTICLE_HPP
#define PARTICLE_HPP

// system includes
#include <random>

// local includes
#include "Coordinate2D.hpp"

class Particle
{
public:
   Particle();
   Particle(const double x, const double y, const double heading);

   void set(const double x, const double y, const double heading, const double weight);

   /**
    * @brief provides coordinates
    * @return 2D coordinates
    */
   inline Coordinate2D getCoordinates2D() const { return Coordinate2D(m_x, m_y); }

   void print() const;

   double m_x;
   double m_y;
   double m_heading;
   double m_weight;
};

#endif // PARTICLE_HPP
