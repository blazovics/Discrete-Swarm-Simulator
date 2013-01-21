#include "swarmentity.h"
#include "place.h"
#include "field.h"

SwarmEntity::SwarmEntity() : Entity()
{
    this->targetEntity = NULL;
    this->targetDistance = 0;
}

void SwarmEntity::setTargetEntity(Entity* targetEntity)
{
    this->targetEntity = targetEntity;
}

void SwarmEntity::Step()
{
    if(this->targetEntity == NULL)
    {
        //In order to keep the entity in a given place
        this->desiredPlace = this->currentPlace;
        return;

        //choose a neighbor
        unsigned freeNbSize = 0;
        char* neighbors = NULL;

        currentPlace->getFreeNextNeighbors(&neighbors,freeNbSize);

        //genrate random number
        if (freeNbSize > 0){
            int randomNumber = rand();
            unsigned index = randomNumber % freeNbSize;
            unsigned newID = neighbors[index];
            Place* newPlace = currentPlace->getNeighbor(newID);

            //Point2i p = newPlace->getPosition();
            //std::cout<<"possible places: "<<freeNbSize<<" randomNum: "<<randomNumber<<" index: "<<index<<" new place: "<<newID<<" "<<p.x<<" "<<p.y<<endl;

            this->desiredPlace = newPlace;
            newPlace->setNextEntity(this);
            delete [] neighbors;
        }

        this->desiredPlace = this->currentPlace;
        return;
    }

    if(this->targetEntity->getCurrentPlace() == NULL)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    neighborhoodType nType = same;

    Place::entityDistance(this->currentPlace,this->targetEntity->getCurrentPlace(),this->targetDistance, nType);

    if(nType == same)
    {
        this->desiredPlace = this->currentPlace;
        return;
    }

    headingDir = this->calculateHeadingDirection();

    neighborType nextNeighbor;

    //circulation only
    if(nType < 6)
    {
        neighborType lookAtN = (neighborType)nType;

        if(headingDir == rightHeading)
        {
             if(lookAtN == leftNeighbor)
             {
                 nextNeighbor = bottomLeftNeighbor;
            }
             else
             {
                 nextNeighbor = (neighborType)((int)nType-1);
             }
        }
        else
        {
            if(lookAtN == bottomLeftNeighbor)
            {
                nextNeighbor = leftNeighbor;
            }
            else
            {
                nextNeighbor = (neighborType)((int)nType+1);
            }
        }
    }
    else if(nType > 6)
    {
        if(headingDir == rightHeading)
        {
            if(nType == l_tl_Neighbor)
            {
                if(currentPlace->getNeighbor(rightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomRightNeighbor;
                }
                else
                {
                    nextNeighbor = topRightNeighbor;
                }
            }
            else if(nType == tl_tr_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
                else
                {
                    nextNeighbor = rightNeighbor;
                }
            }
            else if(nType == tr_r_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = leftNeighbor;
                }
                else
                {
                    nextNeighbor = bottomRightNeighbor;
                }
            }
            else if(nType == r_br_Neighbor)
            {
                if(currentPlace->getNeighbor(leftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topLeftNeighbor;
                }
                else
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
            }
            else if(nType == br_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(topLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topRightNeighbor;
                }
                else
                {
                    nextNeighbor = leftNeighbor;
                }
            }
            else if(nType == l_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(topRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = rightNeighbor;
                }
                else
                {
                    nextNeighbor = topLeftNeighbor;
                }
            }
        }
        else
        {
            if(nType == l_tl_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = rightNeighbor;
                }
                else
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
            }
            else if(nType == tl_tr_Neighbor)
            {
                if(currentPlace->getNeighbor(bottomLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomRightNeighbor;
                }
                else
                {
                    nextNeighbor = leftNeighbor;
                }
            }
            else if(nType == tr_r_Neighbor)
            {
                if(currentPlace->getNeighbor(leftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = bottomLeftNeighbor;
                }
                else
                {
                    nextNeighbor = topLeftNeighbor;
                }
            }
            else if(nType == r_br_Neighbor)
            {
                if(currentPlace->getNeighbor(topLeftNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = leftNeighbor;
                }
                else
                {
                    nextNeighbor = topRightNeighbor;
                }
            }
            else if(nType == br_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(topRightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topLeftNeighbor;
                }
                else
                {
                    nextNeighbor = rightNeighbor;
                }
            }
            else if(nType == l_bl_Neighbor)
            {
                if(currentPlace->getNeighbor(rightNeighbor)->getEntity() == NULL)
                {
                    nextNeighbor = topRightNeighbor;
                }
                else
                {
                    nextNeighbor = bottomRightNeighbor;
                }
            }
        }
    }

    Place* nextPlace = this->currentPlace->getNeighbor(nextNeighbor);

    this->desiredPlace = nextPlace;
}

headingDirection SwarmEntity::calculateHeadingDirection()
{
    if(this->targetDistance % 2 == 0)
    {
        return leftHeading;
    }
    else{
        return rightHeading;
    }
}

void SwarmEntity::Draw(float dTime)
{
    Animate(dTime);
    if(this->currentPlace == NULL)
        return;

    float unit = this->currentPlace->getParentField()->getUnit();
    float height = sqrt(3)/2*unit;

    Point2f placePos;
    
    if(animating)
    {
        placePos = this->animationPosition;
    }
    else
    {
        placePos = this->currentPlace->getOnScreenPos();
    }
    
    Point2i offset = this->currentPlace->getParentField()->getOffset();

#ifdef QT_UI

    painter->setPen(QPen(QColor(100,100,100)));

    painter->setBrush(this->brush);
    painter->save();
    painter->translate(placePos.x, placePos.y);

    painter->drawEllipse(QPoint(height,unit),(int)(unit/2),(int)(unit/2));
    painter->restore();

#endif
    
#ifdef MARMALADE_UI
    CIwSVec2 Position(placePos.x-offset.x, placePos.y-offset.y);

    // Build the transform
	// Set the rotation transform
	Transform.SetRot(0);
	// Scale the transform
	Transform.ScaleRot(IW_GEOM_ONE);
	// Translate the transform
	Transform.SetTrans(Position);
	// Set this transform as the active transform for Iw2D
	Iw2DSetTransformMatrix(Transform);
    
    Iw2DSetColour(0xffffffff); // Set red
    
    Iw2DFillArc(CIwSVec2(height, unit), CIwSVec2((unit/2), (unit/2)), 0, IW_ANGLE_2PI);

#endif
}
