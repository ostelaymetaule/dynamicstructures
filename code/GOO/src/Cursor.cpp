#include "Cursor.h"
#include "CellSystemProperties.h"
#include "Movable2DObject.h"

Cursor::Cursor(std::string& name, Canvas* canvas, Ogre::SceneManager* sceneMgr): 
mCanvas(canvas), mSceneMgr(sceneMgr) 
{

	mCursorNode= mCanvas->getSceneNode()->createChildSceneNode(); 
	mCursorEntity= mSceneMgr->createEntity(name,HEXAGON_LINE_MESH); 
	mCursorNode->attachObject(mCursorEntity); 
	mCursorNode->scale(10,10,10);
	acceleration= Vector2(0,0);
	mPos= Vector2(0,0); 
	mPressed=false;
	mSystemType=1; 
}

Cursor::~Cursor(void)
{

}

bool Cursor::update(const FrameEvent &evt)
{
	mCursorNode->roll(Ogre::Radian(2)*evt.timeSinceLastFrame); 	
	return true;
} 


bool Cursor::mouseMoved(const OIS::MouseEvent &e)
{
	//samples
	acceleration.x= (Ogre::Real)e.state.X.rel;
	acceleration.y= (Ogre::Real)e.state.Y.rel;
	
	if (acceleration.length() > 100.0)
			acceleration= 100.0 * acceleration.normalisedCopy(); 

	mPos.x+= acceleration.x; 
	mPos.y-= acceleration.y;

	mCursorNode->setPosition(Vector3(mPos.x, mPos.y, 0)); 


	
	
	




return true;
}

bool Cursor::mousePressed(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	//plant  seed
	if (mPressed==false)
	{
		switch(mSystemType){
		
			case 1:
			mCanvas->addCellSystem(mPos,"Square",true,1.0); 
			break;
		case 2:
			mCanvas->addCellSystem(mPos,"Hexagon",true,1.0); 
			break;
		case 3:
			mCanvas->addCellSystem(mPos,"Triangle",true,1.0); 
			break;
		case 4:
			mCanvas->addCellSystem(mPos,"Circle",true,1.0); 
			break;
		}
	}


	
	mPressed=true;
	return true;
}

bool Cursor::mouseReleased(const OIS::MouseEvent &e, OIS::MouseButtonID id)
{
	mPressed=false;

	return true;
}


unsigned int  Cursor::getCurrentCellModeID()
{
	return mSystemType; 
} 

void Cursor::setCreateType(unsigned int type)
{
	mSystemType = type;
}

void Cursor::setPosition(Ogre::Vector2& pos)
{
	mPos= pos;
	mCursorNode->setPosition(Vector3(mPos.x, mPos.y, 0)); 
}

void Cursor::attachObject(Movable2DObject* object)
{




}