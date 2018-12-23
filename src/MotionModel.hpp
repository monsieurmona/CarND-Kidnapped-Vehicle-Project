/*
 *  Author: Mario Lüder
 */

#ifndef MOTIONMODEL_HPP
#define MOTIONMODEL_HPP

// local includes
#include "StandardDeviationPosition.hpp"

// forward declaration
class Particle;

class MotionModel
{
public:
   MotionModel(const double deltaTinS, const double velocity, const double yawRate, const StandardDeviationPosition & std);

   /**
    * @brief compute a new particle by using the motion model
    * @param particle input particle
    * @return moved particle bases on the motion model
    */
   Particle operator()(const Particle & particle) const;

private:
   double m_deltaTinS;      ///< delta time in seconds
   double m_velocity;       ///<  velocity
   double m_yawRate;        ///< yaw rate
   StandardDeviationPosition m_std; ///< standard deviation
};

#endif // MOTIONMODEL_HPP
