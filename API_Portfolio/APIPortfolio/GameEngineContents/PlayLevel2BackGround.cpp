#include "PlayLevel2BackGround.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel2BackGround::PlayLevel2BackGround() 
{
}

PlayLevel2BackGround::~PlayLevel2BackGround() 
{
}

void PlayLevel2BackGround::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
}

void PlayLevel2BackGround::Render()
{
}

