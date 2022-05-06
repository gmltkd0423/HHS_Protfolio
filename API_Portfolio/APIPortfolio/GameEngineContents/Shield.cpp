#include "Shield.h"
#include"Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngineBase/GameEngineSound.h>


Shield::Shield() :
	IsUp(false),
	IsDown(false),
	IsLeft(false),
	IsRight(false),
	Timer_(0.2f)
{
}

Shield::~Shield() 
{
}

void Shield::Start()
{
	ShieldRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	ShieldRenderer->SetImage("Shield_Blue.bmp");
	ShieldRenderer->SetIndex(0);
	ShieldRenderer->SetTransColor(RGB(0, 0, 0));
	ShieldRenderer->SetPivot({ 0, -30.0f });
	ShieldCol = CreateCollision("Shield",{75,25});
}

void Shield::Update()
{
	if (true == GameEngineInput::GetInst()->IsDown("MoveUp"))
	{
		ShieldRenderer->SetImage("Shield_Blue.bmp");
		ShieldRenderer->SetIndex(0);
		ShieldRenderer->SetPivot({0, -20.0f });
		ShieldCol->SetScale({ 20,20 });
		ShieldCol->SetPivot({ 0,-40.0f });
		IsUp = true;
		IsDown = false;
		IsLeft = false;
		IsRight = false;
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveRight"))
	{
		ShieldRenderer->SetImage("Shield_Blue.bmp");
		ShieldRenderer->SetIndex(1);
		ShieldRenderer->SetPivot({20.0f,0 });
		ShieldCol->SetScale({ 20,20 });
		ShieldCol->SetPivot({ 40.0f, 0 });
		IsUp = false;
		IsDown = false;
		IsLeft = false;
		IsRight = true;
	}
	if (true == GameEngineInput::GetInst()->IsDown("MoveDown"))
	{
		ShieldRenderer->SetImage("Shield_Blue.bmp");
		ShieldRenderer->SetIndex(2);
		ShieldRenderer->SetPivot({0, 20.0f });
		ShieldCol->SetScale({ 20,20 });
		ShieldCol->SetPivot({ 0, 40.0f });
		IsUp = false;
		IsDown = true;
		IsLeft = false;
		IsRight = false;
	}

	if (true == GameEngineInput::GetInst()->IsDown("MoveLeft"))
	{
		ShieldRenderer->SetImage("Shield_Blue.bmp");
		ShieldRenderer->SetIndex(3);
		ShieldRenderer->SetPivot({-20.0f, 0});
		ShieldCol->SetScale({ 20,20 });
		ShieldCol->SetPivot({ -40.0f,0 });
		IsUp = false;
		IsDown = false;
		IsLeft = true;
		IsRight = false;
	}

	CheckCollision();


}

void Shield::Render()
{
}

void Shield::CheckCollision()
{

	std::vector<GameEngineCollision*> ColList;
	if (true == ShieldCol->CollisionResult("Arrow", ColList))
	{

		if (IsUp == true)
		{
			ShieldRenderer->SetImage("Shield_Red.bmp");
			ShieldRenderer->SetIndex(0);
		}
		else if (IsRight == true)
		{
			ShieldRenderer->SetImage("Shield_Red.bmp");
			ShieldRenderer->SetIndex(1);
		}
		else if (IsDown == true)
		{
			ShieldRenderer->SetImage("Shield_Red.bmp");
			ShieldRenderer->SetIndex(2);
		}
		else if (IsLeft == true)
		{
			ShieldRenderer->SetImage("Shield_Red.bmp");
			ShieldRenderer->SetIndex(3);
		}
	}
	else
	{
		Timer_ -= GameEngineTime::GetDeltaTime();
		if (0 >= Timer_)
		{
			if (IsUp == true)
			{
				ShieldRenderer->SetImage("Shield_Blue.bmp");
				ShieldRenderer->SetIndex(0);
				Timer_ = 0.2f;
			}
			else if (IsRight == true)
			{
				ShieldRenderer->SetImage("Shield_Blue.bmp");
				ShieldRenderer->SetIndex(1);
				Timer_ = 0.2f;
			}
			else if (IsDown == true)
			{
				ShieldRenderer->SetImage("Shield_Blue.bmp");
				ShieldRenderer->SetIndex(2);
				Timer_ = 0.2f;
			}
			else if (IsLeft == true)
			{
				ShieldRenderer->SetImage("Shield_Blue.bmp");
				ShieldRenderer->SetIndex(3);
				Timer_ = 0.2f;
			}
		}
	}
}
