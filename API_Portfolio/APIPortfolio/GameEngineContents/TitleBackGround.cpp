#include "TitleBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

TitleBackGround::TitleBackGround()
{
	// Level_ = nullptr;
}

TitleBackGround::~TitleBackGround()
{
}

void TitleBackGround::Start()
{
	SetPosition(GameEngineWindow::GetScale().Half());

	CreateRenderer("Title.bmp");
}

void TitleBackGround::Render()
{
	//DebugRectRender();
}