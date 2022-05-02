#include "AttackBar.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngine/GameEngineImageManager.h>


AttackBar::AttackBar()	:
	Time_(0.2f),
	Timer_(1.0f),
	IsShake(false),
	SetPos(false)
{
}

AttackBar::~AttackBar()
{
}

void AttackBar::Start()
{
	AttackBarRenderer = CreateRendererToScale("AttackBar.bmp", { 920,210 }, (int)BATTLELEVELORDER::BOX);
	AttackBarRenderer->SetTransColor(RGB(255, 255, 255));


}

void AttackBar::Update()
{
	Shake();
}

void AttackBar::Render()
{
}

void AttackBar::Shake()
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