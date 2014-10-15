#ifndef __NEWSROOM_H__
#define __NEWSROOM_H__

#include "cocos2d.h"

class DocumentContainer;

class Newsroom : public cocos2d::CCLayer
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	virtual ~Newsroom();

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::CCScene* scene();
    
	// implement the "static node()" method manually
    CREATE_FUNC(Newsroom);

	virtual void update(float dt);

	virtual void ccTouchesBegan(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesMoved(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);

private:
	DocumentContainer* mDocumentContainer;
};

#endif // __NEWSROOM_H__
