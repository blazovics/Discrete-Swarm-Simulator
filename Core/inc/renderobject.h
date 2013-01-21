#ifndef RENDEROBJECT_H
#define RENDEROBJECT_H

#include "common.h"

#ifdef MARMALADE_UI

#include "s3e.h"
#include "Iw2D.h"

#endif

class RenderObject
{
public:
    RenderObject();
protected:
    Point2f onScreenPos;

    //for moving animation only
    bool animating;
    Point2f animationPosition;
    
    float animationRemainTime;

public:
    Point2f getOnScreenPos();
    void setOnScreenPos(Point2f newPos);
    virtual void Draw(float dTime);
    virtual void Animate(float dTime);

#ifdef MARMALADE_UI
protected:
	CIwMat2D Transform;
    CIwColour color;
public:
    virtual void setDefaultColor();
    void setColor(CIwColour color);
    CIwColour getColor();
    
    bool getAnimating();
#endif

#ifdef QT_UI
protected:
    QBrush brush;
    QPainter *painter;
public:
    void setPainter(QPainter *painter);
    void setBrush(const QBrush &brush);
#endif

};

#endif // RENDEROBJECT_H
