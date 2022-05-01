#include "PlayLevel2.h"
#include "PlayLevel2Actor.h"
#include "Player.h"
#include "Flowey.h"
#include "PlayLevel2Font.h"
#include "ContentsEnums.h"
#include "SoundPlayer.h"
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngine/GameEngine.h>
#include <GameEngineBase/GameEngineTime.h>

PlayLevel2::PlayLevel2() :
	CheckPos_(false),
	TalkEvent_(false),
	Time_(0),
	PlayBgm_(false),
	Count_(0),
	NextLevel(false)
{
}

PlayLevel2::~PlayLevel2() 
{
}

void PlayLevel2::Loading()
{
	//Init();
}

void PlayLevel2::Update()
{

	CheckPlayerPosition();

	if (true == CheckPos_ && false == NextLevel)
	{
		FloweyTalkEvent();
	}

	MoveNextLevel();
	CheckChangeLevelKey();

}

void PlayLevel2::Init()
{
	BackGround = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::BACKGROUND);
	Back = BackGround->CreateRenderer("Level2.bmp", (int)PLAYLEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);

	Flowey_ = CreateActor<Flowey>((int)PLAYLEVELORDER::MONSTER);


	{
		//플라위 대화 이미지
		FloweyTalk = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::UIIMAGE);
		FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)PLAYLEVELORDER::UIIMAGE);
		FloweyTalk->SetPosition({ GameEngineWindow::GetScale().Half().x - 250 , GameEngineWindow::GetScale().y + 180 });
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Flowey_Idle", 0, 0, 0.4f, true);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Flowey_Talk", 0, 1, 0.2f, true);
		FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
		FloweyTalkRenderer->SetTransColor(RGB(241, 95, 241));
		FloweyTalkRenderer->SetScale({ 120,120 });
		FloweyTalk->Off();
	}

	{
		//대화 텍스트박스이미지
		TextBox = CreateActor<PlayLevel2Actor>((int)PLAYLEVELORDER::UI);
		TextBoxRenderer = TextBox->CreateRendererToScale("TextBox.bmp", { 750 ,200 }, (int)PLAYLEVELORDER::UI);
		TextBox->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y + 180 });
		TextBox->Off();


	}

	{
		//폰트액터
		TextFont_ = CreateActor<PlayLevel2Font>((int)PLAYLEVELORDER::UI);
	}
	


}

void PlayLevel2::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (0 == strcmp("FloweyBattleLevel", _PrevLevel->GetNameConstPtr()))
	{
		NextLevel = true;
		Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,  1200 });
		Back->On();
	}
	else
	{
		//레벨 액터 재배치
		Init();
		NextLevel = false;
		if (nullptr == Player::MainPlayer)
		{
			Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
		}

		//flowey 위치
		Flowey_->SetPosition({ GameEngineWindow::GetScale().Half().x , GameEngineWindow::GetScale().y + 320 });


		Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
		Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,  1400 });
	}
}

void PlayLevel2::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	ResetAll();
	Player::MainPlayer->NextLevelOn();
	Player::MainPlayer->Play();
}


void PlayLevel2::CheckPlayerPosition()
{
	if (Player::MainPlayer->GetPosition().y <= 1200 )
	{
		CheckPos_ = true;
	}
}


//레벨이동 키 검사
void PlayLevel2::CheckChangeLevelKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("ChangeTitleLevel"))
	{
		if (true == PlayBgm_)
		{
			SoundPlayer::Bgm_.Stop();
		}

		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel"))
	{
		if (true == PlayBgm_)
		{
			SoundPlayer::Bgm_.Stop();
		}

		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangeFloweyBattleLevel"))
	{
		if (true == PlayBgm_)
		{
			SoundPlayer::Bgm_.Stop();
		}

		GameEngine::GetInst().ChangeLevel("FloweyBattleLevel");
	}
}


void PlayLevel2::FloweyTalkEvent()
{
	Player::MainPlayer->Stop();
	FloweyTalk->On();
	TextBox->On();

	//레벨전환 키입력
	{
		//z키 입력시
		if (true == Player::MainPlayer->IsActionKeyDown() && true == TextFont_->GetTalkEnd())
		{
			TalkEvent_ = true;
			Back->Off();
			FloweyTalk->Off();
			TextBox->Off();
			Player::MainPlayer->CamPosOn();
			Player::MainPlayer->SetIsChange();
			TextFont_->SetCount(0);
			TextFont_->SetIsTalkEndFalse();
		}

	}

	//잠시 딜레이를 준뒤에 레벨이동
	{
		if (TalkEvent_ == true)
		{
			Time_ += GameEngineTime::GetDeltaTime();
		}

		if (1.0f <= Time_)
		{
			GameEngine::GetInst().ChangeLevel("FloweyBattleLevel");
		}
	}

	//텍스트출력 키입력
	{
		if (true == TextFont_->GetIsAllTextOut())
		{
			FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
		}

		if (true == Player::MainPlayer->IsActionKeyDown() && true == TextFont_->GetIsAllTextOut())
		{
			Count_++;  // 2
			TextFont_->IsAllTextOutFalse();
			TextFont_->SetTextCount(0);
		}


		if (0 == Count_)
		{
			SoundPlayer::Bgm_ = GameEngineSound::SoundPlayControl("03_Your_Best_Friend.flac");
			PlayBgm_ = true;
			Count_++;  //1
		}
		else if (0 < Count_)
		{
			//PlayLevel2Font에 Count값을 전달하여 Texts()에서 다음 텍스트 출력
			TextFont_->SetCount(Count_);
			FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
		}

	}
	
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


void PlayLevel2::ResetAll()
{
	CheckPos_ = false;
	TalkEvent_ = false;
	PlayBgm_ = false;
	Time_ = 0;
	Count_ = 0;
	TextFont_->Death();
	FloweyTalk->Death();
	TextBox->Death();
	Flowey_->Death();
}
