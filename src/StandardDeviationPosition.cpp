/*
 *  Author: Mario Lüder
 */
#include "StandardDeviationPosition.hpp"

StandardDeviationPosition::StandardDeviationPosition(const double stdX, const double stdY, const double stdHeading)
    : m_stdX(stdX)
    , m_stdY(stdY)
    , m_stdHeading(stdHeading)
    , m_normDistX(0.0, stdX)
    , m_normDistY(0.0, stdY)
    , m_normDistHeading(0.0, stdHeading)
    , m_gen(std::random_device()())
{
}
