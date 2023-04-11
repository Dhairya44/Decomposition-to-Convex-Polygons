/*! \file Edges.h
    \brief Contains the HalfEdge struct.
*/
#ifndef EDGES_H
#define EDGES_H

#include "Vertices.h"
#include "Faces.h"
using namespace std;
struct Vertex;
struct Face;
struct HalfEdge{
    Vertex* org;
    Vertex* dest;
    HalfEdge* twin;
    HalfEdge* next;
    HalfEdge* prev;
    Face* incidentFace;
    HalfEdge();
    HalfEdge(Vertex* org, Vertex* dest, HalfEdge* twin, HalfEdge* next, HalfEdge* prev, Face* incidentFace);
};

#endif