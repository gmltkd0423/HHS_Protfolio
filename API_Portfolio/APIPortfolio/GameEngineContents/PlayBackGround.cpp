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
	Render_ = CreateRenderer();
}

void PlayBackGround::Render()
{

}