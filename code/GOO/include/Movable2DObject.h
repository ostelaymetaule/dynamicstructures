#pragma once

#include "Main.h"


class Movable2DObject
{
public:
	Movable2DObject(std::string& name, Ogre::SceneManager* sceneMgr, Ogre::Vector2& position = Ogre::Vector2(0,0));
	~Movable2DObject(void);

	Ogre::Vector3& getVelocity(void); 
	Ogre::Vector3& getHeading(void); 

	Object2DType type; //to allow casting

protected:
	bool mActive;

	std::string mName;
	Ogre::Vector2 mPos;
	double mScale; 

	Ogre::SceneManager* mSceneMgr;
	Ogre::SceneNode* mNode; 
	Ogre::Entity* mEntity;	

private:



};