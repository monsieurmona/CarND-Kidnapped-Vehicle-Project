#ifndef LANDMARKMAP_HPP
#define LANDMARKMAP_HPP

// system includes
#include <iostream>
#include <memory>
#include <string>

// local include
#include "Landmarks.hpp"

class LandmarkMap : public Landmarks<1000>
{
public:
   using UniquePtr = std::unique_ptr<LandmarkMap>;

   /* Reads map data from a file.
    * @param filename Name of file containing map data.
    * @output True if opening and reading file was successful
    * @note this part is was copied from code provided by udacity
    */
   inline bool read_map_data(const std::string & filename)
   {
      // Get file of map:
      std::ifstream in_file_map(filename.c_str(),std::ifstream::in);

      // Return if we can't open the file.
      if (!in_file_map) {
         return false;
      }

      // Declare single line of map file:
      std::string line_map;

      // Run over each single line:
      while(getline(in_file_map, line_map)){
         std::istringstream iss_map(line_map);
         Landmark landmark(iss_map);

         // Add to landmark list of map:
         if (!push_back(landmark))
         {
             std::cerr << "LandmarkMap::read_map_data Too less space available to store landmarks in a map" << std::endl;
             return false;
         }
      }
      return true;
   }
};

#endif // LANDMARKMAP_HPP
