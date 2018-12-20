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
   for (Particle & particle : m_particles)
   {
      particle = meanParticle.sampleParticle();
   }

   m_isInitialized = true;
}

void ParticleFilter::predict(const MotionModel & motionModel)
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
   (void)sensorRange;
   (void)landmarkStd;
   (void)observations;
   (void)landmarkMap;
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
