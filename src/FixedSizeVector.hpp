/*
 *  Author: Mario Lüder
 */

#ifndef FIXEDSIZEVECTOR_HPP
#define FIXEDSIZEVECTOR_HPP

// system includes
#include <array>
#include <algorithm>
#include <assert.h>

/**
 * This is basically an array that can not be resized. The size has must be know at compile time.
 * Though it provides some functions like push_back(), clear(), ... to use this array like a vector
 */
template<class ElementType, size_t nElements>
class FixedSizeVector
{
public:
   using Type = std::array<ElementType, nElements>;
   using Iterator = typename Type::iterator;
   using ConstIterator = typename Type::const_iterator;

   FixedSizeVector() {}

   FixedSizeVector(const FixedSizeVector & rhs)
      : m_array(rhs.m_array)
      , m_length(rhs.m_length)
      , m_last(m_array.begin() + rhs.m_length)
   {
   }

   // remove move
   FixedSizeVector(const FixedSizeVector && rhs) = delete;

   void operator=(const FixedSizeVector & rhs)
   {
      m_array = rhs.m_array;
      m_length = rhs.m_length;
      m_last = m_array.begin() + rhs.m_length;
   }

   inline Iterator begin() { return m_array.begin(); }
   inline Iterator end() { return m_last; }
   inline ConstIterator begin() const { return m_array.begin(); }
   inline ConstIterator end() const { return m_last; }

   /**
    * @brief inserts a landmark into the array as long as there is space
    * @param landmark
    * @return true if inserted otherwise false
    */
   inline bool push_back(const ElementType & element)
   {
      assert((m_array.begin() + m_length) <= m_last);

      bool inserted = false;
      if (m_last != m_array.end())
      {
         *m_last = element;
         m_last++;
         m_length++;
         inserted = true;
      }

      return inserted;
   }

   /**
    * @brief sorted insert based on predicate
    * @return true if inserted
    */
   template<typename Pred>
   inline bool insert(const ElementType & element)
   {
      using LesserThenPred = typename Pred::LesserThan;
      typename Pred::Equal equalPred;
      Iterator insertIter = std::lower_bound(m_array.begin(), m_last, element, LesserThenPred());

      if (insertIter == m_array.end())
      {
         // array is full, nothing can be inserted
         return false;
      }

      if (insertIter == m_last)
      {
         // add element to the end of the list
         return push_back(element);
      }

      // check if element is already in the list
      if (equalPred(element, *insertIter))
      {
         // element is already in the list
         // don't do anything
         return false;
      }

      // make space, move elements to the right
      Iterator last = m_last;

      if (last == m_array.end())
      {
         // the last element will be deleted
         last--;
      }
      else
      {
         // there will be one more element
         m_length++;
      }

      std::move(insertIter, last, insertIter + 1);
      *insertIter = element;
      return true;
   }

   /**
    * @brief removes all elements.
    */
   inline void clear()
   {
      m_last = m_array.begin();
      m_length = 0;
   }

   /**
    * @brief the full array is occupied by elements
    */
   inline void occupy()
   {
      m_last = m_array.end();
      m_length = nElements;
   }

   /**
    * @brief fills the array with elements
    * @param element
    */
   inline void fill(const ElementType & element)
   {
      m_array.fill(element);
      occupy();
   }

   /**
    * @brief amount of landmarks stored
    * @return
    */
   inline size_t length() const { return m_length; }

   /**
    * @brief provides an elment from the array
    * @param idx index to the element
    * @return element
    */
   inline const ElementType & operator[](size_t idx) const { return m_array[idx]; }

   /**
    * @brief provides an elment from the array
    * @param idx index to the element
    * @return element
    */
   inline ElementType & operator[](size_t idx)
   {
      assert(idx < m_length);
      return m_array[idx];
   }

private:
   Type m_array;
   size_t        m_length = 0;
   Iterator      m_last   = m_array.begin();
};

#endif // FIXEDSIZEVECTOR_HPP
