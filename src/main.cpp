// system includes
#include <uWS/uWS.h>
#include <math.h>
#include <iostream>
#include <memory>

// local includes
#include "helper_functions.h"
#include "json.hpp"

#include "LandmarkMap.hpp"
#include "MeanParticle.hpp"
#include "Observations.hpp"
#include "MotionModel.hpp"
#include "ParticleFilter.hpp"
#include "StandardDeviationLandmark.hpp"
#include "StandardDeviationPosition.hpp"

// for convenience
using json = nlohmann::json;

// Checks if the SocketIO event has JSON data.
// If there is data the JSON object in std::string format will be returned,
// else the empty std::string "" will be returned.
std::string hasData(std::string s) {
   auto found_null = s.find("null");
   auto b1 = s.find_first_of("[");
   auto b2 = s.find_first_of("]");
   if (found_null != std::string::npos) {
      return "";
   }
   else if (b1 != std::string::npos && b2 != std::string::npos) {
      return s.substr(b1, b2 - b1 + 1);
   }
   return "";
}

int main()
{
   uWS::Hub h;

   //Set up parameters here
   double delta_t = 0.1; // Time elapsed between measurements [sec]
   double sensor_range = 50; // Sensor range [m]

   StandardDeviationPosition sigma_pos(0.3, 0.3, 0.01); // GPS measurement uncertainty [x [m], y [m], theta [rad]]
   StandardDeviationLandmark sigma_landmark(0.3, 0.3); // Landmark measurement uncertainty [x [m], y [m]]

   // Read map data
   // create the landmark map on heap
   LandmarkMap::UniquePtr landmarkMapPtr = LandmarkMap::UniquePtr(new LandmarkMap());

   if (!landmarkMapPtr->read_map_data("./data/map_data.txt")) {
      std::cout << "Error: Could not open map file" << std::endl;
      return -1;
   }

   // Create particle filter on heap
   using ParticleFilterPtr = std::unique_ptr<ParticleFilter>;
   ParticleFilterPtr pf = ParticleFilterPtr(new ParticleFilter());

   h.onMessage([&pf,&landmarkMapPtr,&delta_t,&sensor_range,&sigma_pos,&sigma_landmark](uWS::WebSocket<uWS::SERVER> ws, char *data, size_t length, uWS::OpCode opCode) {
      (void)opCode;
      // "42" at the start of the message means there's a websocket message event.
      // The 4 signifies a websocket message
      // The 2 signifies a websocket event

      if (length && length > 2 && data[0] == '4' && data[1] == '2')
      {
         auto s = hasData(std::string(data));
         if (s != "") {


            auto j = json::parse(s);
            std::string event = j[0].get<std::string>();

            if (event == "telemetry") {
               // j[1] is the data JSON object


               if (!pf->isInitialized()) {
                  // Sense noisy position data from the simulator
                  double sense_x = std::stod(j[1]["sense_x"].get<std::string>());
                  double sense_y = std::stod(j[1]["sense_y"].get<std::string>());
                  double sense_theta = std::stod(j[1]["sense_theta"].get<std::string>());
                  MeanParticle meanParticle(Particle(sense_x, sense_y, sense_theta), sigma_pos);
                  pf->init(meanParticle);
               }
               else {
                  // Predict the vehicle's next state from previous (noiseless control) data.
                  double previous_velocity = std::stod(j[1]["previous_velocity"].get<std::string>());
                  double previous_yawrate = std::stod(j[1]["previous_yawrate"].get<std::string>());

                  std::cout << "velocity:" << previous_velocity << " yawrate:" << previous_yawrate << std::endl;
                  MotionModel motionModel(delta_t, previous_velocity, previous_yawrate, sigma_pos);
                  pf->predict(motionModel);
               }

               // receive noisy observation data from the simulator
               // sense_observations in JSON format [{obs_x,obs_y},{obs_x,obs_y},...{obs_x,obs_y}]
               std::string sense_observations_x = j[1]["sense_observations_x"];
               std::string sense_observations_y = j[1]["sense_observations_y"];

               Observations noisy_observations;
               noisy_observations.receive(sense_observations_x, sense_observations_y);

               // Update the weights and resample
               const LandmarkMap & landmarkMap = *landmarkMapPtr.get();
               pf->updateWeights(sensor_range, sigma_landmark, noisy_observations, landmarkMap);
               // pf->print();
               pf->resample();

               size_t num_particles = pf->getAmount();
               const ParticleFilter::BestParticle best_particle = pf->getBestParticle();
               const double highest_weight = best_particle.m_ptr->m_weight;
               const double weight_sum = best_particle.m_totalWeight;

               std::cout << "highest w " << highest_weight << std::endl;
               std::cout << "average w " << weight_sum/num_particles << std::endl;

               json msgJson;
               msgJson["best_particle_x"] = best_particle.m_ptr->m_x;
               msgJson["best_particle_y"] = best_particle.m_ptr->m_y;
               msgJson["best_particle_theta"] = best_particle.m_ptr->m_heading;

               //Optional message data used for debugging particle's sensing and associations
               std::string associatedLandmarkIds;
               std::string associatedObeservationXCoordinates;
               std::string associatedObeservationYCoordinates;
               /*
               pf->getAssociationsString(
                        sensor_range,
                        *best_particle.m_ptr,
                        noisy_observations,
                        *landmarkMapPtr,
                        associatedLandmarkIds,
                        associatedObeservationXCoordinates,
                        associatedObeservationYCoordinates
                        );
               */
               msgJson["best_particle_associations"] = associatedLandmarkIds;
               msgJson["best_particle_sense_x"] = associatedObeservationXCoordinates;
               msgJson["best_particle_sense_y"] = associatedObeservationYCoordinates;

               auto msg = "42[\"best_particle\"," + msgJson.dump() + "]";
               // std::cout << msg << std::endl;
               ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);

            }
         } else {
            std::string msg = "42[\"manual\",{}]";
            ws.send(msg.data(), msg.length(), uWS::OpCode::TEXT);
         }
      }

   });

   // We don't need this since we're not using HTTP but if it's removed the program
   // doesn't compile :-(
   h.onHttpRequest([](uWS::HttpResponse *res, uWS::HttpRequest req, char *data, size_t, size_t) {
      (void)data;
      const std::string s = "<h1>Hello world!</h1>";
      if (req.getUrl().valueLength == 1)
      {
         res->end(s.data(), s.length());
      }
      else
      {
         // i guess this should be done more gracefully?
         res->end(nullptr, 0);
      }
   });

   h.onConnection([&h](uWS::WebSocket<uWS::SERVER> ws, uWS::HttpRequest req) {
      (void)h;
      (void)ws;
      (void)req;
      std::cout << "Connected!!!" << std::endl;
   });

   h.onDisconnection([&h](uWS::WebSocket<uWS::SERVER> ws, int code, char *message, size_t length) {
      (void)h;
      (void)code;
      (void)message;
      (void)length;
      ws.close();
      std::cout << "Disconnected" << std::endl;
   });

   int port = 4567;
   if (h.listen(port))
   {
      std::cout << "Listening to port " << port << std::endl;
   }
   else
   {
      std::cerr << "Failed to listen to port" << std::endl;
      return -1;
   }
   h.run();
}























































































