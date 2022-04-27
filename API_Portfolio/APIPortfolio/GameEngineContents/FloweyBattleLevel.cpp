#include "FloweyBattleLevel.h"
#include "BattleLevelActor.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "FloweyBullet.h"
#include "FloweyBattleLevelFont.h"
#include <GameEngine/GameEngine.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineInput.h>




FloweyBattleLevel::FloweyBattleLevel() :
	Check_(false),
	PlayerPos_(float4::ZERO),
	CheckBullet_(false),
	IsDeathCheck(0),
	Count_(0),
	CurState_(PatternState::Talk)
{
}

FloweyBattleLevel::~FloweyBattleLevel() 
{
}

void FloweyBattleLevel::Loading()
{
	//백그라운드
	{
		GameEngineActor* BackGround = CreateActor<BattleLevelActor>();
		GameEngineRenderer* Back = BackGround->CreateRenderer("BattleLevelBackGround.bmp", (int)BATTLELEVELORDER::BACKGROUND);
		float4 Half = Back->GetImage()->GetScale().Half();
		Back->SetPivot(Half);
	}

	//네모 이미지
	{
		GameEngineActor* Box = CreateActor<BattleLevelActor>();
		GameEngineRenderer* BoxRenderer = Box->CreateRendererToScale("TextBox_Square.bmp", { 250,250 }, (int)BATTLELEVELORDER::BOX, RenderPivot::CENTER, { 640 , 465 });
	}


	{
		//플라위 대화 이미지
		FloweyTalk = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::ACTOR);
		FloweyTalkRenderer = FloweyTalk->CreateRenderer((int)BATTLELEVELORDER::ACTOR , RenderPivot::CENTER,{640 , 230});
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Flowey_Idle", 0, 0, 0.4f, true);
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Flowey_Talk", 0, 1, 0.4f, true);
		FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
		FloweyTalkRenderer->SetTransColor(RGB(241, 95, 241));
		FloweyTalkRenderer->SetScale({ 120,120 });
		FloweyTalk->Off();
	}

	{
		//말풍선
		Speech_Bubble = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::BOX);
		Speech_BubbleRenderer = Speech_Bubble->CreateRenderer((int)BATTLELEVELORDER::BOX, RenderPivot::CENTER, { 890 , 240 });
		Speech_BubbleRenderer->SetImage("Speech_Bubble.bmp");
		Speech_BubbleRenderer->SetScale({ 387, 160 });
		Speech_BubbleRenderer->SetTransColor(RGB(255, 102, 255));
		Speech_BubbleRenderer->Off();
	}

	{
		

		//CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);


	}

}

void FloweyBattleLevel::Update()
{

	//하트위치 이동
	if (Player::MainPlayer->GetPosition().y < 460.0f && false == Check_)
	{
		Player::MainPlayer->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 70);
		if (Player::MainPlayer->GetPosition().y >= 460.0f)
		{
			Check_ = true;
			FloweyTalk->On();
			Speech_BubbleRenderer->On();
			Player::MainPlayer->Play();
			Count_++;
		}
	}

	StateUpdate();


	

	CheckChangeLevelKey();


}

void FloweyBattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
		Player::MainPlayer->IsHeart();
	}

	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,420 });
	Player::MainPlayer->SetSpeed(200.0f);
	Player::MainPlayer->CamPosOff();
	Player::MainPlayer->Stop();
	
	TextFont_ = CreateActor<FloweyBattleLevelFont>((int)BATTLELEVELORDER::ACTOR);


	ChangeState(PatternState::Talk);
	//Player::MainPlayer->



}

void FloweyBattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	Player::MainPlayer->NextLevelOn();
	Count_ = 0;
}

void FloweyBattleLevel::CreateBullet()
{
	BulletPos_[0] = { 480, 160 };
	BulletPos_[1] = { 560, 120 };
	BulletPos_[2] = { 640, 80 };
	BulletPos_[3] = { 720, 120 };
	BulletPos_[4] = { 800, 160 };

	if (0 != Bullet_.size())
	{
		return;
	}

	for (int i = 0; i < 5;++i)
	{
		GameEngineActor* Bullets = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);

		Bullet_.push_back(Bullets);
		Bullet_[i]->SetPosition(BulletPos_[i]);
	}
}



