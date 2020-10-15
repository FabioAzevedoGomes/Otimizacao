#include "SimulatedAnnealing.h"

SimulatedAnnealing::SimulatedAnnealing(unsigned long seed_, float t_, float k_, float r_, std::string file)
{
    std::ifstream in_file;

    // Initialize values
    this->seed = seed_;
    this->k = k_;
    this->r = r_;
    this->t = t_;

    // Try to open file
    in_file.open(file, std::ifstream::in);

    if (in_file.is_open())
        this->prepareData(in_file);
    else
        throw std::runtime_error("Input file does not exist!");

    // Close file
    in_file.close();
}

SimulatedAnnealing::~SimulatedAnnealing()
{
    // TODO Free data structures used
}

void SimulatedAnnealing::prepareData(std::ifstream &file)
{
    // TODO
}

// ALGORITHM LOGIC

/**
 * Pseudo-Algorithm:
 * 
 * p = e ^ - (f(s') - f(s)) / k * t
 * 
 * while STOP 2
 *  while STOP 1
 *   Choose s' not visited from N(s)
 *    if f(s') < f(s)
 *      s = s'
 *    else 
 *      s = s' with probability p
 *  t = t * r
 * 
 * return s
 */

int SimulatedAnnealing::run()
{
    // TODO

    return 0;
}
