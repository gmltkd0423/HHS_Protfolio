#include "Box.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

Box::Box() :
	Time_(0.2f),
	Timer_(1.0f),
	IsShake(false),
	SetPos(false),
	Speed(50.0f),
	IsChange(false)
{
}

Box::~Box()
{
}

void Box::Start()
{
	TextBox = CreateRendererToScale("TextBox.bmp", { 1000,230 }, (int)BATTLELEVELORDER::BOX);
	ChangeState(BoxState::Text);
}

void Box::Update()
{
	StateUpdate();
	Shake();
}

void Box::Render()
{
}


void Box::Shake()
{
	if (true == IsShake)
	{
		if (false == SetPos)
		{
			float4 RanPos_ = { 3.0f,3.0f };


			Pos_ = GetPosition();
			RightDownPos_ = GetPosition() + RanPos_;
			LeftTopPos_ = GetPosition() - RanPos_;

		}


		SetPos = true;

		if (0.0f <= Timer_)
		{
			Timer_ -= GameEngineTime::GetDeltaTime();
			Time_ += GameEngineTime::GetDeltaTime();

			if (0.0f <= Time_ && false == IsRightDown)
			{
				MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.0f;
				MoveDir2_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 100.0f;
				SetMove(MoveDir_);
				SetMove(MoveDir2_);

				if (GetPosition().x >= RightDownPos_.x && GetPosition().y >= RightDownPos_.y)
				{
					IsRightDown = true;
					RightDownPos_.x -= 1.0f;
					RightDownPos_.y -= 1.0f;
					//MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;

					IsLeftTop = false;
				}
			}
			else if (0.1f <= Time_ && false == IsLeftTop)
			{
				MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 100.0f;
				MoveDir2_ = float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
				SetMove(MoveDir_);
				SetMove(MoveDir2_);
				if (GetPosition().x <= LeftTopPos_.x && GetPosition().y <= LeftTopPos_.y)
				{
					IsLeftTop = true;
					IsRightDown = false;
					LeftTopPos_.x += 1.0f;
					LeftTopPos_.y += 1.0f;
					Time_ = 0.0f;
				}


			}

			if (0.0f >= Timer_)
			{
				Timer_ = 1.0f;
				SetPosition(Pos_);
				IsShake = false;
				SetPos = false;
			}
		}
	}
}

void Box::TextStateStart()
{

}

void Box::TextStateUpdate()
{

}

void Box::BattleStateStart()
{
	MyScale = TextBox->GetScale();
	SizeX = 0;
	SizeY = 0;
}

void Box::BattleStateUpdate()
{
	if (GetPosition().y >= 350.0f && IsChange==true)
	{
		float4 MoveDir_;
		MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 500.0f;
		SetMove(MoveDir_);
	}

	if (TextBox->GetScale().x <= 150.0f && TextBox->GetScale().y <= 150.0f)
	{
		IsChange = true;
		return;
	}
	if (TextBox->GetScale().x >= 150.0f)
	{
		SizeX = GameEngineTime::GetDeltaTime() * 1200;
		TextBox->SetScale({ TextBox->GetScale().x - SizeX, TextBox->GetScale().y });
	}
	else
	{

		SizeY = GameEngineTime::GetDeltaTime() * 600;
		TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y - SizeY });

	}

}


void Box::ChangeState(BoxState _State)
{
	if (_State != CurState_)
	{
		switch (_State)
		{
		case BoxState::Text:
			TextStateStart();
			break;
		case BoxState::Battle:
			BattleStateStart();
			break;

		default:
			break;
		}

		CurState_ = _State;
	}
}

void Box::StateUpdate()
{
	switch (CurState_)
	{
	case BoxState::Text:
		TextStateUpdate();
		break;
	case BoxState::Battle:
		BattleStateUpdate();
		break;
	default:
		break;
	}
}
