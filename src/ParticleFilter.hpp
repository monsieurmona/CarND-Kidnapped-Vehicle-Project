/*
 *  Author: Mario Lüder
 */
#ifndef PARTICLEFILTER_HPP
#define PARTICLEFILTER_HPP

// system includes
#include <array>
#include <memory>

// local includes
#include "FixedSizeVector.hpp"
#include "Landmarks.hpp"
#include "LandmarkAssociation.hpp"
#include "MotionModel.hpp"
#include "Particle.hpp"

// forward declaration
class LandmarkMap;
class MeanParticle;
class MotionModel;
class Observations;
class StandardDeviationLandmark;
class StandardDeviationPosition;

// class defintion
class ParticleFilter
{
public:
   static constexpr int nParticles = 3;
   using ParticleStorage = FixedSizeVector<Particle, nParticles>;

   struct BestParticle
   {
      BestParticle() : m_ptr(nullptr), m_totalWeight(0.0) {}
      const Particle * m_ptr;
      double m_totalWeight;
   };

   template<typename TRandomValue, typename TDistribution>
   class RandomGenerator
   {
   public:
      using Type = TRandomValue;

      RandomGenerator(TRandomValue start, TRandomValue end)
         : gen(std::random_device()())
         , distribution(start, end)
      {
      }

      Type operator()() { return distribution(gen); }

   private:
      std::mt19937 gen;
      TDistribution distribution;
   };

   /**
    * @brief initialized the particle filter around the first measurement
    * @param meanParticle
    */
   void init(MeanParticle & meanParticle);

   /**
    * @brief predicts the state of all particles for the next time
    * @param motionModel defines how the object moves
    */
   void predict(const MotionModel & motionModel);

   /**
    * @brief Updates the weights for each particle based on the likelihood of the observed measurements.
    * @param sensorRange Range [m] of sensor
    * @param carPosition postion of the car
    * @param landmarkStd Landmark measurement uncertainty [x [m], y [m]]
    * @param observations landmark observations
    * @param landmarkMap contains map landmarks
    */
   void updateWeights(const double sensorRange, const MeanParticle & carPosition, const StandardDeviationLandmark & landmarkStd, const Observations & observations, const LandmarkMap & landmarkMap);

   /**
    * resample Resamples from the updated set of particles to form
    *   the new set of particles.
    */
   void resample();

   /**
    * @brief print all particle values to stdout - debug only
    */
   void print();

   /**
    * @brief provides initialization status
    * @return
    */
   bool isInitialized() {return m_isInitialized;}

   /**
    * @brief get the particle with the hightes weight
    * @return BestParticle
    */
   const BestParticle getBestParticle() const;

   /**
    * @brief get the amount of stored particles
    * @return amount of particles
    */
   inline size_t getAmount() const { return m_particles.length(); }

private:
   double getMaxWeight() const;


   ParticleStorage m_particles; ///< all particles
   LandmarkAssociation m_landmarkAssociation;
   bool m_isInitialized = false;
};

#endif // PARTICLEFILTER_HPP
