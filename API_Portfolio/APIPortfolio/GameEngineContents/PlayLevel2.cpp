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
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>

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
	CheckChangeLevelKey();

	CheckPlayerPosition();

	MoveNextLevel();
}

void PlayLevel2::Init()
{
	GameEngineActor* BackGround = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("Level2.bmp", (int)PLAYLEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);

	Flowey_ = CreateActor<Flowey>((int)PLAYLEVELORDER::MONSTER);


	{
		//플라위 대화 이미지
		FloweyTalk = CreateActor<PlayLevel2Actor>((int)UIORDER::IMAGE);
		FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)UIORDER::IMAGE);
		FloweyTalk->SetPosition({ GameEngineWindow::GetScale().Half().x - 250 , GameEngineWindow::GetScale().y + 180 });
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
		TextBox->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y + 180 });
		TextBox->Off();


	}

	


}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	//flowey 위치
	Flowey_->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y + 320 });

	//카메라 수정
	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,  1400});
	//Player::MainPlayer->CamPosOff();

}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->NextLevelOn();
}


void PlayLevel2::CheckPlayerPosition()
{

	if (Player::MainPlayer->GetPosition().y <= 1200 )
	{
		FloweyTalkEvent();

		if (true == Player::MainPlayer->IsActionKeyDown())
		{
			TalkEvent_ = true;
			Player::MainPlayer->CamPosOn();
			
			GameEngine::GetInst().ChangeLevel("FloweyBattleLevel");
		}
	}

	

	if (TalkEvent_ == true)
	{
		Player::MainPlayer->Play();
	}
}

void PlayLevel2::CheckChangeLevelKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("ChangeTitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}

}

void PlayLevel2::FloweyTalkEvent()
{
	Player::MainPlayer->Stop();
	FloweyTalk->On();

	TextBox->On();

	Bgm_ = GameEngineSound::SoundPlayControl("03_Your_Best_Friend.flac");
}

void PlayLevel2::MoveNextLevel()
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find("Level2_ColMap.bmp");

	float4 NextPos = Player::MainPlayer->GetPosition() + Player::MainPlayer->GetMoveDir();
	int Color = MapColImage_->GetImagePixel(NextPos);

	if (RGB(255, 0, 0) == Color)
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}
}