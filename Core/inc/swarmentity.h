#ifndef SWARMENTITY_H
#define SWARMENTITY_H

#include "entity.h"

typedef enum{
    leftHeading,
    rightHeading
}headingDirection;

class SwarmEntity : public Entity
{
    unsigned targetDistance;
    headingDirection headingDir;

    Entity* targetEntity;

    headingDirection calculateHeadingDirection();

public:
    SwarmEntity();
    void setTargetEntity(Entity* targetEntity);
    void Step();
    void Draw(float dTime);

};

#endif // SWARMENTITY_H
