#include "SpearCircle.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>


SpearCircle::SpearCircle()	:
	LookPlayer(false),
	Timer_(0.0f)
{
}

SpearCircle::~SpearCircle() 
{
}

void SpearCircle::Start()
{
	SpearRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	SpearRenderer->SetImage("Spear2.bmp");
	SpearRenderer->SetIndex(0);
	SpearRenderer->SetRotationFilter("Spear4.bmp");
	Angle = 0.0f;
	SpearRenderer->SetTransColor(RGB(0, 0, 0));
	MoveAngle = 0;
	float Degree = float4::VectorXYtoDegree(GetPosition(), Player::MainPlayer->GetPosition());
	SpearRenderer->SetRotationZ(Degree + 180.0f);
	PlayerPos = Player::MainPlayer->GetPosition();
	Dir = PlayerPos - GetPosition();
	Timer_ = 1.2f;
}

void SpearCircle::Update()
{
	float Degree = float4::VectorXYtoDegree(GetPosition(), PlayerPos);
	SpearRenderer->SetRotationZ(Degree + 180.0f);

	if (false == LookPlayer) 
	{
		Dir = PlayerPos - GetPosition();
		LookPlayer = true;
	}

	SetMove(Dir * GameEngineTime::GetDeltaTime() * 0.8f);


	Timer_ -= GameEngineTime::GetDeltaTime();
	if (0.0f >= Timer_)
	{
		Dir = float4::ZERO;
	}

}

void SpearCircle::Render()
{
}
