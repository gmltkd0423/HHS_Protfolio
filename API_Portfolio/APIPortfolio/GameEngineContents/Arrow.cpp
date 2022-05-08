#include "Arrow.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>

Arrow::Arrow() :
	Angle(0),
	Angle2(180.0f),
	UpDownAngle(90.0f),
	IsUp(false),
	IsSpin(false)
{
}

Arrow::~Arrow() 
{
}

void Arrow::Start()
{
	ArrowType = Ran.RandomInt(0, 3);
	IsYellow = Yellow.RandomInt(0, 7);

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
	ArrowCol = CreateCollision("Arrow", { 10,40 });
	PlayerPos = Player::MainPlayer->GetPosition();
}

void Arrow::Update()
{
	CheckCol();

	//왼
	if (ArrowType == 0)
	{
		ArrowCol->SetScale({ 40,10 });
		if (Angle >= 180)
		{
			IsUp = false;
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
			if (200 >= len && false == IsSpin)
			{
				IsUp = true;
				IsSpin = true;
			}

			if (true == IsUp)
			{
				if (Angle <= 180.0f)
				{
					Angle += 3.0f;
				}

				float4 Dir = float4::DegreeToDirectionFloat4(Angle);
				Dir *= -200;
				SetPosition(PlayerPos + Dir);
	
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
		if (UpDownAngle >= 270)
		{
			IsUp = false;
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
			if (150 >= len && false == IsSpin)
			{
				IsUp = true;
				IsSpin = true;
			}

			if (true == IsUp)
			{
				if (UpDownAngle <= 270.0f)
				{
					UpDownAngle += 3.0f;
				}

				float4 Dir = float4::DegreeToDirectionFloat4(UpDownAngle);
				Dir *= 150;
				SetPosition(PlayerPos + Dir);

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
		ArrowCol->SetScale({ 40,10 });
		if (Angle >= 180)
		{
			IsUp = false;
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
			if (200 >= len && false == IsSpin)
			{
				IsUp = true;
				IsSpin = true;
			}

			if (true == IsUp)
			{
				if (Angle <= 180.0f)
				{
					Angle += 3.0f;
				}

				float4 Dir = float4::DegreeToDirectionFloat4(Angle);
				Dir *= 200;
				SetPosition(PlayerPos + Dir);

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
	else if(ArrowType == 3)
	{
		if (UpDownAngle >= 270)
		{
			IsUp = false;
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
			if (150 >= len && false == IsSpin)
			{
				IsUp = true;
				IsSpin = true;
			}

			if (true == IsUp)
			{
				if (UpDownAngle <= 270.0f)
				{
					UpDownAngle += 3.0f;
				}

				float4 Dir = float4::DegreeToDirectionFloat4(UpDownAngle);
				Dir *= -150;
				SetPosition(PlayerPos + Dir);

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

void Arrow::CheckCol()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == ArrowCol->CollisionResult("Player", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		Off();
	}

	if (true == ArrowCol->CollisionResult("Shield", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		Sound_.SoundPlayOneShot("snd_bell.wav");
		Death();
	}



}
