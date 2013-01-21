#include "renderobject.h"

RenderObject::RenderObject()
{
#ifdef MARMALADE_UI
    this->color.Set(0xff0000ff);
#endif

}

Point2f RenderObject::getOnScreenPos()
{
    return this->onScreenPos;
}

void RenderObject::setOnScreenPos(Point2f newPos)
{
    this->onScreenPos = newPos;
}

bool RenderObject::getAnimating()
{
    return this->animating;
}

void RenderObject::Animate(float dTime)
{
    
}

#ifdef QT_UI

void RenderObject::setPainter(QPainter *painter)
{
    this->painter = painter;
}

void RenderObject::setBrush(const QBrush &brush)
{
    this->brush = brush;
}

#endif

#ifdef MARMALADE_UI

void RenderObject::setDefaultColor()
{
    color.Set(0xffffffff);
}

void RenderObject::setColor(CIwColour color)
{
    this->color = color;
}

CIwColour RenderObject::getColor()
{
    return this->color;
}

#endif

void RenderObject::Draw(float dTime)
{

#ifdef MARMALADE_UI
    
    CIwSVec2 Position(onScreenPos.x, onScreenPos.y);
 
    // Build the transform
	// Set the rotation transform
	Transform.SetRot(0);
	// Scale the transform
	Transform.ScaleRot(0);
	// Translate the transform
	Transform.SetTrans(Position);
	// Set this transform as the active transform for Iw2D
	Iw2DSetTransformMatrix(Transform);
    
#endif

}


