/*
 *  Author: Mario Lüder
 */
#ifndef STANDARDDEVIATIONPOSITION_HPP
#define STANDARDDEVIATIONPOSITION_HPP

// system includes
#include <random>

class StandardDeviationPosition
{
public:
   StandardDeviationPosition(const double stdX, const double stdY, const double stdHeading);

   inline double getStdX() const { return m_stdX; }
   inline double getStdY() const { return m_stdY; }
   inline double getStdHeading() const { return m_stdHeading; }

   inline double getXNoise() { return m_normDistX(m_gen); }
   inline double getYNoise() { return m_normDistY(m_gen); }
   inline double getHeadingNoise() { return m_normDistHeading(m_gen); }

private:
   double m_stdX;
   double m_stdY;
   double m_stdHeading;

   std::normal_distribution<double> m_normDistX;
   std::normal_distribution<double> m_normDistY;
   std::normal_distribution<double> m_normDistHeading;

   std::mt19937 m_gen;
};

#endif // STANDARDDEVIATIONPOSITION_HPP
