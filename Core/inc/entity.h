#ifndef ENTITY_H
#define ENTITY_H

#include "common.h"
#include "renderobject.h"

class Place;

class Entity : public RenderObject
{

protected:

    Place* currentPlace;
    Place* desiredPlace;
    
    static float aspect;

public:
    Entity();
    virtual ~Entity();
    
    void setCurrentPlace(Place* place, bool forced = false);
    
    Place* getCurrentPlace();

    Place* getDesiredPlace();

    virtual void Draw(float dTime);
    virtual void Step();
    virtual void Animate(float dTime);
    virtual void PrepareForAnimation(Place* previousPlace, Place* nextPlace);
};

#endif // ENTITY_H
