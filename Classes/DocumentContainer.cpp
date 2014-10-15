#include "Document.h"
#include "DocumentContainer.h"

USING_NS_CC;

DocumentContainer::DocumentContainer() :
	mActiveDocument( NULL ),
	mDocumentSprite( NULL ),
	mIsDraggingDocument( false )
{
}

DocumentContainer::~DocumentContainer()
{
	mDocumentSprite = NULL;
	if ( mActiveDocument != NULL )
	{
		delete mActiveDocument;
	}
}

bool DocumentContainer::IsInteractable()
{
	return ( mActiveDocument != NULL );
}

void DocumentContainer::SpawnNewDocument()
{
	mActiveDocument = new Document();
}

void DocumentContainer::WarpToSpawnPoint()
{
	CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	mDocumentSprite->setPosition(ccp(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
}

Document* DocumentContainer::GetDocument()
{
	return mActiveDocument;
}

CCSprite* DocumentContainer::GetSprite()
{
	return mDocumentSprite;
}

void DocumentContainer::SetSprite(CCSprite* sprite)
{
	mDocumentSprite = sprite;
}

bool DocumentContainer::GetIsBeingDragged()
{
	return mIsDraggingDocument;
}

void DocumentContainer::SetIsBeingDragged(bool isBeingDragged)
{
	mIsDraggingDocument = isBeingDragged;
}
