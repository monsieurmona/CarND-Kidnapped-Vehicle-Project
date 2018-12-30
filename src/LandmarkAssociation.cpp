/*
 *  Author: Mario Lüder
 */

// local includes
#include "LandmarkAssociation.hpp"
#include "LandmarkMap.hpp"
#include "MeanParticle.hpp"
#include "StandardDeviationLandmark.hpp"

void LandmarkAssociation::associate(const double sensorRange, const Particle & predictedCarPosition, Observations carObservations, const LandmarkMap & landmarkMap)
{
   const double maxDistance = std::numeric_limits<double>::max();

   carObservations.transform(predictedCarPosition);
   m_assocations.clear();

   // get landmarks in view for association
   LandmarkMap::LandmarksInView landmarksInView;
   landmarkMap.getLandmarksInView(predictedCarPosition, sensorRange * 1.1, landmarksInView);

   // for all observations find the closest landmark
   for (const Observation & observation : carObservations)
   {
      double minDistance = maxDistance;
      const Landmark * closestLandmark = nullptr;

      // find the closest landmark for the observation
      for (const Landmark * landmarkInView : landmarksInView)
      {
         if (landmarkInView)
         {
            const double associationDistance = observation.euclideanDistance(*landmarkInView);

            if (associationDistance < minDistance)
            {
               closestLandmark = landmarkInView;
               minDistance = associationDistance;
            }
         }
      }

      // add closest landmark if available
      if (closestLandmark != nullptr)
      {
         AssociationPair associationPair(observation, closestLandmark);

         if (!m_assocations.push_back(associationPair))
         {
            std::cerr << "LandmarkAssociation::associate can't add more associations" << std::endl;
            break;
         }
      }
   }
}

double LandmarkAssociation::getWeight(const StandardDeviationLandmark & stdLandmark)
{
   double prob = 1.0;

   for (const AssociationPair & association : m_assocations)
   {
      const Observation & observation = association.first;
      const Landmark * landmark = association.second;

      if (landmark != nullptr)
      {
         //prob *= stdLandmark.gaussian(landmark->getCoord2d(), observation.getCoord2d());
         const double observationProb =
               stdLandmark.gaussian(observation.getCoord2d(), landmark->getCoord2d());

         if (observationProb > 0.0)
         {
            prob *= observationProb;
         }
         else
         {
            prob = 0.0;
            break;
         }
      }
   }

   return prob;
}


bool LandmarkAssociation::getLandmarkIds(LandmarkIds & landmakIds) const
{
   landmakIds.clear();

   for (const AssociationPair & association : m_assocations)
   {
      const Landmark * landmark = association.second;

      if (landmark != nullptr)
      {
         if (!landmakIds.push_back(landmark->getId()))
         {
            return false;
         }
      }
   }

   return true;
}

bool LandmarkAssociation::getObservationWorldCoordinates(ObservationWorldCoordinates & observationWorldCoordinates) const
{
   observationWorldCoordinates.clear();

   for (const AssociationPair & association : m_assocations)
   {
      const Observation & observation = association.first;
      const Landmark * landmark = association.second;

      if (landmark != nullptr)
      {
         const Coordinate2D coordinates = observation.getCoord2d();
         if (!observationWorldCoordinates.push_back(coordinates))
         {
            return false;
         }
      }
   }

   return true;
}
