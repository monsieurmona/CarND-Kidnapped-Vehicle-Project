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
      const double x1 = getCoord2d().m_x;
      const double y1 = getCoord2d().m_y;
      const double x2 = particle.getCoordinates2D().m_x;
      const double y2 = particle.getCoordinates2D().m_y;

      return dist(x1,y1, x2, y2);
   }

   /**
    * @brief calculates the euclidean distance between two landmarks
    * @param particle
    * @return
    */
   inline double euclideanDistance(const Landmark & landmark) const
   {
      const double x1 = getCoord2d().m_x;
      const double y1 = getCoord2d().m_y;
      const double x2 = landmark.getCoord2d().m_x;
      const double y2 = landmark.getCoord2d().m_y;

      return dist(x1,y1, x2, y2);
   }

   /**
    * @brief checks if a particle is in a landmark square
    * @param particle
    * @param sideLength
    * @return
    */
   inline bool inTile(const Particle & particle, const double maxSideLength) const
   {
      const Coordinate2D sideLengths = getCoord2d() - particle.getCoordinates2D();

      return fabs(sideLengths.m_x) <= maxSideLength &&
             fabs(sideLengths.m_y) <= maxSideLength;
   }

   /**
    * @brief checks if a landmark is in a landmark square
    * @param particle
    * @param sideLength
    * @return
    */
   inline bool inTile(const Landmark & landmark, const double maxSideLength) const
   {
      const Coordinate2D sideLengths = getCoord2d() - landmark.getCoord2d();

      return fabs(sideLengths.m_x) <= maxSideLength &&
             fabs(sideLengths.m_y) <= maxSideLength;
   }

   /**
    * @brief subtract two landmark coordinates
    * @param landmark
    * @return resulting coordinate
    */
   inline Coordinate2D operator-(const Landmark & landmark) const
   {
      return getCoord2d() - landmark.getCoord2d();
   }

   /**
    * @brief subtract particle coordinate from a landmark coordinate
    * @param particle
    * @return resulting coordinate
    */
   inline Coordinate2D operator-(const Particle & particle) const
   {
      return getCoord2d() - particle.getCoordinates2D();
   }

   /**
    * @brief transforms observations, meassured in car coordinate system, to map coordinates
    * @param predictedCarPosition
    */
   inline void transform(const Particle & predictedCarPosition)
   {
      m_position.transform(predictedCarPosition.getCoordinates2D(), predictedCarPosition.m_heading);
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
   inline const Coordinate2D & getCoord2d() const { return m_position; }

private:
   int m_id;   // Id of matching landmark in the map.
   Coordinate2D m_position;
};

#endif // LANDMARK_HPP
