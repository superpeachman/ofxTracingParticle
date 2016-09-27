//
//  Particles.cpp
//
//
//  Created by Toshiya Momota on 1/6/16.
//
//

#include "Particles.h"

Particles::Particles(Grid &_grid){
    grid = &_grid;
    pSize = grid->getPanelSize();//Resolusion
    
    auto screenW = ofGetWidth();
    auto screenH = ofGetHeight();
    
    for(int i=0;i<_grid.getPanelNumber();i++){
        par.emplace_back(*new Particle(speed, screenW, screenH));
    }
    
    auto initTime = ofGetElapsedTimef();
    for(int i=0;i<par.size();i++){
        if(i<grid->getPanelNumber()){
            par[i].setGoal(grid->getByIndex(i), grid->getPanelColor(i), initTime);
        }
    }
}
void Particles::update(){
    for(int i=0; i < par.size();i++){
        par[i].update();
    }
    
    mesh.clear();
    
    for(int i=0; i<par.size(); i++){
        ofVec3f pos = par[i].getLocation();
        auto val = 100;

        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y, pos.z));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z));             
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y, pos.z));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y, pos.z));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));

        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));

        
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z-pSize));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z-pSize));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z-pSize));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z-pSize));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z));
        mesh.addVertex(ofVec3f(pos.x, pos.y, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));

        
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z-pSize));
        mesh.addVertex(ofVec3f(pos.x, pos.y+pSize, pos.z));
        mesh.addVertex(ofVec3f(pos.x+pSize, pos.y+pSize, pos.z));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
        mesh.addColor(ofColor(val));
    }
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    mesh.setupIndicesAuto();//Set up indices
    setNormals(mesh);
}
void Particles::draw(){
    mesh.draw();
}
void Particles::setSpeed(int _speed){
    speed = _speed;
    
    for(int i=0;i<par.size();i++){
        par[i].setSpeed(speed);
    }
}
void Particles::setGoals(Grid &_grid){
    grid = &_grid;
    auto screenW = ofGetScreenWidth();
    auto screenH = ofGetScreenHeight();
    auto initTime = ofGetElapsedTimef();
    
    if(grid->getPanelNumber() < par.size()) {
        par.erase(par.begin() + grid->getPanelNumber(), par.begin() + par.size() );
        vector<Particle> (par).swap(par);
        //cout << "2:par.size():" << par.size() << "\n";
    }
    
    for(int i=0; i<grid->getPanelNumber(); i++){
        if(i<par.size()){
            //cout << "Speed1:" << speed << "\n";
            par[i].setGoal(grid->getByIndex(i), grid->getPanelColor(i), initTime);
            //cout << i << ": YES? \n";
        }else{
            //cout << "Speed2:" << speed << "\n";
            //par.push_back(*new Particle(speed, screenW, screenH));
            par.emplace_back(*new Particle(speed, screenW, screenH));
            par[i].setGoal(grid->getByIndex(i), grid->getPanelColor(i), initTime);
            //cout << i << ": NO? \n";
        }
    }
}
int Particles::getParticleNumber(){
    return par.size();
}

//--------------------------------------------------------------
void Particles::setNormals( ofMesh &mesh ){
    
    //The number of the vertices
    int nV = mesh.getNumVertices();
    
    //The number of the triangles
    int nT = mesh.getNumIndices() / 3;
    
    vector<ofPoint> norm( nV );			//Array for the normals
    
    //Scan all the triangles. For each triangle add its
    //normal to norm's vectors of triangle's vertices
    for (int t=0; t<nT; t++) {
        
        //Get indices of the triangle t
        int i1 = mesh.getIndex( 3 * t );
        int i2 = mesh.getIndex( 3 * t + 1 );
        int i3 = mesh.getIndex( 3 * t + 2 );
        
        //Get vertices of the triangle
        const ofPoint &v1 = mesh.getVertex( i1 );
        const ofPoint &v2 = mesh.getVertex( i2 );
        const ofPoint &v3 = mesh.getVertex( i3 );
        
        //Compute the triangle's normal
        ofPoint dir = ( (v2 - v1).crossed( v3 - v1 ) ).normalized();
        
        //Accumulate it to norm array for i1, i2, i3
        norm[ i1 ] += dir;
        norm[ i2 ] += dir;
        norm[ i3 ] += dir;
    }
    
    //Normalize the normal's length
    for (int i=0; i<nV; i++) {
        norm[i].normalize();
    }
    
    //Set the normals to mesh
    mesh.clearNormals();
    mesh.addNormals( norm );
}

