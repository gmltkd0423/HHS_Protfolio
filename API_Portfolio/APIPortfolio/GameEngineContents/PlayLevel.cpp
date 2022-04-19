#include "PlayLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "PlayBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	PlayBackGround* Back = CreateActor<PlayBackGround>((int)PLAYLEVELORDER::BACKGROUND);
	Back->GetRenderer()->SetImage("Level2.bmp");

	float4 NewPivot = Back->GetRenderer()->GetImage()->GetScale().Half();
	Back->GetRenderer()->SetPivot(NewPivot);

	Player_ = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	Player_->SetPosition({ 400,300 });
}

void PlayLevel::Update()
{
	BgmTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= BgmTime_)
	{
		Bgm_.Stop();
	}
}


void PlayLevel::LevelChangeStart()
{
	Bgm_ = GameEngineSound::SoundPlayControl("05_Ruins.flac");
	BgmTime_ = 30.0f;

}

void PlayLevel::LevelEnd()
{
	Bgm_.Stop();
}