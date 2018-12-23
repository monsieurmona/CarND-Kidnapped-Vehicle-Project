/*
 *  Author: Mario Lüder
 */

#ifndef LANDMARKS_HPP
#define LANDMARKS_HPP

// system include
#include <array>

// local include
#include "FixedSizeVector.hpp"
#include "Landmark.hpp"

/**
 * @brief Fixed Array of landmarks (without dynamic memory allocation according to MISRA)
 */
template<size_t nLandmarks>
class Landmarks : public FixedSizeVector<Landmark, nLandmarks>
{
public:
   Landmarks() : FixedSizeVector<Landmark, nLandmarks>() {}
};

#endif // LANDMARKS_HPP
