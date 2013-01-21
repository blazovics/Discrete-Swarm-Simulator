#ifndef SCENE_H
#define SCENE_H

#include "common.h"
#include <set>
#include <list>

using namespace std;

class Field;
class Entity;
class PlayerEntity;

typedef enum
{
    gameStateUnitAdd,
    gameStateUnitSelect,
    gameStateUnitDestination
}SceneState;

class Scene
{
    Field* field;
    set<Entity*> entities;
    list<Point2i> touches;
    PlayerEntity* playerEntity;
    
    SceneState sceneState;
    Entity* selectedEntity;

#ifdef QT_UI
    QPainter* painter;
public:
    void setPainter(QPainter *painter);
#endif

public:
    Scene(unsigned fieldWidth, unsigned fieldHeight, unsigned unitWidth = 0, int xOffset = 0, int yOffset = 0);
    void addEntityAtPosition(Entity* entity,Point2i point);
    void handleTouchEvent(Point2i touchPoint);

    Point2i getOffset();
    void setOffset(Point2i offset);
    
    ~Scene();
    void Step();
    void Draw(float dTime);
    
    void saveScene();
    void loadScene();
    
    void undo();
    
    void startNewGame(int difficulity = 0);
};

#endif // SCENE_H
