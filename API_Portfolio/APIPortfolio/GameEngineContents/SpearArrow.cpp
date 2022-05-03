#include "SpearArrow.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

SpearArrow::SpearArrow() :
	Timer_(1.0f),
	LookPlayer(false)
{

}

SpearArrow::~SpearArrow() 
{

}

void SpearArrow::Start()
{
	SpearRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	SpearRenderer->SetImage("Spear2.bmp");
	SpearRenderer->SetIndex(0);
	SpearRenderer->SetRotationFilter("Spear4.bmp");
	Angle = 0.0f;
	SpearRenderer->SetTransColor(RGB(0, 0, 0));
}

void SpearArrow::Update()
{
	Angle += 180.0f * GameEngineTime::GetDeltaTime();
	Timer_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Timer_)
	{
		if(false == LookPlayer)
		{
			float Degree = float4::VectorXYtoDegree(GetPosition(), Player::MainPlayer->GetPosition());
			SpearRenderer->SetRotationZ(Degree + 180.0f);
			MoveDir_ = (Player::MainPlayer->GetPosition() - GetPosition()) * GameEngineTime::GetDeltaTime() * 1.3f;
			LookPlayer = true;
		}
	
		SetMove(MoveDir_);
	}
	else
	{
		SpearRenderer->SetRotationZ(Angle);
	}
}

void SpearArrow::Render()
{
}
