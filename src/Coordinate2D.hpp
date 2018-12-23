/*
 *  Author: Mario Lüder
 */

#ifndef COORDINATE2D_HPP
#define COORDINATE2D_HPP

struct Coordinate2D
{
   Coordinate2D(const double x, const double y) : m_x(x), m_y(y) {}
   double m_x;
   double m_y;
};

#endif // COORDINATE2D_HPP
