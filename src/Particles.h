//
//  Particles.h
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#pragma once
#include "ofMain.h"
#include "Particle.h"
#include "Grid.h"

class Particles {
public:
    Particles(Grid &_grid);
    void update();
    void draw();
    void setGoals(Grid &_grid);
    void setSpeed(int speed);
    int getParticleNumber();
private:
    //for the triangle mesh
    void setNormals( ofMesh &mesh );
    vector<Particle> par;
    Grid *grid;
    ofMesh mesh;
    int pSize;
    float speed = 50;
};
