/*
 *  Author: Mario Lüder
 */

#ifndef LANDMARK_HPP
#define LANDMARK_HPP

// system includes
#include <iostream>
#include <math.h>

// local include
#include "helper_functions.h"
#include "Particle.hpp"

/**
 * @brief A Landmark
 */
class Landmark
{
public:
   Landmark(const int id, const double x, const double y);
   Landmark(std::istringstream & iss);

   /**
    * @brief calculates the euclidean distance between a particle and a observed landmark
    * @param particle
    * @return
    */
   inline double euclideanDistance(const Particle & particle)
   {
      return dist(m_x, m_y, particle.m_x, particle.m_y);
   }

   /**
    * @brief transforms observations in car coordinate system to map coordinates
    * @param predictedCarPosition
    */
   inline void transform(const Particle & predictedCarPosition)
   {
      const double x_p = predictedCarPosition.m_x;
      const double y_p = predictedCarPosition.m_y;
      const double theta = predictedCarPosition.m_heading;
      const double cos_theta = cos(theta);
      const double sin_theta = sin(theta);

      m_x = x_p + cos_theta * m_x - sin_theta * m_y;
      m_y = y_p + sin_theta * m_x + cos_theta * m_y;
   }

private:
   int m_id;			// Id of matching landmark in the map.
   double m_x;			// Local (vehicle coordinates) x position of landmark observation [m]
   double m_y;			// Local (vehicle coordinates) y position of landmark observation [m]
};

#endif // LANDMARK_HPP
