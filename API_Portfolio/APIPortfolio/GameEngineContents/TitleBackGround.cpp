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
	GameEngineRenderer* Render = CreateRendererToScale("Title.bmp", { 1280,740 });
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
}

void TitleBackGround::Render()
{
	DebugRectRender();
}