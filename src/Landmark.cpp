/*
 *  Author: Mario Lüder
 */

// local include
#include "Landmark.hpp"
#include "Particle.hpp"

Landmark::Landmark(const int id, const double x, const double y)
    : m_id(id)
    , m_x(x)
    , m_y(y)
{
}

Landmark::Landmark(std::istringstream & iss)
{
   // Read data from current line to values::
   iss >> m_x;
   iss >> m_y;
   iss >> m_id;
}
