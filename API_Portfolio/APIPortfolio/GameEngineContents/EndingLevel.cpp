#include "EndingLevel.h"
#include <GameEngine/GameEngineRenderer.h>
#include"ContentsEnums.h"
#include "PlayLevel2Actor.h"
#include "Player.h"
#include <GameEngine/GameEngineImage.h>

EndingLevel::EndingLevel()
{
}

EndingLevel::~EndingLevel()
{
}


void EndingLevel::Loading()
{
	BackGround = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::BACKGROUND);
	Back = BackGround->CreateRenderer("Title.bmp", (int)PLAYLEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);
}

void EndingLevel::Update()
{

}

void EndingLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->Off();
}
