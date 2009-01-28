#include "Cell.h"
#include "CellSystem.h"

Cell::Cell(std::string name, unsigned int id,Ogre::SceneManager* sceneMgr, CellSystem* cellSystem, Ogre::Vector2 position):
mName(name), mID(id), mPos(position), mSceneMgr(sceneMgr), mSystem(cellSystem)
{
	
	node= sceneMgr->getSceneNode("CanvasRootNode")->createChildSceneNode(name + "_node"); 
	
	//TODO: ELABORATE PROPERTIES!
	//TODO: Replace with CellSystem->getProperties(); 
	switch(cellSystem->getLocalProperties()->getCellType())
	{
		case CELLTYPE::SQUARE:
			outlineEntity= mSceneMgr->createEntity(name +"_entity", SQUARE_LINE_MESH); 		
			mDirectionInterval= Math::TWO_PI /4;
			break;
		case CELLTYPE::HEXAGON:
			outlineEntity= mSceneMgr->createEntity(name +"_entity", HEXAGON_LINE_MESH); 
			mDirectionInterval= Math::TWO_PI /6;
			break;
		case CELLTYPE::CIRCLE:
			outlineEntity= mSceneMgr->createEntity(name +"_entity", CIRCLE_LINE_MESH); 	
			mDirectionInterval= Math::TWO_PI /8;
			break;
		default:
			break;
	}

	//mProperties= retrieveProperties(mSystem); 
	Ogre::Real size;
	
	size = cellSystem->getLocalProperties()->getCellSize(); 

	node->setVisible(true); 
	node->scale(Vector3(size,size,size)); 
	node->setPosition(position.x,position.y,0); 
	node->attachObject(outlineEntity); 
	mDivideDirection= Radian(0);
	mCloneIntervalTime = 0.1;
	mTimePassed=0.0;


}



Cell::~Cell(void)
{

}

bool Cell::frameStarted(const FrameEvent &evt)
{
	mTimePassed+=evt.timeSinceLastFrame;

	if (mTimePassed > mCloneIntervalTime){
		mTimePassed=0.0;
		divide(); 
	}

return true;
}

bool Cell::frameEnded(const FrameEvent &evt)
{

return true;
}

void Cell::divide()
{
	Cell* myClone;
	//spawn new cell
	myClone= mSystem->requestCell(); 
	//initialize the new clone: 
	Ogre::Vector2 position;
	position.x = mPos.x + Math::Cos(mDivideDirection)* (mSize * 0.7);
	position.y = mPos.y + Math::Sin(mDivideDirection)* (mSize * 0.7);
	myClone->setPosition(position); 

	//set divide angle: 
	mDivideDirection+= mDirectionInterval;
}


CellProperties  Cell::retrieveProperties(CellSystem* system)
{
	CellProperties properties;
	
	return properties;
}
	