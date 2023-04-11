/*! \file Vertices.h
    \brief Contains the Vertex struct.
*/
#ifndef VERTICES_H
#define VERTICES_H

#include<bits/stdc++.h>
#include<stdio.h>
#include<unistd.h>
#include "Edges.h"
using namespace std;
struct HalfEdge;
struct Vertex{
    double x,y;
    int ind;
    HalfEdge* incidentEdge;
    Vertex(double x, double y, int ind);
};

#endif