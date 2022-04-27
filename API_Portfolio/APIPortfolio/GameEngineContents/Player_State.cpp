#include"Player.h"
#include<GameEngine/GameEngineRenderer.h>
#include<GameEngine/GameEngineImageManager.h>
#include<GameEngineBase/GameEngineWindow.h>
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineMath.h>


void Player::IdleStart()
{
	AnimationName_ = "Idle";
	Frisk_->ChangeAnimation(DirName_ + AnimationName_);
}

void Player::IdleUpdate()
{
	if (true == IsKeyPress() && true == IsMove_)
	{
		ChangeState(PlayerState::Move);
		return;
	}

}

void Player::MoveStart()
{

}

void Player::MoveUpdate()
{
	if (true == IsKeyUp() && false == IsKeyPress() && true == IsMove_)
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight") && true == IsMove_)
	{
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * Speed_;
		Frisk_->ChangeAnimation("MoveRight");
		DirName_ = "MoveRight";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft") && true == IsMove_)
	{
		MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * Speed_;
		Frisk_->ChangeAnimation("MoveLeft");
		DirName_=  "MoveLeft";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp") && true == IsMove_)
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * Speed_;
		Frisk_->ChangeAnimation("MoveUp");
		DirName_ = "MoveUp";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown") && true == IsMove_)
	{
		MoveDir_ = float4::DOWN * GameEngineTime::GetDeltaTime() * Speed_;
		Frisk_->ChangeAnimation("MoveDown");
		DirName_ = "MoveDown";
	}

	CheckWall(MoveDir_);

	return;
}

void Player::GetDamaged()
{
}

