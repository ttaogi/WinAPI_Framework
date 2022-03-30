#include "Stdafx/stdafx.h"

#include "Scene/FieldScene/FieldScene.h"

FieldScene::FieldScene() { }

FieldScene::~FieldScene() { }

void FieldScene::OnNotify(Subject* _subject, EVENT _event)
{
}

HRESULT FieldScene::Init()
{
	return E_NOTIMPL;
}

void FieldScene::Release()
{
	SAFE_DELETE(root);
}

void FieldScene::Update()
{
	SOUND->Update();

	root->Update();
}

void FieldScene::Render()
{
	HDC memDC = MAIN_GAME->GetMemDC();

	PatBlt(memDC, 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);

	backgroundImage->Render(memDC);

	priority_queue<Rendered*, vector<Rendered*>, CmpRenderedPtr> renderQue;

	root->CollectRendered(&renderQue);
	ProcessRender(memDC, &renderQue);
}
