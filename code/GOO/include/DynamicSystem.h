#pragma once

#include "Movable2DObject.h"

class DynamicSystem: public Movable2DObject
{
public:
	DynamicSystem(std::string& name, Ogre::SceneManager* sceneMgr, Ogre::Vector2& position);
	~DynamicSystem(void);
};