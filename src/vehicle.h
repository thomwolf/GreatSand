/***********************************************************************
vehicle.h - vehicle class (fires moving in the sandbox)
Copyright (c) 2016 Thomas Wolf

This file is part of the Magic Sand.

The Magic Sand is free software; you can redistribute it
and/or modify it under the terms of the GNU General Public License as
published by the Free Software Foundation; either version 2 of the
License, or (at your option) any later version.

The Magic Sand is distributed in the hope that it will be
useful, but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
General Public License for more details.

You should have received a copy of the GNU General Public License along
with the Augmented Reality Sandbox; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
***********************************************************************/

#pragma once
#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxCv.h"

#include "KinectProjector/KinectProjector.h"

class Vehicle{

public:
    Vehicle(std::shared_ptr<KinectProjector> const& k, ofPoint slocation, ofRectangle sborders, float sangle);
    
    // Virtual functions
    virtual void setup() = 0;
    virtual void applyBehaviours() = 0;
    virtual void draw() = 0;
    
    void update();
    
    std::vector<ofVec2f> getForces(void);
    
    const ofPoint& getLocation() const {
        return location;
    }
    const ofPoint& getVelocity() const {
        return velocity;
    }
    
    const float getAngle() const {
        return angle;
    }
    
protected:
    void updateBeachDetection();
    ofPoint bordersEffect();
    ofPoint slopesEffect();
	ofPoint hillEffect();
	ofPoint windEffect(float windspeed, float winddirection);
    virtual ofPoint wanderEffect();
    void applyVelocityChange(const ofPoint & force);
    
    std::shared_ptr<KinectProjector> kinectProjector;

    ofPoint location;
    ofPoint velocity;
    ofPoint globalVelocityChange;
    ofVec2f currentForce;
    float angle; // direction of the drawing
    
    ofVec2f separateF ;
    ofVec2f bordersF ;
    ofVec2f slopesF ;
    ofVec2f wanderF ;
	ofVec2f hillF;
	ofVec2f windF;

    bool beach;
    bool border;
    
    // For slope effect
    float beachDist;
    ofVec2f beachSlope;
    
    ofVec2f projectorCoord;
    ofRectangle borders, internalBorders;
    float maxVelocityChange;
    float maxRotation;
    int r, minborderDist, desiredseparation, cor;
    
    float wanderR ;         // Radius for our "wander circle"
    float wanderD ;         // Distance for our "wander circle"
    float change ;
    float wandertheta;
    float topSpeed;
};


class Fire : public Vehicle {
public:
    Fire(std::shared_ptr<KinectProjector> const& k, ofPoint slocation, ofRectangle sborders) : Vehicle(k, slocation, sborders, 0){}

    Fire(std::shared_ptr<KinectProjector> const& k, ofPoint slocation, ofRectangle sborders, float sangle) : Vehicle(k, slocation, sborders, sangle){}

    void setup();
    void applyBehaviours();
	void applyBehaviours(float temp, float windspeed, float winddirection);
    void draw();

    const bool isAlive() const {
        return alive;
    }

    int getIntensity() {
        return intensity;
    }
    
    void kill();

private:
    ofPoint wanderEffect();

    ofColor getFlameColor();

    int maxStraightPath; // max rabbit straight path length
    int currentStraightPathLength;// current rabbit straight path length
    int intensity;
    
    float velocityIncreaseStep; // Rabbit increase step
    float minVelocity;
	bool alive;
};

