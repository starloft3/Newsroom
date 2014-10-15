#include "DocumentContainer.h"
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
Newsroom::~Newsroom()
{
	if ( mDocumentContainer != NULL )
	{
		delete mDocumentContainer;
	}
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

	// Create the game objects
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    /////////////////////////////

    // add "Newsroom" background
    CCSprite* pSprite = CCSprite::create("background.jpg");
    pSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	this->addChild(pSprite, BACKGROUND);

	// add Document
	mDocumentContainer = new DocumentContainer();
	CCSprite* documentSprite = CCSprite::create("DocumentTemplate.jpg");
	this->addChild(documentSprite, GAME_LAYER);
	mDocumentContainer->SetSprite(documentSprite);
	mDocumentContainer->WarpToSpawnPoint();
	mDocumentContainer->GetSprite()->setVisible(false);

	/////////////////////////////

	// This needs to be called in order to use touch events
	setTouchEnabled(true);

	// This needs to be called in order for update to be called.
	scheduleUpdate();
    
    return true;
}

//
void Newsroom::update(float dt)
{
	static float timer = 3.0;
	bool shouldShow = mDocumentContainer->IsInteractable();
	mDocumentContainer->GetSprite()->setVisible(shouldShow);

	// Simulate "finding a new story"
	if ( mDocumentContainer->GetDocument() == NULL )
	{
		timer -= dt;
		if ( timer < 0 )
		{
			mDocumentContainer->SpawnNewDocument();
			timer = 3.0;
		}
	}
}

//
void Newsroom::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
    CCSetIterator it = pTouches->begin();
    CCTouch* touch = (CCTouch*)(*it);
    CCPoint location = touch->getLocation();
    if(mDocumentContainer->IsInteractable() && mDocumentContainer->GetSprite()->boundingBox().containsPoint(location))
    {
        mDocumentContainer->SetIsBeingDragged(true);
		mDocumentContainer->GetSprite()->setPosition(ccp(location.x, location.y));
    }
}

//
void Newsroom::ccTouchesMoved(CCSet *pTouches, CCEvent *pEvent)
{
    if (mDocumentContainer->IsInteractable() && mDocumentContainer->GetIsBeingDragged())
    {
		CCSetIterator it = pTouches->begin();
		CCTouch* touch = (CCTouch*)(*it);
		CCPoint location = touch->getLocation();
		mDocumentContainer->GetSprite()->setPosition(ccp(location.x, location.y));
    }
	else
	{
		mDocumentContainer->SetIsBeingDragged(false);
		mDocumentContainer->WarpToSpawnPoint();
	}
}

//
void Newsroom::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
    mDocumentContainer->SetIsBeingDragged(false);
	mDocumentContainer->WarpToSpawnPoint();
}
