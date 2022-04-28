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
	Count_(0)
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
	


}

void FloweyBullet::Update()
{
	if (13 == Count_ && false == IsCheckPos_)
	{
		SetOrder(5);
		AniRender_->SetOrder(5);
		//한번만 추적
		Speed_ = 0.0005f;
		Pos_ = Player::MainPlayer->GetPosition() - GetPosition();

		IsCheckPos_ = true;
	}

	//플레이어 위치 추적
	//Pos_ = Player::MainPlayer->GetPosition() - GetPosition();
	//MoveDir_ = Pos_ * GameEngineTime::GetDeltaTime() * Speed_;

	if (true == IsCheckPos_)
	{
		MoveDir_ += Pos_ * GameEngineTime::GetDeltaTime() * Speed_;
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

	if (720.0f <= GetPosition().y ||
		0.0f >= GetPosition().y ||
		00.0f >= GetPosition().x ||
		1280.0f <= GetPosition().x
		)
	{
		Death();
	}
}
