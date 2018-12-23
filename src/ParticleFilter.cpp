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


void ParticleFilter::updateWeights(const double sensorRange, const MeanParticle & carPosition, const StandardDeviationLandmark & landmarkStd, const Observations & observations, const LandmarkMap & landmarkMap)
{
   for (Particle & predictedCarPosition : m_particles)
   {
      m_landmarkAssociation.associate(sensorRange, predictedCarPosition, observations, landmarkMap);
      predictedCarPosition.m_weight = m_landmarkAssociation.getWeight(carPosition, predictedCarPosition, landmarkStd);
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
   using ParticleIndexes = FixedSizeVector<ParticleIndex, nParticles>;
   ParticleIndexes particleIndexes;

   // comparators for the insert function, to avoid duplicates
   // this class is defined here, as this is only needed in this scope
   class ComparePred
   {
   public:
      class LesserThan
      {
      public:
         bool operator()(const ParticleIndex & lhs, const ParticleIndex & rhs) const {return lhs < rhs;}
      };

      class Equal
      {
      public:
         bool operator()(const ParticleIndex & lhs, const ParticleIndex & rhs) const {return lhs == rhs;}
      };
   };

   const double maxWeight = getMaxWeight();

   RandomGenerator<ParticleIndex, std::uniform_int_distribution<ParticleIndex>>
         randomIndexGenerator(0, m_particles.length());

   RandomGenerator<double, std::uniform_real_distribution<double>>
         randomBetaGenerator(0.0, 2.0 * maxWeight);

   ParticleIndex selectIdx = randomIndexGenerator();
   double beta = 0.0;
   const size_t N = m_particles.length();

   for (ParticleIndex particleIdx = 0; particleIdx < N; particleIdx++)
   {
      beta += randomBetaGenerator();
      const Particle & particle = m_particles[particleIdx];

      while(beta > particle.m_weight)
      {
         beta -= particle.m_weight;
         selectIdx = (selectIdx + 1) % N;
      }

      if (particleIndexes.insert<ComparePred>(selectIdx))
      {
         // if we don't have the particle already,
         // we insert the new particle into the new set
         const Particle & newParticle = m_particles[selectIdx];
         newParticles.push_back(newParticle);
      }
   }

   m_particles = newParticles;
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

