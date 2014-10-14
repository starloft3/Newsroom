#include "Newsroom.h"

USING_NS_CC;

enum SPRITE_DRAW_PRIORITY
{
	BACKGROUND = 0,
	GAME_LAYER,
};

CCScene* Newsroom::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Newsroom *layer = Newsroom::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

//
void Newsroom::reset()
{
	mDocumentSprite = NULL;
	mIsDraggingDocument = false;
}

// on "init" you need to initialize your instance
bool Newsroom::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

	reset();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////

    // add "Newsroom" background
    CCSprite* pSprite = CCSprite::create("background.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, BACKGROUND);

	// add Document
	mDocumentSprite = CCSprite::create("DocumentTemplate.jpg");
	this->addChild(mDocumentSprite, GAME_LAYER);
	warpDocumentToSpawnPoint();

	/////////////////////////////

	// This needs to be called in order to use touch events
	setTouchEnabled(true);
    
    return true;
}

void Newsroom::warpDocumentToSpawnPoint()
{
	if ( mDocumentSprite != NULL )
	{
		CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
		CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
		mDocumentSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	}
}

void Newsroom::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint location = touch->getLocation();
    if(mDocumentSprite->boundingBox().containsPoint(location))
    {
        mIsDraggingDocument = true;
		mDocumentSprite->setPosition(ccp(location.x, location.y));
    }
}

void Newsroom::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (mIsDraggingDocument)
    {
		CCSetIterator it = pTouches->begin();
		CCTouch* touch = (CCTouch*)(*it);
		CCPoint location = touch->getLocation();
		mDocumentSprite->setPosition(ccp(location.x, location.y));
    }
}

void Newsroom::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	mIsDraggingDocument = false;
	warpDocumentToSpawnPoint();
}
