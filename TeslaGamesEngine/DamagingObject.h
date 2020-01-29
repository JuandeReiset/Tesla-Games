#pragma once

#include "Object.h"
#include "DamageComponent.h"

/*
 * DamagingOblject class inherits from Object class, representing objects, e.g., bullet, spikes, that can cause damages 
 */
class DamagingObject : Object
{
public:
    DamagingObject();
    DamagingObject(double d);
    ~DamagingObject();
    
    void Tick(float deltaTime);
    double sendDamage(float deltaTime);

private:
    DamageComponent damage;
};

