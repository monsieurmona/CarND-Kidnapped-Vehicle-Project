/*
 *  Author: Mario Lüder
 */

#ifndef LANDMARKASSOCIATION_HPP
#define LANDMARKASSOCIATION_HPP

// local includes
#include "FixedSizeVector.hpp"
#include "Observations.hpp"

// forward declarations
class LandmarkMap;
class MeanParticle;
class StandardDeviationLandmark;

class LandmarkAssociation
{
public:
   using Observation = Landmark;

   // a association consits of a transformed observation (map coordinates) and a pointer to a landmark if available
   using AssociationPair = std::pair<Observation, const Landmark *>;
   using Associations = FixedSizeVector<AssociationPair, ObservationDefines::m_nMaxObservations>;

   /**
    * @brief associates car observations to map landmarks
    * @param sensorRange
    * @param predictedCarPosition a particle that represents a possible car position
    * @param carObervations a copy of all car observations
    * @param landmarkMap all map landmarks
    */
   void associate(const double sensorRange, const Particle & predictedCarPosition, Observations carObervations, const LandmarkMap & landmarkMap);

   /**
    * @brief calculate the new weight for a particle
    * @param carPosition the position of the car in world coordinates
    * @param predictedCarPosition one particle
    * @param stdLandmark standard deviation of an observation
    * @return new weight
    */
   double getWeight(const MeanParticle & carPosition, const Particle & predictedCarPosition, const StandardDeviationLandmark & stdLandmark);
private:
   Associations m_assocations;
};

#endif // LANDMARKASSOCIATION_HPP