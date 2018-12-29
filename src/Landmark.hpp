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
#include "Coordinate2D.hpp"
#include "Particle.hpp"

/**
 * @brief A Landmark
 */
class Landmark
{
public:
   Landmark() {}
   Landmark(const int id, const double x, const double y);
   Landmark(std::istringstream & iss);

   /**
    * @brief calculates the euclidean distance between a particle and a observed landmark
    * @param particle
    * @return
    */
   inline double euclideanDistance(const Particle & particle) const
   {
      return dist(m_x, m_y, particle.m_x, particle.m_y);
   }

   /**
    * @brief calculates the euclidean distance between two landmarks
    * @param particle
    * @return
    */
   inline double euclideanDistance(const Landmark & landmark) const
   {
      return dist(m_x, m_y, landmark.m_x, landmark.m_y);
   }

   inline Coordinate2D operator-(const Landmark & landmark) const
   {
      Coordinate2D coordinate(m_x, m_y);
      coordinate.m_x -= landmark.m_x;
      coordinate.m_y -= landmark.m_y;
      return coordinate;
   }

   inline Coordinate2D operator-(const Particle & particle) const
   {
      Coordinate2D coordinate(m_x, m_y);
      coordinate.m_x -= particle.m_x;
      coordinate.m_y -= particle.m_y;
      return coordinate;
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

   /**
    * @brief provides the id of the landmark
    * @return landmark id
    */
   inline int getId() const { return m_id; }

   /**
    * @brief provides the coordinate of the landmark
    * @return landmark coordinates
    */
   inline Coordinate2D operator()() const { return Coordinate2D(m_x, m_y); }

private:
   int m_id;			// Id of matching landmark in the map.
   double m_x;			// Local (vehicle coordinates) x position of landmark observation [m]
   double m_y;			// Local (vehicle coordinates) y position of landmark observation [m]
};

#endif // LANDMARK_HPP
