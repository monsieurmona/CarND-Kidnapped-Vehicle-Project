/*
 *  Author: Mario Lüder
 */

#ifndef LANDMARKS_HPP
#define LANDMARKS_HPP

// system include
#include <array>

// local include
#include "Landmark.hpp"

/**
 * @brief Fixed Array of landmarks (without dynamic memory allocation according to MISRA)
 */
template<size_t nLandmarks>
class Landmarks
{
public:
   using Type = std::array<Landmark, nLandmarks>;
   using Iterator = typename Type::iterator;
   using ConstIterator = typename Type::const_iterator;

   Landmarks() {}

   inline Iterator begin() { return m_landmarks.begin(); }
   inline Iterator end() { return m_last; }
   inline ConstIterator begin() const { return m_begin; }
   inline ConstIterator end() const { return m_last; }

   /**
    * @brief inserts a landmark into the array as long as there is space
    * @param landmark
    * @return true if inserted otherwise false
    */
   inline bool push_back(const Landmark & landmark)
   {
      bool inserted = false;
      if (m_last != m_end)
      {
         *m_last = landmark;
         m_last++;
         m_length++;
         inserted = true;
      }

      return inserted;
   }

   /**
    * @brief removes all elements.
    */
   inline void clear()
   {
      m_last = m_landmarks.begin();
      m_length = 0;
   }

   /**
    * @brief amount of landmarks stored
    * @return
    */
   inline size_t length() { return m_length; }

private:
   Type m_landmarks;
   ConstIterator m_begin  = m_landmarks.begin();
   ConstIterator m_end    = m_landmarks.end();
   Iterator      m_last   = m_landmarks.begin();
   size_t        m_length = 0;
};

#endif // LANDMARKS_HPP
