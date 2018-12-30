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
   using LandmarkIds = FixedSizeVector<int, ObservationDefines::m_nMaxObservations>;
   using ObservationWorldCoordinates = FixedSizeVector<Coordinate2D, ObservationDefines::m_nMaxObservations>;
   using AssociationPair = std::pair<Observation, const Landmark *>;
   using Associations = FixedSizeVector<AssociationPair, ObservationDefines::m_nMaxObservations>;

   /**
    * @brief associates car observations to map landmarks
    * @param sensorRange
    * @param predictedCarPosition a particle that represents a possible car position
    * @param carObservations a copy of all car observations
    * @param landmarkMap all map landmarks
    */
   void associate(const double sensorRange, const Particle & predictedCarPosition, const Observations & carObservations, const LandmarkMap & landmarkMap);

   /**
    * @brief calculate the new weight for a particle
    * @param carPosition the position of the car in world coordinates
    * @param predictedCarPosition one particle
    * @param stdLandmark standard deviation of an observation
    * @return new weight
    */
   double getWeight(const StandardDeviationLandmark & stdLandmark);

   /**
    * @brief provides associated landmark ids
    * @param landmakIds
    * @return true : successful
    */
   bool getLandmarkIds(LandmarkIds & landmakIds) const;

   /**
    * @brief provides provides the world coordinates of observations that were associated to landmarks
    * @param observationWorldCoordinates world coordinates of observations
    * @return true : successful
    */
   bool getObservationWorldCoordinates(ObservationWorldCoordinates & observationWorldCoordinates) const;

private:
   Associations m_assocations;
};

#endif // LANDMARKASSOCIATION_HPP
