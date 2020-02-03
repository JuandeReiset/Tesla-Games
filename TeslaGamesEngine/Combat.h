#pragma once

/*
 * Combat class only has one global instance to accept damages from damaging object and send it to the target vihecle
 */

class Combat
{
public:
    Combat() = default;
    void SetTargetID(int id);
    void SetDamage(double d);
    int GetTargetID();
    double GetDamage();

private:
    int targetID;                                                   
    double damage;                                                  
};

