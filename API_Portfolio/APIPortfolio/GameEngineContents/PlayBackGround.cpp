#include "PlayBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayBackGround::PlayBackGround() 
{
}

PlayBackGround::~PlayBackGround() 
{
}

void PlayBackGround::Start()
{
	GameEngineRenderer* Render = CreateRendererToScale("Level1.bmp", { 1280,740 });
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
}

void PlayBackGround::Render()
{
	DebugRectRender();
}
