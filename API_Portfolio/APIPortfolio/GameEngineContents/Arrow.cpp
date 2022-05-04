#include "Arrow.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>

Arrow::Arrow() :
	Angle(0),
	Angle2(180.0f),
	IsUp(false)
{
}

Arrow::~Arrow() 
{
}

void Arrow::Start()
{
	ArrowType = Ran.RandomInt(0, 3);
	IsYellow = Yellow.RandomInt(0, 9);

	//왼쪽
	Pos_[0] = { -50.0f,360.0f };

	Pos_[1] = { 640.0f,750.0f };

	Pos_[2] = { 1340.0f,360.0f };

	Pos_[3] = { 640.0f,-50.0f };


	ArrowRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	ArrowRenderer->SetImage("Arrow_Blue.bmp");
	if (ArrowType == 0)
	{
		SetPosition(Pos_[0]);
		ArrowRenderer->SetIndex(2);
	}
	else if (ArrowType == 1)
	{
		SetPosition(Pos_[1]);
		ArrowRenderer->SetIndex(1);
	}
	else if (ArrowType == 2)
	{
		SetPosition(Pos_[2]);
		ArrowRenderer->SetIndex(3);
	}
	else 
	{
		SetPosition(Pos_[3]);
		ArrowRenderer->SetIndex(0);
	}

	ArrowRenderer->SetTransColor(RGB(121, 230, 234));
	ArrowRenderer->SetScale({ 40,40 });
}

void Arrow::Update()
{
	//왼
	if (ArrowType == 0)
	{
		if (Angle >= 180)
		{
			MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 800.0f;
			SetMove(MoveDir_);
		}
		else
		{
			MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 800.0f;
			SetMove(MoveDir_);
		}

		//노란색이면
		if (IsYellow == 0)
		{
			ArrowRenderer->SetImage("Arrow_Yellow.bmp");
			ArrowRenderer->SetIndex(3);
			ArrowRenderer->SetScale({ 40,40 });
			ArrowRenderer->SetTransColor(RGB(124, 231, 234));

			float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
			len = NewPos_.Len2D();
			if (300 >= len)
			{
				IsUp = true;
		
			}

			if (true == IsUp)
			{
				Angle += 3.0f;
				if (Angle <= 180.0f)
				{
					if (Angle >= 180.0f)
					{
						SetPosition({ GetPosition().x,360.0f });
						IsUp = false;
					}

					float4 Dir = float4::DegreeToDirectionFloat4Up(Angle);
					Dir *= 30;
					SetMove(Dir * GameEngineTime::GetDeltaTime() * 100.0f);
				}
			}
		}
		else
		{
			float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
			len = NewPos_.Len2D();
			if (90 >= len)
			{
				ArrowRenderer->SetImage("Arrow_Red.bmp");
				ArrowRenderer->SetIndex(2);
			}
		}

	}
	else if (ArrowType == 1)                //////////////////아래에서위로
	{
		if (Angle >= 300)
		{
			MoveDir_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 600.0f;
			SetMove(MoveDir_);
		}
		else
		{
			MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 600.0f;
			SetMove(MoveDir_);
		}

		//노란색이면
		if (IsYellow == 0)
		{
			ArrowRenderer->SetImage("Arrow_Yellow.bmp");
			ArrowRenderer->SetIndex(0);
			ArrowRenderer->SetScale({ 40,40 });
			ArrowRenderer->SetTransColor(RGB(124, 231, 234));

			float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
			len = NewPos_.Len2D();
			if (100 >= len)
			{
				IsUp = true;

			}

			if (true == IsUp)
			{
				Angle += 3.0f;
				if (Angle <= 300.0f)
				{
					if (Angle >= 300.0f)
					{
						SetPosition({ 640.0f,GetPosition().y});
						IsUp = false;
					}

					float4 Dir = float4::DegreeToDirectionFloat4Up(Angle);
					Dir *= 15;
					SetMove(Dir * GameEngineTime::GetDeltaTime() * 100.0f);
				}
			}
		}
		else
		{
			float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
			len = NewPos_.Len2D();
			if (90 >= len)
			{
				ArrowRenderer->SetImage("Arrow_Red.bmp");
				ArrowRenderer->SetIndex(1);
			}
		}
	}
	else if (ArrowType == 2)
	{
	if (Angle >= 270)
	{
		MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 800.0f;
		SetMove(MoveDir_);
	}
	else
	{
		MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 800.0f;
		SetMove(MoveDir_);
	}

	//노란색이면
	if (IsYellow == 0)
	{
		ArrowRenderer->SetImage("Arrow_Yellow.bmp");
		ArrowRenderer->SetIndex(2);
		ArrowRenderer->SetScale({ 40,40 });
		ArrowRenderer->SetTransColor(RGB(124, 231, 234));

		float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
		len = NewPos_.Len2D();
		if (200 >= len)
		{
			IsUp = true;

		}

		if (true == IsUp)
		{
			Angle += 3.0f;
			if (Angle <= 270.0f)
			{
				if (Angle >= 270.0f)
				{
					SetPosition({ GetPosition().x,360.0f });
					IsUp = false;
				}

				float4 Dir = float4::DegreeToDirectionFloat4(Angle);
				Dir *= 20;
				SetMove(Dir * GameEngineTime::GetDeltaTime() * 100.0f);
			}
		}
	}
	else
	{
		float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
		len = NewPos_.Len2D();
		if (90 >= len)
		{
			ArrowRenderer->SetImage("Arrow_Red.bmp");
			ArrowRenderer->SetIndex(3);
		}
	}
	}
	else
	{
		if (Angle2 <= 0)
		{
			MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 600.0f;
			SetMove(MoveDir_);
		}
		else
		{
			MoveDir_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 600.0f;
			SetMove(MoveDir_);
		}

		//노란색이면
		if (IsYellow == 0)
		{
			ArrowRenderer->SetImage("Arrow_Yellow.bmp");
			ArrowRenderer->SetIndex(1);
			ArrowRenderer->SetScale({ 40,40 });
			ArrowRenderer->SetTransColor(RGB(124, 231, 234));

			float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
			len = NewPos_.Len2D();
			if (100 >= len)
			{
				IsUp = true;

			}

			if (true == IsUp)
			{
				Angle2 -= 3.0f;
				if (Angle2 >= 0)
				{
					if (Angle2 <= 0)
					{
						SetPosition({ 640.0f,GetPosition().y});
						IsUp = false;
					}

					float4 Dir = float4::DegreeToDirectionFloat4(Angle2);
					Dir *= 10;
					SetMove(Dir * GameEngineTime::GetDeltaTime() * 90.0f);
				}
			}
		}
		else
		{
			float4 NewPos_ = Player::MainPlayer->GetPosition() - GetPosition();
			len = NewPos_.Len2D();
			if (90 >= len)
			{
				ArrowRenderer->SetImage("Arrow_Red.bmp");
				ArrowRenderer->SetIndex(0);
			}
		}
	}
}

void Arrow::Render()
{

}
