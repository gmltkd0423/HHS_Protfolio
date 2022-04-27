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
	

}

void FloweyBullet::Update()
{
	if (true == Player::MainPlayer->IsActionKeyDown())   //z 키를 누르면
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

	CheckDeath();
}

void FloweyBullet::Render()
{

}

void FloweyBullet::CheckDeath()
{
	/*if (false == IsCheckPos_)
	{
		return;
	}*/

	if (700.0f <= GetPosition().y ||
		100.0f >= GetPosition().y ||
		50.0f >= GetPosition().x ||
		1200.0f <= GetPosition().x
		)
	{
		Death();
	}
}
