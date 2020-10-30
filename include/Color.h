/**
 * This file models a color or label from the MVC problem, with the 
 * objective of speeding up the adjacency check of vertexes 
 * 
 * Author: Fábio de Azevedo Gomes
 */
#include <vector>

#ifndef COLOR_H
#define COLOR_H

#include "Vertex.h"

// Forward declaration of vertex
class Vertex;

class Color
{
private:
    static int color_count; // Total number of colors generated

    int label;                      // Color label
    std::vector<Vertex *> vertexes; // List of vertexes that have this color

public:
    /**
     * @brief Color constructor
     */
    Color();

    /**
     * @brief Color destructor 
     */
    ~Color();

    // Getters
    int getLabel();
    bool isUsed();

    // Setters
    void setUser(Vertex *vertex);
};

#endif