#include "PlayBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include "ContentsEnums.h"

PlayBackGround::PlayBackGround() 
{
}

PlayBackGround::~PlayBackGround() 
{
}

void PlayBackGround::Start()
{
	GameEngineRenderer* Back = CreateRenderer("Level1.bmp", (int)PLAYLEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);
}

void PlayBackGround::Render()
{

}
