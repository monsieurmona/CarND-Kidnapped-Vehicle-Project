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

Particle MotionModel::operator()(const Particle & particle)
{
   Particle movedParticle;

   // for convinience to make the formulars more comprehensible
   const double x0 = particle.m_x;
   const double y0 = particle.m_y;
   const double theta0 = particle.m_heading;
   const double weight = particle.m_weight;
   const double v = m_velocity;
   const double yr = m_yawRate;
   const double dt = m_deltaTinS;

   double x1 = 0.0;
   double y1 = 0.0;
   double theta1 = 0.0;

   if (fabs(yr) > 0.00001)
   {
      // if yaw rate is not zero
      const double yr_dt = yr * dt;
      const double v_by_yr = v / yr;
      x1 = x0 + v_by_yr * (sin(theta0 + yr_dt) - sin(theta0));
      y1 = y0 + v_by_yr * (cos(theta0) - cos(theta0 + yr_dt));
      theta1 = theta0 + yr_dt;
   }
   else
   {
      // if yaw rate is zero
      // going straight
      x1 = x0 + v * cos(theta0) * dt;
      y1 = y0 + v * sin(theta0) * dt;
      theta1 = theta0;
   }

   // add noise
   x1 += m_std.getXNoise();
   y1 += m_std.getYNoise();
   theta1 += m_std.getHeadingNoise();

   movedParticle.set(x1, y1, theta1, weight);

   return movedParticle;
}
