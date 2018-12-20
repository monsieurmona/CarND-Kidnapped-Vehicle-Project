/*
 *  Author: Mario Lüder
 */

// local includes
#include "LandmarkAssociation.hpp"
#include "MeanParticle.hpp"
#include "LandmarkMap.hpp"

void LandmarkAssociation::associate(const double sensorRange, const Particle & predictedCarPosition, Observations carObervations, const LandmarkMap & landmarkMap)
{
   carObervations.transform(predictedCarPosition);

   // find the landmarks in the  map that match the observations
}
