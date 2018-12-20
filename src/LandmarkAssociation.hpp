/*
 *  Author: Mario Lüder
 */

#ifndef LANDMARKASSOCIATION_HPP
#define LANDMARKASSOCIATION_HPP

// local includes
#include "Observations.hpp"

// forward declarations
class MeanParticle;
class LandmarkMap;

class LandmarkAssociation
{
   /**
    * @brief associates car observations to map landmarks
    * @param sensorRange
    * @param predictedCarPosition a particle that represents a possible car position
    * @param carObervations a copy of all car observations
    * @param landmarkMap all map landmarks
    */
   void associate(const double sensorRange, const Particle & predictedCarPosition, Observations carObervations, const LandmarkMap & landmarkMap);

private:
   Observations m_assocations;
};

#endif // LANDMARKASSOCIATION_HPP
