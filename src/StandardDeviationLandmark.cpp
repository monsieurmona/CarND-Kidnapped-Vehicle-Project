/*
 *  Author: Mario Lüder
 */

#include "StandardDeviationLandmark.hpp"

StandardDeviationLandmark::StandardDeviationLandmark(const double stdX, const double stdY)
   : m_stdX(stdX)
   , m_stdY(stdY)
   , m_stdX2(2 * pow(stdX, 2))
   , m_stdY2(2 * pow(stdY, 2))
   , m_gauss_norm(1.0/(2.0 * M_PI * m_stdX * m_stdY))
{

}
