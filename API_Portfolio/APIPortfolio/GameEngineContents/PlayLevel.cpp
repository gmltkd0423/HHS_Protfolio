#include "PlayLevel.h"
#include "Player.h"
#include "ContentsEnums.h"
#include "PlayBackGround.h"
#include "SoundPlayer.h"
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
	CheckChangeLevelKey();
	BgmTime_ -= GameEngineTime::GetDeltaTime();

	if (0 >= BgmTime_)
	{
		SoundPlayer::Bgm_.Stop();
	}

	MoveNextLevel();
}


void PlayLevel::Init()
{
	CreateActor<PlayBackGround>();

}


void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	SoundPlayer::Bgm_ = GameEngineSound::SoundPlayControl("05_Ruins.flac");
	BgmTime_ = 30.0f;
	Player::MainPlayer->CollisionImage("Level1_ColMap.bmp");
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,  500 });
	Player::MainPlayer->GetFrisk()->ChangeAnimation("MoveDownIdle");

}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	//Reset();
	Player::MainPlayer->NextLevelOn();
	SoundPlayer::Bgm_.Stop();
}

void PlayLevel::MoveNextLevel()
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");

	float4 NextPos = Player::MainPlayer->GetPosition() + Player::MainPlayer->GetMoveDir();
	int Color = MapColImage_->GetImagePixel(NextPos);

	if (RGB(255, 0, 0) == Color)
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}
}

void PlayLevel::CheckChangeLevelKey()
{

	if (true == GameEngineInput::GetInst()->IsPress("ChangeTitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel2"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}
	if (true == GameEngineInput::GetInst()->IsPress("ChangeFloweyBattleLevel"))
	{
		Player::MainPlayer->SetIsChange();
		GameEngine::GetInst().ChangeLevel("FloweyBattleLevel");
	}

}
