#include "FloweyBullet.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>

FloweyBullet::FloweyBullet() :
	Pos_(float4::ZERO),
	MoveDir_(float4::ZERO),
	Speed_(0.0005f),
	IsCheckPos_(false),
	KeyCount_(0),
	SpeedCount_(0),
	Count_(0),
	DeathCheck_(false),
	IsCircleBullet(false),
	PhaseStart_(false),
	PhaseEnd_(false)
{
}

FloweyBullet::~FloweyBullet() 
{
}

void FloweyBullet::Start()
{
	AniRender_ = CreateRenderer(1);

	AniRender_->CreateAnimation("Flowey_Bullet.bmp","Bullet", 0, 1, 0.07f, true);
	AniRender_->ChangeAnimation("Bullet");
	AniRender_->SetTransColor(RGB(241, 95, 241));
	
	BulletCol_ = CreateCollision("Bullet", { 15,14 });

} 

void FloweyBullet::Update()
{

	NormalBullet();
	CircleBullet();



	CheckDeath();
}

void FloweyBullet::Render()
{

}

void FloweyBullet::NormalBullet()
{
	//세번쏠때
	if (13 == Count_ && false == IsCheckPos_ ||
		16 == Count_ && false == IsCheckPos_ ||
		19 == Count_ && false == IsCheckPos_)
	{
		SetOrder(5);
		AniRender_->SetOrder(5);
		//한번만 추적
		Speed_ = 0.0005f;
		Pos_ = Player::MainPlayer->GetPosition() - GetPosition();

		Count_++;
		IsCheckPos_ = true;
	}

	if (true == IsCheckPos_)
	{
		MoveDir_ += Pos_ * GameEngineTime::GetDeltaTime() * Speed_;
		SetMove(MoveDir_);
	}

}

void FloweyBullet::CircleBullet()
{
	if (23 == Count_ && false == IsCheckPos_)
	{
			//한번만 추적
		Speed_ = 0.1f;
		Pos_ = Player::MainPlayer->GetPosition() - GetPosition();
		MoveDir_ = Pos_ * GameEngineTime::GetDeltaTime() * Speed_;
		Count_++;
		IsCircleBullet = true;
		PlayerPos_ = Player::MainPlayer->GetPosition();
	}

	if (true == IsCircleBullet && true == PhaseStart_)
	{
		if (true == Player::MainPlayer->IsActionKeyDown())
		{
			Count_++;
		}
	}

	if (25 <= Count_ && true == IsCircleBullet)
	{
		MoveDir_ = Pos_ * GameEngineTime::GetDeltaTime() * Speed_;
		SetMove(MoveDir_);

		float4 NewPos_= PlayerPos_ - GetPosition();
		len = NewPos_.Len2D();
		if (60 >= len)
		{
			Off();
			PhaseEnd_ = true;
		}
	}
}

void FloweyBullet::CheckDeath()
{
	/*if (false == IsCheckPos_)
	{
		return;
	}*/

	if (720.0f <= GetPosition().y ||
		0.0f >= GetPosition().y ||
		00.0f >= GetPosition().x ||
		1280.0f <= GetPosition().x
		)
	{
		DeathCheck_ = true;
		IsCheckPos_ = false;
		MoveDir_ = float4::ZERO;
	}
}
