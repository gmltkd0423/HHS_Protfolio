#include "PlayLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "PlayBackGround.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineImageManager.h>


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	Init();
}

void PlayLevel::Update()
{
	if (true == GameEngineInput::GetInst()->IsPress("ChangeTitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
	else if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel2"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}

	BgmTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= BgmTime_)
	{
		Bgm_.Stop();
	}

	MoveNextLevel();
}

void PlayLevel::Init()
{
	GameEngineActor* BackGround = CreateActor<PlayBackGround>((int)PLAYLEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("Level1.bmp", (int)PLAYLEVELORDER::BACKGROUND);
	
	Player_ = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	Player_->SetPosition({ 400,300 });
}


void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Bgm_ = GameEngineSound::SoundPlayControl("05_Ruins.flac");
	BgmTime_ = 30.0f;

}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player_->SetPosition({ 400,300 });
	Bgm_.Stop();
}

void PlayLevel::MoveNextLevel()
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");

	float4 NextPos = Player_->GetPosition() + Player_->GetMoveDir();
	int Color = MapColImage_->GetImagePixel(NextPos);

	if (RGB(255, 22, 0) == Color)
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}
}