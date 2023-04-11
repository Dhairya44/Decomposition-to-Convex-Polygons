/*! \file DCEL.h
    \brief Contains the main DCEL class and all the functions related to it.
*/
#ifndef DCEL_H
#define DCEL_H
#include <bits/stdc++.h>
#include "Vertices.h"
#include "Edges.h"
#include "Faces.h"
using namespace std;
struct Vertex;
struct HalfEdge;
struct Face;
/*! \class DCEL
    \brief The main DCEL class.
*/
class DCEL{
    public:
    vector<Face*> faces;
    vector<Vertex*> vertices;
    vector<HalfEdge*> edges;
    vector<HalfEdge*> diag;

    void createPolygon(vector<pair<double, double>> &points);

    void traverseFace();

    vector<pair<Vertex*, Vertex*>> findLLE();

    void traverse();

    vector<pair<int, Vertex*>> LP(Vertex *v);

    HalfEdge* findEdge(int face, Vertex *v);
};

#endif