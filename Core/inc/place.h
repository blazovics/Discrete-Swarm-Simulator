#ifndef PLACE_H
#define PLACE_H

#include "common.h"
#include "renderobject.h"

class Field;
class Entity;

typedef enum{
    leftNeighbor = 0,
    topLeftNeighbor = 1,
    topRightNeighbor = 2,
    rightNeighbor = 3,
    bottomRightNeighbor = 4,
    bottomLeftNeighbor = 5
}neighborType;

typedef enum{
    same = 6,
    l_Neighbor = rightNeighbor, //circulates only (CO)
    l_tl_Neighbor = 7,
    tl_Neighbor = bottomRightNeighbor, //circulates only (CO)
    tl_tr_Neighbor = 8,
    tr_Neighbor = bottomLeftNeighbor, //circulates only (CO)
    tr_r_Neighbor = 9,
    r_Neighbor = leftNeighbor, //circulates only (CO)
    r_br_Neighbor = 10,
    br_Neighbor = topLeftNeighbor, //circulates only (CO)
    br_bl_Neighbor = 11,
    bl_Neighbor = topRightNeighbor, //circulates only (CO)
    l_bl_Neighbor = 12
}neighborhoodType;

class Place:public RenderObject
{ 
private:
    Field* parentField;
    
    Point2i position;
    unsigned unit;
    Place* neighbors[6];
    Entity* entity;

    Entity* nextEntity;

public:
    Place();
    void setNeighbor(Place* neighbor, neighborType type);
    Place* getNeighbor(neighborType type);
    Place* getNeighbor(unsigned neighborID);

    void getFreeNeighbors(char** neighborIDArray, unsigned& size);
    void getFreeNeighbors(char** neighborIDArray, unsigned& size, Entity* ignorableEntity);

    void setPosition(Point2i position);
    Point2i getPosition();
    
    void setUnitDistance(unsigned unit);
    unsigned getUnitDistance();
    
    void setParentField(Field* field);
    Field* getParentField();

    void setEntity(Entity* entity);
    Entity *getEntity();

    void setNextEntity(Entity* entity);
    Entity *getNextEntity();
    
    void setDefaultColor();

    void getFreeNextNeighbors(char ** neighborIDArray, unsigned& size);

    static void entityDistance(Place* firstPlace, Place* secondPlace, unsigned& distance, neighborhoodType& nType);

    void Draw(float dTime);
    
    void invertColor();
};

#endif // PLACE_H
