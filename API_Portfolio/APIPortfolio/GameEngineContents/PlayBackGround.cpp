#include "PlayBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

PlayBackGround::PlayBackGround() 
{
}

PlayBackGround::~PlayBackGround() 
{
}

void PlayBackGround::Start()
{
	SetPosition({ GameEngineWindow::GetInst().GetScale().Half().x + 350,GameEngineWindow::GetInst().GetScale().Half().y });
}

void PlayBackGround::Render()
{

}
