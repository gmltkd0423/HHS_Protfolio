#include "FloweyBullet.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineRenderer.h>

FloweyBullet::FloweyBullet() :
	Pos_(float4::ZERO),
	MoveDir_(float4::ZERO),
	Speed_(0.2f),
	IsCheckPos_(false),
	KeyCount_(0),
	SpeedCount_(0)
{
}

FloweyBullet::~FloweyBullet() 
{
}

void FloweyBullet::Start()
{
	AniRender_ = CreateRenderer();

	AniRender_->CreateAnimation("Flowey_Bullet.bmp","Bullet", 0, 1, 0.1f, true);
	AniRender_->ChangeAnimation("Bullet");
	AniRender_->SetTransColor(RGB(241, 95, 241));
	AniRender_->Off();
	

}

void FloweyBullet::Update()
{
	if (true == Player::MainPlayer->IsActionKeyDown() && 0 == KeyCount_)
	{
		AniRender_->On();
		KeyCount_++;
	}
	else if (true == Player::MainPlayer->IsActionKeyDown() && 1 == KeyCount_)   //z 키를 누르면
	{
		if (0 == SpeedCount_)
		{
			Pos_ = Player::MainPlayer->GetPosition() - GetPosition();
			MoveDir_ = Pos_ * GameEngineTime::GetDeltaTime() * Speed_;
			IsCheckPos_ = true;
			KeyCount_ = 1;
			SpeedCount_= 1;
		}
	}


	if (true == IsCheckPos_)
	{

		SetMove(MoveDir_);
	}
}

void FloweyBullet::Render()
{

}

void FloweyBullet::CheckDeath()
{

}
