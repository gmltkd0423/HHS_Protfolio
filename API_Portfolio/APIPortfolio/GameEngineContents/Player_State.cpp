#include"Player.h"
#include<GameEngine/GameEngineRenderer.h>
#include<GameEngine/GameEngineImageManager.h>
#include<GameEngineBase/GameEngineWindow.h>
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>


void Player::IdleStart()
{
	AnimationName_ = "Idle";
	AniRender_->ChangeAnimation(DirName_ + AnimationName_);
}

void Player::IdleUpdate()
{
	if (true == IsKeyPress())
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
	if (true == IsKeyUp() && false == IsKeyPress())
	{
		ChangeState(PlayerState::Idle);
		return;
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveRight"))
	{
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveRight");
		DirName_ = "MoveRight";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveLeft");
		DirName_=  "MoveLeft";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveUp");
		DirName_ = "MoveUp";
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveDown");
		DirName_ = "MoveDown";
	}

	CheckWall(MoveDir_);

	return;
}

