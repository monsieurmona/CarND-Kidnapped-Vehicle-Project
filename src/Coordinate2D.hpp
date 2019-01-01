/*
 *  Author: Mario Lüder
 */

#ifndef COORDINATE2D_HPP
#define COORDINATE2D_HPP

// system includes
#include "math.h"

struct Coordinate2D
{
   Coordinate2D() { /* not initialized on purpose */ }
   Coordinate2D(const double x, const double y) : m_x(x), m_y(y) {}

   /**
    * @brief subtract one coordinate from another
    * @param rhs right hand side value
    * @return result of subtraction
    */
   inline Coordinate2D operator-(const Coordinate2D & rhs) const
   {
      Coordinate2D result = rhs;
      result.m_x -= rhs.m_x;
      result.m_y -= rhs.m_y;
      return result;
   }

   /**
    * @brief transforms observations, meassured in car coordinate system, to map coordinates
    * @param predictedCarPosition
    */
   inline void transform(const Coordinate2D & position, const double theta)
   {
      const double x_p = position.m_x;
      const double y_p = position.m_y;
      const double cos_theta = cos(theta);
      const double sin_theta = sin(theta);

      const double newX = m_x * cos_theta - m_y * sin_theta + x_p;
      const double newY = m_x * sin_theta + m_y * cos_theta + y_p;
      m_x = newX;
      m_y = newY;
   }

   double m_x;
   double m_y;
};

#endif // COORDINATE2D_HPP
