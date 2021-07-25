#include "CollisionHandler.h"

#include "Player.h"
#include "Treat.h"
#include "Button.h"
#include "Switch.h"
#include "House.h"
#include "Box.h"
#include "MirrorBox.h"
#include "Obstacle.h"
#include "Floor.h"

namespace
{
    void playerObstacleStart(GameObject* p, GameObject* o)
    {
        auto player = static_cast<Player*>(p);
        auto obstacle = static_cast<Obstacle*>(o);
        player->startContact(obstacle);
    }

    void playerTreatStart(GameObject* p, GameObject* t)
    {
        auto player = static_cast<Player*>(p);
        auto treat = static_cast<Treat*>(t);
        player->startContact(treat);
    }

    void playerButtonStart(GameObject* p, GameObject* b)
    {
        auto player = static_cast<Player*>(p);
        auto button = static_cast<Button*>(b);
        player->startContact(button);
    }

    void playerSwitchStart(GameObject* p, GameObject* s)
    {
        auto player = static_cast<Player*>(p);
        auto switchObj = static_cast<Switch*>(s);
        player->startContact(switchObj);
    }

    void boxButtonStart(GameObject* bo, GameObject* bu)
    {
        auto box = static_cast<Box*>(bo);
        auto button = static_cast<Button*>(bu);
        box->startContact(button);
    }

    void mirrorBoxButtonStart(GameObject* m, GameObject* b)
    {
        auto box = static_cast<MirrorBox*>(m);
        auto button = static_cast<Button*>(b);
        box->startContact(button);
    }

    void obstaclePlayerStart(GameObject* o, GameObject* p)
    {
        playerObstacleStart(p, o);
    }

    void treatPlayerStart(GameObject* t, GameObject* p)
    {
        playerTreatStart(p, t);
    }

    void buttonPlayerStart(GameObject* b, GameObject* p)
    {
        playerButtonStart(p, b);
    }

    void switchPlayerStart(GameObject* s, GameObject* p)
    {
        playerSwitchStart(p, s);
    }

    void buttonBoxStart(GameObject* bu, GameObject* bo)
    {
        boxButtonStart(bo, bu);
    }

    void buttonMirrorBoxStart(GameObject* b, GameObject* m)
    {
        mirrorBoxButtonStart(m, b);
    }

    void playerButtonEnd(GameObject* p, GameObject* b)
    {
        auto player = static_cast<Player*>(p);
        auto button = static_cast<Button*>(b);
        player->endContact(button);
    }

    void boxButtonEnd(GameObject* bo, GameObject* bu)
    {
        auto box = static_cast<Box*>(bo);
        auto button = static_cast<Button*>(bu);
        box->endContact(button);
    }

    void mirrorBoxButtonEnd(GameObject* m, GameObject* b)
    {
        auto box = static_cast<MirrorBox*>(m);
        auto button = static_cast<Button*>(b);
        box->endContact(button);
    }

    void buttonPlayerEnd(GameObject* b, GameObject* p)
    {
        playerButtonEnd(p, b);
    }

    void buttonBoxEnd(GameObject* bu, GameObject* bo)
    {
        boxButtonEnd(bo, bu);
    }

    void buttonMirrorBoxEnd(GameObject* b, GameObject* m)
    {
        mirrorBoxButtonEnd(m, b);
    }
}

HitMap CollisionHandler::initializeStartCollisionMap()
{
    HitMap hmPtr;
    hmPtr[Key(typeid(Player), typeid(Obstacle))] = &playerObstacleStart;
    hmPtr[Key(typeid(Player), typeid(Treat))] = &playerTreatStart;
    hmPtr[Key(typeid(Player), typeid(Button))] = &playerButtonStart;
    hmPtr[Key(typeid(Player), typeid(Switch))] = &playerSwitchStart;
    hmPtr[Key(typeid(Box), typeid(Button))] = &boxButtonStart;
    hmPtr[Key(typeid(MirrorBox), typeid(Button))] = &mirrorBoxButtonStart;
    hmPtr[Key(typeid(Obstacle), typeid(Player))] = &obstaclePlayerStart;
    hmPtr[Key(typeid(Treat), typeid(Player))] = &treatPlayerStart;
    hmPtr[Key(typeid(Button), typeid(Player))] = &buttonPlayerStart;
    hmPtr[Key(typeid(Switch), typeid(Player))] = &switchPlayerStart;
    hmPtr[Key(typeid(Button), typeid(Box))] = &buttonBoxStart;
    hmPtr[Key(typeid(Button), typeid(MirrorBox))] = &buttonMirrorBoxStart;

    return hmPtr;
}

HitMap CollisionHandler::initializeEndCollisionMap()
{
    HitMap hmPtr;
    hmPtr[Key(typeid(Player), typeid(Button))] = &playerButtonEnd;
    hmPtr[Key(typeid(Box), typeid(Button))] = &boxButtonEnd;
    hmPtr[Key(typeid(MirrorBox), typeid(Button))] = &mirrorBoxButtonEnd;
    hmPtr[Key(typeid(Button), typeid(Player))] = &buttonPlayerEnd;
    hmPtr[Key(typeid(Button), typeid(Box))] = &buttonBoxEnd;
    hmPtr[Key(typeid(Button), typeid(MirrorBox))] = &buttonMirrorBoxEnd;

    return hmPtr;
}

HitFunctionPtr CollisionHandler::lookup(const std::type_index& class1, const std::type_index& class2, bool isStart)
{
    static HitMap collisionMap;
    if (isStart)
    {
        collisionMap = initializeStartCollisionMap();
    }
    else
    {
        collisionMap = initializeEndCollisionMap();
    }
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

CollisionHandler& CollisionHandler::getCollisionHandler()
{
    static CollisionHandler collisionHandler;
    return collisionHandler;
}

void CollisionHandler::processCollision(GameObject* object1, GameObject* object2, bool isStart)
{
    auto hfPtr = lookup(typeid(*object1), typeid(*object2), isStart);
    if (!hfPtr)
    {
        return;
    }
    hfPtr(object1, object2);
}