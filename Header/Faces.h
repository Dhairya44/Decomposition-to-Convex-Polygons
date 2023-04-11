/*! \file Faces.h
    \brief Contains the Face struct.
*/
#ifndef FACES_H
#define FACES_H
#include<bits/stdc++.h>
#include "Edges.h"
using namespace std;
struct HalfEdge;
struct Face{
    int id;
    vector<HalfEdge*> interComponent;
    Face();
    Face(int id, vector<HalfEdge*> interComponent);
};

#endif