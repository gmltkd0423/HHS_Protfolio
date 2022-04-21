#include "PlayLevel2.h"
#include "PlayLevel2BackGround.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineWindow.h>

PlayLevel2::PlayLevel2() 
{
}

PlayLevel2::~PlayLevel2() 
{
}

void PlayLevel2::Loading()
{
	Init();
}

void PlayLevel2::Update()
{

}

void PlayLevel2::Init()
{
	GameEngineActor* BackGround = CreateActor<PlayLevel2BackGround>((int)PLAYLEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("Level2.bmp", (int)PLAYLEVELORDER::BACKGROUND);

	Player_ = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	Player_->SetPosition({ 640, 900 });
}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

