#ifndef FIELD_H
#define FIELD_H

#include "common.h"

class Place;

class Field
{
    Place* placeArray;
    unsigned width;
    unsigned height;
    unsigned unit;
    Point2i offset;
    Point2i maxOffset;

#ifdef QT_UI
    QPainter *painter;
public:
    void setPainter(QPainter *painter);
#endif

private:
    unsigned placeCount();

public:
    Field();
    Field(unsigned width, unsigned height, float unit = 20.0, float xOffset = 0.0, float yOffset = 0.0);
    Place* getPlaceAtPosition(Point2i pos);
    Place* getPlaceForTouchPoint(Point2i pos);
    bool getPathBetweenPlaces(Place* startPlace,Place* destPlace, Place ***routePlaces, unsigned &routeLength);
    
    void Draw(float dTime);
    Point2i getOffset();
    unsigned getUnit(){return this->unit;}
    void setOffset(Point2i offset);
    
    bool isAnimating();
    bool checkWinCondition();
    
    void clean(int difficulty = 10);
    
    void serializeForColorSaving(char** array, int& arraySize);
    void deserializeForColorLoading(char* array, int arraySize);
    
    ~Field();
};

#endif // FIELD_H
