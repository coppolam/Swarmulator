#ifndef MAIN_H
#define MAIN_H

#include <mutex>
#include <vector>
#include "agent.h"
#include "parameters.hxx" // auto generated file at compile time

// Simulation variables
extern uint nagents; // Number of agents in the swarm
extern uint knearest;  // Knearest neighbours
extern std::vector<Agent *> s; // Set up a vector of particles
// extern std::vector<Wall> w; // Set up a vector of walls
extern float simulation_time; // Simulation time (our time)
extern float simtime_seconds; // Adjusted simulation time (time according to simulation)
extern std::mutex mtx; // Mutex for critical section
extern bool program_running; // True if the program is (or should be) running. If false the program shuts down.
extern unique_ptr<parameters_t> param; // XML parameters from conf file
extern uint window_width, window_height;
extern float realtimefactor;

#endif /*MAIN_H*/