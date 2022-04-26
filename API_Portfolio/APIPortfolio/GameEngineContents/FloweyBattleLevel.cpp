#include "FloweyBattleLevel.h"
#include "BattleLevelActor.h"
#include "ContentsEnums.h"
#include "Player.h"
#include "FloweyBullet.h"
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
	Count_(0)
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
		FloweyTalkRenderer->CreateAnimation("Flowey_Talk_Idle.bmp", "Talk_Idle", 0, 1, 0.4f, true);
		FloweyTalkRenderer->ChangeAnimation("Talk_Idle");
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
	if (Player::MainPlayer->GetPosition().y < 460.0f && false == Check_)
	{
		Player::MainPlayer->SetMove(float4::DOWN * GameEngineTime::GetDeltaTime() * 70);
		if (Player::MainPlayer->GetPosition().y >= 460.0f)
		{
			Check_ = true;
			FloweyTalk->On();
			Speech_BubbleRenderer->On();
		}
	}

	//총알생성
	if (true == Player::MainPlayer->IsActionKeyDown() && 0 == Count_)
	{
		CreateBullet();

		for (int i = 0; i < 5; ++i)
		{
			Bullet_[i]->On();
		}

		++Count_;
	}
	else if (true == Player::MainPlayer->IsActionKeyDown() && 1 == Count_)
	{
		Count_ = 0;

		//총알 캐릭터를 중심으로 원으로 생성
		CreateBulletCircle();
	}

	CheckDeath();

	CheckChageLevelKey();


}

void FloweyBattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
		Player::MainPlayer->IsHeart();
	}

	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,420 });
	Player::MainPlayer->SetSpeed(200.0f);
	Player::MainPlayer->CamPosOff();
	//Player::MainPlayer->



}

void FloweyBattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
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
		Bullet_[i]->Off();
	}
}


void FloweyBattleLevel::CreateBulletCircle()
{


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
	}
}

void FloweyBattleLevel::CheckChageLevelKey()
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
