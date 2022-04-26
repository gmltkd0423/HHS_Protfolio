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
	IsCheckPos_(false)
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
	if (Player::MainPlayer->IsActionKeyDown())
	{
		Pos_ = Player::MainPlayer->GetPosition() - GetPosition();
		MoveDir_ = Pos_ * GameEngineTime::GetDeltaTime() * Speed_;
		IsCheckPos_ = true;
	}


	if (true == IsCheckPos_)
	{
		SetMove(MoveDir_);
	}
}

void FloweyBullet::Render()
{

}
