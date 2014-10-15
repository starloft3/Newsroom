#ifndef __DOCUMENT_CONTAINER_H__
#define __DOCUMENT_CONTAINER_H__

#include "cocos2d.h"

class Document;

class DocumentContainer
{
public:
	DocumentContainer();
	~DocumentContainer();

	void SpawnNewDocument();
	void WarpToSpawnPoint();
	bool IsInteractable();

	Document* GetDocument();
	cocos2d::CCSprite* GetSprite();
	void SetSprite(cocos2d::CCSprite* sprite);
	bool GetIsBeingDragged();
	void SetIsBeingDragged(bool isBeingDragged);

private:
	Document* mActiveDocument;
	cocos2d::CCSprite* mDocumentSprite;
	bool mIsDraggingDocument;
};

#endif // __NEWSROOM_H__
