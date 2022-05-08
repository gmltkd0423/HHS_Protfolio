#include "SpearCircle.h"
#include "ContentsEnums.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>

int SpearCircle::SpearCount = 0;
SpearCircle::SpearCircle()	:
	LookPlayer(false),
	Timer_(1.2f),
	IsSpin(false),
	Speed_(0),
	Value(255),
	Alpha(false)
{
}

SpearCircle::~SpearCircle() 
{
}

void SpearCircle::Start()
{
	SpearRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	SpearRenderer->SetImage("Spear.bmp");
	SpearRenderer->SetRotationFilter("Spear5.bmp");
	SpearCol = CreateCollision("Arrow", { 35,35 });
	Angle = 0.0f;
	SpearRenderer->SetTransColor(RGB(0, 0, 0));
	if (SpearCount == 0)
	{
		MoveAngle = 0;
		SpearCount++;
	}
	else if (SpearCount == 1)
	{
		MoveAngle = 60;
		SpearCount++;
	}
	else if (SpearCount == 2)
	{
		MoveAngle = 120;
		SpearCount++;
	}
	else if (SpearCount == 3)
	{
		MoveAngle = 180;
		SpearCount++;
	}
	else if (SpearCount == 4)
	{
		MoveAngle = 240;
		SpearCount++;
	}
	else if (SpearCount == 5)
	{
		MoveAngle = 300;
		SpearCount++;
	}
	else if (SpearCount == 6)
	{
		MoveAngle = 360;
		SpearCount++;
	}
	float Degree = float4::VectorXYtoDegree(GetPosition(), Player::MainPlayer->GetPosition());
	SpearRenderer->SetRotationZ(Degree + 180.0f);
	PlayerPos = Player::MainPlayer->GetPosition();
	Speed_ = 250.0f;
}


void SpearCircle::Update()
{

	//플레이어 바라보게하기
	float Degree = float4::VectorXYtoDegree(GetPosition(), PlayerPos);
	SpearRenderer->SetRotationZ(Degree + 180.0f);


	MoveAngle += SpinAngle * GameEngineTime::GetDeltaTime() * 0.2f;


	//원으로회전
	if (Alpha == false)
	{
		float4 Dir = float4::DegreeToDirectionFloat4(MoveAngle);
		Dir *= Speed_;
		Speed_ -= 1.0f;
		SetPosition(PlayerPos + Dir);
	}

	if (Speed_<=0.0f)
	{
		Alpha = true;
	}

	if (Alpha==true)
	{
		Death();
	}
}


void SpearCircle::Render()
{
}
