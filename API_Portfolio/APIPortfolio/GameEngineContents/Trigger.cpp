#include "Trigger.h"
#include "GameEngineBase/GameEngineTime.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include "GameEngine/GameEngineRenderer.h"

Trigger::Trigger()	:
	FireDeath_(false)
{
}

Trigger::~Trigger()
{
}

void Trigger::Start()
{
	
	Fire_Trigger = CreateCollision("Fire_Trigger", { 50,200 });
}

void Trigger::Update()
{
	std::vector<GameEngineCollision*> ColList;

	if (true == Fire_Trigger->CollisionResult("Fire", ColList, CollisionType::Rect, CollisionType::Rect))
	{
		for (size_t i = 0; i < ColList.size(); i++)
		{
			ColList[i]->GetActor()->Death();
			Fire_Trigger->Off();
			FireDeath_ = true;
		}
	}
	
}

void Trigger::Render()
{
}


