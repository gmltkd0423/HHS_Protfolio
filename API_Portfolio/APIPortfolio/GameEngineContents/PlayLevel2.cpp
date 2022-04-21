#include "PlayLevel2.h"
#include "PlayLevel2Actor.h"
#include "Player.h"
#include "Flowey.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>

PlayLevel2::PlayLevel2() :
	CheckPos(false)
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
	CheckPlayerPosition();
}

void PlayLevel2::Init()
{
	GameEngineActor* BackGround = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("Level2.bmp", (int)PLAYLEVELORDER::BACKGROUND);

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	FloweyTalk = CreateActor<PlayLevel2Actor>((int)UIORDER::IMAGE);
	FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)UIORDER::IMAGE);
	FloweyTalk->SetPosition({ GameEngineWindow::GetScale().Half().x- 250 , GameEngineWindow::GetScale().y - 250 });
	FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Talk_Idle", 0, 1, 0.4f, true);
	FloweyTalkRenderer->ChangeAnimation("Talk_Idle");
	FloweyTalkRenderer->SetTransColor(RGB(241, 95, 241));
	FloweyTalkRenderer->SetScale({ 120,120 });
	FloweyTalk->Off();

	//Player_ = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);

	Flowey_ = CreateActor<Flowey>((int)PLAYLEVELORDER::MONSTER);
	Flowey_->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y - 70 });
}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().y + 250 });
}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->NextLevelOn();
}


void PlayLevel2::CheckPlayerPosition()
{
	if (Player::MainPlayer->GetPosition().y <= GameEngineWindow::GetInst().GetScale().Half().y + 460 && CheckPos == false)
	{
		CheckPos = true;
		FloweyTalk->On();
	}
}
