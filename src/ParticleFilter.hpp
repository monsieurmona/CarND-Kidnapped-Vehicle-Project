/*
 *  Author: Mario Lüder
 */
#ifndef PARTICLEFILTER_HPP
#define PARTICLEFILTER_HPP

// system includes
#include <array>
#include <memory>

// local includes
#include "Landmarks.hpp"
#include "MotionModel.hpp"
#include "Particle.hpp"
#include "ParticleStorage.hpp"

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
   using X = std::unique_ptr<ParticleFilter>;

   struct BestParticle
   {
      BestParticle() : m_ptr(nullptr), m_totalWeight(0.0) {}
      const Particle * m_ptr;
      double m_totalWeight;
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
    * @param landmarkStd Landmark measurement uncertainty [x [m], y [m]]
    * @param observations landmark observations
    * @param landmarkMap contains map landmarks
    */
   void updateWeights(const double sensorRange, const StandardDeviationLandmark & landmarkStd, const Observations & observations, const LandmarkMap & landmarkMap);

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
   inline size_t getAmount() const { return m_particles.getAmount(); }

private:
   ParticleStorage<3> m_particles; ///< all particles
   bool m_isInitialized = false;
};

#endif // PARTICLEFILTER_HPP
