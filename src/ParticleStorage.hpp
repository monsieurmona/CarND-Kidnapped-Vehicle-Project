/*
 *  Author: Mario Lüder
 */
#ifndef PARTICLESTORAGE_HPP
#define PARTICLESTORAGE_HPP

// system includes
#include <array>

// local includes
#include "Particle.hpp"

/**
 * @brief Array of Particles without dynamic memory allocation according to MISRA
 */
template <size_t nParticles>
class ParticleStorage
{
public:
   using StorageType = std::array<Particle, nParticles>;
   using Iterator = typename StorageType::iterator;
   using ConstIterator = typename StorageType::const_iterator;

   Iterator begin() { return m_begin; }
   Iterator end() { return m_end; }

   ConstIterator begin() const { return m_begin; }
   ConstIterator end() const { return m_end; }

   const Particle & operator[](size_t idx) const { return m_particles[idx]; }

   size_t getAmount() const { return m_particles.size(); }

private:
   StorageType m_particles;
   Iterator m_begin = m_particles.begin();
   Iterator m_end = m_particles.end();
};

#endif // PARTICLESTORAGE_HPP
