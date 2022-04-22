#include "PlayLevel2.h"
#include "PlayLevel2Actor.h"
#include "Player.h"
#include "Flowey.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>

PlayLevel2::PlayLevel2() :
	CheckPos_(false),
	TalkEvent_(false)
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
	if (true == Player::MainPlayer->IsActionKeyDown())
	{
		TalkEvent_ = true;
	}

	CheckPlayerPosition();

	Player::MainPlayer->GetLevel()->GetCameraPos();
}

void PlayLevel2::Init()
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	GameEngineActor* BackGround = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("Level2.bmp", (int)PLAYLEVELORDER::BACKGROUND);
	//BackGround->SetPosition({ GameEngineWindow::GetInst().GetScale().x,GameEngineWindow::GetScale().y + 200 });

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
		FirstLineText_->CreateAnimation("FirstLineText1.bmp","Flowey_Text1" ,0, 3, 0.4f, false);
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


	// 글자
	{
		for (int i = 0; i < 4; ++i)
		{
			WordActor_[i] = CreateActor<PlayLevel2Actor>((int)UIORDER::TEXT);
			WordRenderer_[i] = WordActor_[i]->CreateRenderer((int)UIORDER::TEXT);
		}


		WordRenderer_[0]->SetImage("Text1.bmp");
		WordRenderer_[0]->SetPivot({ -100,150 });
		WordRenderer_[0]->SetTransColor(RGB(255, 0, 0));
		WordRenderer_[0]->Off();
		WordRenderer_[1]->SetImage("Text2.bmp");
		WordRenderer_[1]->SetPivot({ -50,150 });
		WordRenderer_[1]->SetTransColor(RGB(255, 0, 0));
		WordRenderer_[1]->Off();
		WordRenderer_[2]->SetImage("Text3.bmp");
		WordRenderer_[2]->SetPivot({ 0,150 });
		WordRenderer_[2]->SetTransColor(RGB(255, 0, 0));
		WordRenderer_[2]->Off();
		WordRenderer_[3]->SetImage("Text4.bmp");
		WordRenderer_[3]->SetPivot({ 50,150 });
		WordRenderer_[3]->SetTransColor(RGB(255, 0, 0));
		WordRenderer_[3]->Off();






	}

	//Player_ = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);

	Flowey_ = CreateActor<Flowey>((int)PLAYLEVELORDER::MONSTER);
	Flowey_->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y - 70 });
}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	//카메라 수정
	//Player::MainPlayer->GetPosition().x, Player::MainPlayer->GetPosition().y - 200
	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x, GameEngineWindow::GetScale().y + 250 });
	Player::MainPlayer->GetLevel()->SetCameraPos({ GameEngineWindow::GetScale().Half().x - 640, GameEngineWindow::GetScale().y  });
	Player::MainPlayer->CamPosOff();

}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->NextLevelOn();
}


void PlayLevel2::CheckPlayerPosition()
{

	if (Player::MainPlayer->GetPosition().y <= GameEngineWindow::GetInst().GetScale().Half().y + 460 && CheckPos_ == false)
	{
		FloweyTalkEvent();

	}

	if (TalkEvent_ == true)
	{
		Player::MainPlayer->Play();
	}
}

void PlayLevel2::FloweyTalkEvent()
{
	Player::MainPlayer->Stop();
	CheckPos_ = true;
	FloweyTalk->On();

	WordRenderer_[0]->On();
	WordRenderer_[1]->On();
	WordRenderer_[2]->On();
	WordRenderer_[3]->On();


	TextBox->On();
	FirstLineText_->On();
	FirstLineText_->PauseOff();
	Bgm_ = GameEngineSound::SoundPlayControl("03_Your_Best_Friend.flac");
}