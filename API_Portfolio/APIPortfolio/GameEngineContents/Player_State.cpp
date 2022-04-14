#include"Player.h"
#include<GameEngine/GameEngineRenderer.h>
#include<GameEngine/GameEngineImageManager.h>
#include<GameEngineBase/GameEngineWindow.h>;
#include<GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>


void Player::IdleStart()
{
	if (true == GameEngineInput::GetInst()->IsFree("MoveRight"))
	{
		AniRender_->ChangeAnimation("MoveRightIdle");
	}

	if (true == GameEngineInput::GetInst()->IsFree("MoveLeft"))
	{
		AniRender_->ChangeAnimation("MoveLeftIdle");
	}

	if (true == GameEngineInput::GetInst()->IsFree("MoveUp"))
	{
		AniRender_->ChangeAnimation("MoveUpIdle");
	}

	if (true == GameEngineInput::GetInst()->IsFree("MoveDown"))
	{
		AniRender_->ChangeAnimation("MoveDownIdle");
	}
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
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveLeft"))
	{
		MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveLeft");
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveUp"))
	{
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveUp");
	}

	if (true == GameEngineInput::GetInst()->IsPress("MoveDown"))
	{
		MoveDir_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 500;
		AniRender_->ChangeAnimation("MoveDown");
	}

	CheckWall(MoveDir_);

	return;
}

