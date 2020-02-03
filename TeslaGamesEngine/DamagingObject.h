#pragma once

#include "Object.h"
#include "DamageComponent.h"
#include "Combat.h"
#include "Global.h"

/*
 * DamagingOblject class inherits from Object class, representing objects, e.g., bullet, spikes, that can cause damages 
 */
class DamagingObject : public Object
{
public:
    DamagingObject();
    DamagingObject(double d, int id);
    ~DamagingObject();
    
    void Tick(float deltaTime);
    double sendDamage();                                            //send damage to the combat class to give damage to the target vihecle
    int GetTargetId();
    void SetTargetId(int id);

private:
    DamageComponent damage;
    int targetID;
};

