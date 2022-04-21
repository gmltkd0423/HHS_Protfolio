#include "PlayLevel2Actor.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel2Actor::PlayLevel2Actor()
{
}

PlayLevel2Actor::~PlayLevel2Actor()
{
}

void PlayLevel2Actor::Start()
{
	SetPosition(GameEngineWindow::GetInst().GetScale().Half());
}

void PlayLevel2Actor::Render()
{
}

