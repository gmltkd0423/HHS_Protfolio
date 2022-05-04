#include "Undyne.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngineBase/GameEngineTime.h>
#include "ContentsEnums.h"
#include <math.h>

Undyne::Undyne() :
	IsHurt(false),
	IsIdle(false),
	IsShake(false),
	Time_(0.0f),
	Timer_(1.0f),
	IsRight(false),
	IsLeft(false),
	Hp(1000.0f),
	MaxHp(1000.0f),
	IsDamaged(false)

{
}

Undyne::~Undyne()
{
}

void Undyne::Start()
{
	UndyneRenderer = CreateRenderer((int)BATTLELEVELORDER::BACKGROUND);
	UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle", 0, 67, 0.04f, true);
	UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle_Stop", 0, 0, 0, false);
	UndyneRenderer->CreateAnimation("Undyne_Hurt.bmp", "Hurt", 0, 0, 0, false);
	UndyneRenderer->ChangeAnimation("Idle");
	UndyneRenderer->SetScale({ 550,380 });
}

void Undyne::Update()
{
	Shake();
}

void Undyne::Render()
{
}

void Undyne::Hurt()
{

	IsHurt = true;

}

void Undyne::Idle()
{

	UndyneRenderer->ChangeAnimation("Idle");
	IsIdle = true;

}

void Undyne::GetDamaged(float _Damage)
{
	Hp -= _Damage;



}

void Undyne::Shake()
{
	if (true == IsHurt)
	{

		UndyneRenderer->ChangeAnimation("Hurt");

		if (false == IsShake)
		{
			Pos_ = GetPosition();
			RightPos_.x = GetPosition().x + 30.0f;
			LeftPos_.x = GetPosition().x - 30.0f;
			//MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;
		}

		IsShake = true;
		if (0.0f <= Timer_)
		{
			GameEngineRandom Ran;
			float Randomfloat = Ran.RandomInt(1.0f, 4.0f);
			Timer_ -= GameEngineTime::GetDeltaTime();
			Time_ += GameEngineTime::GetDeltaTime();

			if (0.0f <= Time_ && false == IsRight)
			{
				MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 2000.0f;
				SetMove(MoveDir_);

				if (GetPosition().x >= RightPos_.x)
				{
					IsRight = true;
					RightPos_.x -= 5.0f;
					//MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;

					IsLeft = false;
				}
			}
			else if (0.1f <= Time_ && false == IsLeft)
			{
				MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 2000.0f;
				SetMove(MoveDir_);
				if (GetPosition().x <= LeftPos_.x)
				{
					IsLeft = true;
					IsRight = false;
					LeftPos_.x += 5.0f;
					Time_ = 0.0f;
				}
			}
			//SetPosition( {GetPosition().x + Randomfloat,GetPosition().y});
			
		
	
			//	SetPosition({ GetPosition().x - Randomfloat,GetPosition().y });
\

			if (0.0f >= Timer_)
			{
				Timer_ = 1.0f;
				Time_ = 0.0f;
				SetPosition(Pos_);
				IsShake = false;
				IsHurt = false;
				//UndyneRenderer->ChangeAnimation("Idle");
			}
		}
	}
}
