/*
 *  Author: Mario Lüder
 */
// system includes
#include <iostream>

// local includes
#include "LandmarkMap.hpp"
#include "MeanParticle.hpp"
#include "MotionModel.hpp"
#include "Observations.hpp"
#include "ParticleFilter.hpp"
#include "StandardDeviationPosition.hpp"
#include "StandardDeviationLandmark.hpp"

void ParticleFilter::init(MeanParticle & meanParticle)
{
   m_particles.occupy();

   for (Particle & particle : m_particles)
   {
      particle = meanParticle.sampleParticle();
   }

   m_isInitialized = true;
}

void ParticleFilter::predict(MotionModel & motionModel)
{
   for (Particle & particle : m_particles)
   {
      particle = motionModel(particle);
   }
}

void ParticleFilter::print()
{
   using namespace std;

   int i = 0;
   for (const Particle & particle : m_particles)
   {
      i++;
      cout << "Sample: " << i << " ";
      particle.print();
      cout << endl;
   }
}


void ParticleFilter::updateWeights(const double sensorRange, const StandardDeviationLandmark & landmarkStd, const Observations & observations, const LandmarkMap & landmarkMap)
{
   for (Particle & predictedCarPosition : m_particles)
   {
      m_landmarkAssociation.associate(sensorRange, predictedCarPosition, observations, landmarkMap);
      predictedCarPosition.m_weight = m_landmarkAssociation.getWeight(landmarkStd);
   }
}

const ParticleFilter::BestParticle ParticleFilter::getBestParticle() const
{
   double highestWeight = -1.0;
   BestParticle bestParticle;

   for (const Particle & particle : m_particles)
   {
      if (particle.m_weight > highestWeight) {
         highestWeight = particle.m_weight;
         bestParticle.m_ptr = &particle;
      }

      bestParticle.m_totalWeight += particle.m_weight;
   }

   return bestParticle;
}

void ParticleFilter::resample()
{
   ParticleStorage newParticles;
   using ParticleIndex = size_t;

   const double maxWeight = getMaxWeight();

   RandomGenerator<ParticleIndex, std::uniform_int_distribution<ParticleIndex>>
         randomIndexGenerator(0, m_particles.length());

   RandomGenerator<double, std::uniform_real_distribution<double>>
         randomBetaGenerator(0.0, 2.0 * maxWeight);

   ParticleIndex selectIdx = randomIndexGenerator();
   double beta = 0.0;
   const size_t N = m_particles.length();

   for (ParticleIndex counter = 0; counter < N; counter++)
   {
      beta += randomBetaGenerator();

      while(beta > m_particles[selectIdx].m_weight)
      {
         beta -= m_particles[selectIdx].m_weight;
         selectIdx = (selectIdx + 1) % N;
      }

      // if we don't have the particle already,
      // we insert the new particle into the new set
      const Particle & newParticle = m_particles[selectIdx];
      newParticles.push_back(newParticle);
   }

   m_particles = newParticles;
}


void ParticleFilter::getAssociationsString(
      const double sensorRange,
      const Particle & particle,
      const Observations & observations,
      const LandmarkMap & landmarkMap,
      std::string & landmarkIdsStr,
      std::string & xCoordinatesStr,
      std::string & yCoordinatesStr)
{
   m_landmarkAssociation.associate(sensorRange, particle, observations, landmarkMap);
   LandmarkAssociation::LandmarkIds landmarkIds;
   LandmarkAssociation::ObservationWorldCoordinates observationWorldCoordinates;
   m_landmarkAssociation.getLandmarkIds(landmarkIds);
   m_landmarkAssociation.getObservationWorldCoordinates(observationWorldCoordinates);

   std::stringstream idSs;
   std::stringstream xSs;
   std::stringstream ySs;

   std::copy( landmarkIds.begin(), landmarkIds.end(), std::ostream_iterator<int>(idSs, " "));
   landmarkIdsStr = idSs.str();

   if (landmarkIdsStr.length() > 0)
   {
      landmarkIdsStr = landmarkIdsStr.substr(
               0, landmarkIdsStr.length()-1);  // get rid of the trailing space
   }

   for (const auto & coordinate : observationWorldCoordinates)
   {
      xSs << coordinate.m_x << " ";
      ySs << coordinate.m_y << " ";
   }

   xCoordinatesStr = xSs.str();
   yCoordinatesStr = ySs.str();

   if (xCoordinatesStr.length() > 0)
   {
      xCoordinatesStr = xCoordinatesStr.substr(
               0, xCoordinatesStr.length()-1);  // get rid of the trailing space
   }

   if (yCoordinatesStr.length() > 0)
   {
      yCoordinatesStr = yCoordinatesStr.substr(
               0, yCoordinatesStr.length()-1);  // get rid of the trailing space
   }
}

double ParticleFilter::getMaxWeight() const
{
   double maxWeight = 0.0;

   for (const Particle & particle : m_particles)
   {
      if (particle.m_weight > maxWeight)
      {
         maxWeight = particle.m_weight;
      }
   }

   return maxWeight;
}

