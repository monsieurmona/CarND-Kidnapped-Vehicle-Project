#ifndef OBSERVATIONS_HPP
#define OBSERVATIONS_HPP

// system includes
#include <iostream>
#include <string>

// local includes
#include "Landmarks.hpp"

#include "json.hpp"

namespace ObservationDefines {
   static constexpr size_t m_nMaxObservations = 100;
}

/**
 * @brief Stores observations
 */
class Observations : public Landmarks<ObservationDefines::m_nMaxObservations>
{
public:
   using LandmarksType = Landmarks<ObservationDefines::m_nMaxObservations>;

   /**
    * @brief Reads coordinates from observations.
    * @param sense_observations_x x-coordinates
    * @param sense_observations_y y-coordinates
    * @return true if all coordinates where read from strings
    * @warning this function uses dynamic memory - and needs to be refactored.
    * @note this part is was copied from code provided by udacity
    */
   bool receive(const std::string & sense_observations_x, const std::string & sense_observations_y)
   {
      bool fullyReceived = true;

      // receive noisy observation data from the simulator
      // sense_observations in JSON format [{obs_x,obs_y},{obs_x,obs_y},...{obs_x,obs_y}]
      std::vector<float> x_sense;
      x_sense.reserve(ObservationDefines::m_nMaxObservations);
      std::stringstream iss_x(sense_observations_x);

      std::copy(std::istream_iterator<float>(iss_x),
                std::istream_iterator<float>(),
                std::back_inserter(x_sense));

      std::vector<float> y_sense;
      y_sense.reserve(ObservationDefines::m_nMaxObservations);
      std::stringstream iss_y(sense_observations_y);

      std::copy(std::istream_iterator<float>(iss_y),
                std::istream_iterator<float>(),
                std::back_inserter(y_sense));

      for(size_t i = 0; i < x_sense.size() && i < y_sense.size(); i++)
      {
         Landmark obs(
                  -1,
                  static_cast<double>(x_sense[i]),
                  static_cast<double>(y_sense[i]));

         if (!LandmarksType::push_back(obs))
         {
            std::cerr << "Add noisy observations failed" << std::endl;
            fullyReceived = false;
            break;
         }
      }

      return fullyReceived;
   }

   /**
    * @brief transforms observations in car coordinate system to map coordinates
    * @param predictedCarPosition
    */
   inline void transform(const Particle & predictedCarPosition)
   {
      for (Landmark & observation : *this)
      {
         observation.transform(predictedCarPosition);
      }
   }
};


#endif // OBSERVATIONS_HPP
