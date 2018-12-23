/*
 *  Author: Mario Lüder
 */

// system includes
#include <math.h>

// local includes
#include "MotionModel.hpp"
#include "Particle.hpp"

MotionModel::MotionModel(const double deltaTinS, const double velocity, const double yawRate, const StandardDeviationPosition & std)
   : m_deltaTinS(deltaTinS)
   , m_velocity(velocity)
   , m_yawRate(yawRate)
   , m_std(std)
{
}

Particle MotionModel::operator()(const Particle & particle) const
{
   Particle movedParticle;

   // for convinience to make the formulars more comprehensible
   const double x0 = particle.m_x;
   const double y0 = particle.m_y;
   const double thetha0 = particle.m_heading;
   const double weight = particle.m_weight;
   const double v = m_velocity;
   const double yr = m_yawRate;
   const double dt = m_deltaTinS;

   if (fabs(yr) > 0.0001)
   {
      // if yaw rate is not zero
      const double yr_dt = yr * dt;
      const double v_by_yr = v / yr;
      const double x1 = x0 + v_by_yr * (sin(thetha0 + yr_dt) - sin(thetha0));
      const double y1 = y0 + v_by_yr * (cos(thetha0) - cos(thetha0 + yr_dt));
      const double thetha1 = thetha0 + yr_dt;
      movedParticle.set(x1, y1, thetha1, weight);
   }
   else
   {
      // if yaw rate is zero
      const double x1 = x0 + v * cos(thetha0) * dt;
      const double y1 = y0 + v * sin(thetha0) * dt;
      const double thetha1 = thetha0;
      movedParticle.set(x1, y1, thetha1, weight);
   }

   return movedParticle;
}
