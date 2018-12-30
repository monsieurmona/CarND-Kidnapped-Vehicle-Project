/*
 *  Author: Mario Lüder
 */
#ifndef STANDARDDEVIATIONLANDMARK_HPP
#define STANDARDDEVIATIONLANDMARK_HPP

// system includes
#include <math.h>
// local includes
#include "helper_functions.h"
#include "Coordinate2D.hpp"

class StandardDeviationLandmark
{
public:
   StandardDeviationLandmark(const double stdX, const double stdY);

   inline double getStdX() const { return m_stdX; }
   inline double getStdY() const { return m_stdY; }

   inline double gaussian(const Coordinate2D & mu, const Coordinate2D & observation) const
   {
      const double exponent=
            (pow((observation.m_x - mu.m_x),2) / m_stdX2) +
            (pow((observation.m_y - mu.m_y),2) / m_stdY2);

      const double weight = m_gauss_norm * exp(- exponent);
      return weight;
   }

private:
   double m_stdX;
   double m_stdY;
   double m_stdX2;
   double m_stdY2;
   double m_gauss_norm;
};

#endif // STANDARDDEVIATIONLANDMARK_HPP
