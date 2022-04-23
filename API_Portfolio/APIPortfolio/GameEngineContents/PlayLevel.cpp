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
	if (Player::MainPlayer->IsPressAnyMoveKey() == true)
	{
		Player::MainPlayer->CamPosOn();
	}


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
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);
	

}


void PlayLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	Bgm_ = GameEngineSound::SoundPlayControl("05_Ruins.flac");
	BgmTime_ = 30.0f;
	Player::MainPlayer->CollisionImage("Level1_ColMap.bmp");
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,  500 });
	//Player::MainPlayer->GetLevel()->SetCameraPos({ 0,  250 });
	//Player::MainPlayer->CamPosOff();

}

void PlayLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->GetAniRender()->ChangeAnimation("MoveDownIdle");
	Player::MainPlayer->NextLevelOn();
	Bgm_.Stop();
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