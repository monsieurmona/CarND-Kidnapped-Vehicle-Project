/*
 *  Author: Mario Lüder
 */
#include "MeanParticle.hpp"
#include "StandardDeviationPosition.hpp"

MeanParticle::MeanParticle(const Particle & particle, const StandardDeviationPosition & std)
   : m_ndX(particle.m_x, std.getStdX())
   , m_ndY(particle.m_y, std.getStdY())
   , m_ndHeading(particle.m_heading, std.getStdHeading())
   , m_position(particle)
{
}
