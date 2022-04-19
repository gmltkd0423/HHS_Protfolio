#include "TitleBackGround.h"
#include "TitleTime.h"
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
	CreateRendererToScale("TitleBackGround.bmp", { 1280,740 });
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
}

void TitleBackGround::Update()
{
}

void TitleBackGround::Render()
{
	//DebugRectRender();
}