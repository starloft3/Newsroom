#ifndef __DOCUMENT_CONTAINER_H__
#define __DOCUMENT_CONTAINER_H__

#include "cocos2d.h"

class DocumentContainer
{
public:
	DocumentContainer();
	~DocumentContainer();

	void WarpToSpawnPoint();

	cocos2d::CCSprite* GetSprite();
	void SetSprite(cocos2d::CCSprite* sprite);
	bool GetIsBeingDragged();
	void SetIsBeingDragged(bool isBeingDragged);

private:
	cocos2d::CCSprite* mDocumentSprite;
	bool mIsDraggingDocument;
};

#endif // __NEWSROOM_H__
