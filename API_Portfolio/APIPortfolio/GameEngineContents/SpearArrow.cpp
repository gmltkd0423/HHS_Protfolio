#include "SpearArrow.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>

SpearArrow::SpearArrow() 
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
	Angle += 90.0f * GameEngineTime::GetDeltaTime();

	SpearRenderer->SetRotationZ(Angle);
}

void SpearArrow::Render()
{
}
