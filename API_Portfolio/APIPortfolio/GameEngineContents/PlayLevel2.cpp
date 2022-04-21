#include "PlayLevel2.h"
#include "PlayLevel2Actor.h"
#include "Player.h"
#include "Flowey.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>

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

	{
		//플라위 대화 이미지
		FloweyTalk = CreateActor<PlayLevel2Actor>((int)UIORDER::IMAGE);
		FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)UIORDER::IMAGE);
		FloweyTalk->SetPosition({ GameEngineWindow::GetScale().Half().x - 250 , GameEngineWindow::GetScale().y - 250 });
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Talk_Idle", 0, 1, 0.4f, true);
		FloweyTalkRenderer->ChangeAnimation("Talk_Idle");
		FloweyTalkRenderer->SetTransColor(RGB(241, 95, 241));
		FloweyTalkRenderer->SetScale({ 120,120 });
		FloweyTalk->Off();
	}

	{
		//대화 텍스트박스이미지
		TextBox = CreateActor<PlayLevel2Actor>((int)UIORDER::MESSAGEBOX);
		TextBoxRenderer = TextBox->CreateRendererToScale("TextBox.bmp", { 750 ,200 }, (int)UIORDER::MESSAGEBOX);
		TextBox->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y - 250 });
		TextBox->Off();

		
		FirstLineActor_ = CreateActor<PlayLevel2Actor>((int)UIORDER::TEXT);
		
		FirstLineText_ = FirstLineActor_->CreateRenderer((int)UIORDER::TEXT);
		FirstLineActor_->SetPosition({ GameEngineWindow::GetScale().Half().x - 100, GameEngineWindow::GetScale().y - 300 });
		FirstLineText_->CreateAnimation("FirstLineText1.bmp","Flowey_Text1" ,0, 3, 0.3f, false);
		FirstLineText_->ChangeAnimation("Flowey_Text1");
		FirstLineText_->SetTransColor(RGB(255, 0, 0));
		//폴더이미지
		//FirstLineActor_->SetPosition({ GameEngineWindow::GetScale().Half().x + 100, GameEngineWindow::GetScale().y - 250 });
		//FirstLineText_->CreateFolderAnimation("FloweyText", "Flowey_Text", 0, 3 ,0.3f, false);
		//FirstLineText_->ChangeAnimation("Flowey_Text");
		//FirstLineText_->SetTransColor(RGB(1, 1, 1));
		FirstLineText_->SetScale({ 130,130 });
		FirstLineText_->PauseOn();
		FirstLineText_->Off();

	}

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
		Player::MainPlayer->Stop();
		CheckPos = true;
		FloweyTalk->On();
		TextBox->On();
		FirstLineText_->On();
		FirstLineText_->PauseOff();
		Bgm_ = GameEngineSound::SoundPlayControl("03_Your_Best_Friend.flac");
	}
}
