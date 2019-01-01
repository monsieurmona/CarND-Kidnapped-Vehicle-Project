/*
 *  Author: Mario Lüder
 */

// local include
#include "Landmark.hpp"
#include "Particle.hpp"

Landmark::Landmark(const int id, const double x, const double y)
    : m_id(id)
    , m_position(x, y)
{
}

Landmark::Landmark(std::istringstream & iss)
{
   // Read data from current line to values::
   iss >> m_position.m_x;
   iss >> m_position.m_y;
   iss >> m_id;
}
