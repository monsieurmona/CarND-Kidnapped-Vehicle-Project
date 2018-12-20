/*
 *  Author: Mario Lüder
 */
#ifndef STANDARDDEVIATIONPOSITION_HPP
#define STANDARDDEVIATIONPOSITION_HPP


class StandardDeviationPosition
{
public:
   StandardDeviationPosition(const double stdX, const double stdY, const double stdHeading);

   inline double getStdX() const { return m_stdX; }
   inline double getStdY() const { return m_stdY; }
   inline double getStdHeading() const { return m_stdHeading; }

private:
   double m_stdX;
   double m_stdY;
   double m_stdHeading;
};

#endif // STANDARDDEVIATIONPOSITION_HPP
