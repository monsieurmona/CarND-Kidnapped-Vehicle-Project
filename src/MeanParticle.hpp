/*
 *  Author: Mario Lüder
 */
#ifndef MEANPARTICLE_HPP
#define MEANPARTICLE_HPP

// system includes
#include <random>

// local includes
#include "Particle.hpp"

// foward declaration
class StandardDeviationPosition;

class MeanParticle
{
public:
   MeanParticle(const Particle & particle, const StandardDeviationPosition & std);
   inline Particle sampleParticle() { return Particle(getNdX(), getNdY(), getNdHeading()); }
   inline Particle operator()() { return sampleParticle(); }

private:
   using NormDist = std::normal_distribution<double>;

   inline double getNdX() { return m_ndX(m_gen); }
   inline double getNdY() { return m_ndY(m_gen); }
   inline double getNdHeading() { return m_ndHeading(m_gen); }

   std::default_random_engine m_gen;

   NormDist m_ndX;
   NormDist m_ndY;
   NormDist m_ndHeading;

   Particle m_position;
};

#endif // MEANPARTICLE_HPP