void FloweyBattleLevel::CheckDeath()
{
	if (0 == Bullet_.size())
	{
		return;
	}

	for (int i = 0; i < 5; ++i)
	{
		if (500.0f <= Bullet_.back()->GetPosition().y)
		{
			CheckBullet_ = true;
		}
	}

	if (true == CheckBullet_)
	{
		for (int i = 0; i < 5; ++i)
		{
			Bullet_[i]->Death();
		}

		Bullet_.clear();
		CheckBullet_ = false;

		Pattern1Start();
		Count_++;
	}
}

void FloweyBattleLevel::ChangeState(PatternState _State)
{

	switch (_State)
	{
	case PatternState::Talk:
		TalkStart();
		break;
	case PatternState::Pattern1:
		Pattern1Start();
		break;
	case PatternState::Pattern2:
		Pattern2Start();
		break;
	default:
		break;
	}
	

	CurState_ = _State;
}

void FloweyBattleLevel::StateUpdate()
{
	switch (CurState_)
	{
	case PatternState::Talk:
		TalkUpdate();
		break;
	case PatternState::Pattern1:
		Pattern1Update();
		break;
	case PatternState::Pattern2:
		Pattern2Update();
		break;
	default:
		break;
	}
}


void FloweyBattleLevel::CheckChangeLevelKey()
{
	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangePlayLevel2"))
	{
		GameEngine::GetInst().ChangeLevel("PlayLevel2");
	}

	if (true == GameEngineInput::GetInst()->IsPress("ChangeTitleLevel"))
	{
		GameEngine::GetInst().ChangeLevel("TitleLevel");
	}
}

void FloweyBattleLevel::TalkStart()
{

}

void FloweyBattleLevel::TalkUpdate()
{
	if (1 == Count_)
	{
		TextFont_->SetCount(Count_);
		FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
	}

	if (true == TextFont_->GetIsAllTextOut())
	{
		FloweyTalkRenderer->ChangeAnimation("Flowey_Idle");
	}

	if (true == Player::MainPlayer->IsActionKeyDown() && true == TextFont_->GetIsAllTextOut())
	{
		Count_++;  // 1
		TextFont_->IsAllTextOutFalse();
		TextFont_->SetTextCount(0);

		TextFont_->SetCount(Count_);
		FloweyTalkRenderer->ChangeAnimation("Flowey_Talk");
	}
	
}

void FloweyBattleLevel::Pattern1Start()
{
	if (Count_ == 3)
	{
		return;
	}

	if(true == Player::MainPlayer->IsActionKeyDown())
	{
	
		FloweyBullet* NewBullet1 = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
		NewBullet1->SetPosition({ 480,160 });

		FloweyBullet* NewBullet2 = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
		NewBullet2->SetPosition({ 560,120 });

		FloweyBullet* NewBullet3 = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
		NewBullet3->SetPosition({ 640,80 });

		FloweyBullet* NewBullet4 = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
		NewBullet4->SetPosition({ 720,120 });

		FloweyBullet* NewBullet5 = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
		NewBullet5->SetPosition({ 800,160 });

		Count_++;
		//CreateBullet();
	}
	
}

void FloweyBattleLevel::Pattern1Update()
{
	//CheckDeath();

	if (Count_ <  3)
	{
		ChangeState(PatternState::Pattern1);
	}
	else
	{
		ChangeState(PatternState::Pattern2);
	}


}

static float Angle = 0;
static float Time = 0;
//static float Timer = 1.0f;

void FloweyBattleLevel::Pattern2Start()
{
	Angle = 0.0f;
	Time = 0.05f;

	//float4 Dir = float4::DegreeToDirectionFloat4(Angle);
	//Dir *= 100.0f;
	//loweyBullet* NewBullet = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
	//NewBullet->SetPosition(Player::MainPlayer->GetPosition() + Dir);

}

void FloweyBattleLevel::Pattern2Update()
{
	if (360.0f <= Angle)
	{
		return;
	}

	Time -= GameEngineTime::GetDeltaTime();

	if (0.0f < Time)
	{
		return;
	}


	Angle += 3.0f;

	float4 Dir = float4::DegreeToDirectionFloat4(Angle);
	Dir *= 200.0f;
	FloweyBullet* NewBullet = CreateActor<FloweyBullet>((int)BATTLELEVELORDER::BULLET);
	NewBullet->SetPosition(Player::MainPlayer->GetPosition() + Dir);
	Time = 0.05f;

}