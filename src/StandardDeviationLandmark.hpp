/*
 *  Author: Mario Lüder
 */

#ifndef STANDARDDEVIATIONLANDMARK_HPP
#define STANDARDDEVIATIONLANDMARK_HPP


class StandardDeviationLandmark
{
public:
   StandardDeviationLandmark(const double stdX, const double stdY);

   inline double getStdX() const { return m_stdX; }
   inline double getStdY() const { return m_stdY; }

private:
   double m_stdX;
   double m_stdY;
};

#endif // STANDARDDEVIATIONLANDMARK_HPP
