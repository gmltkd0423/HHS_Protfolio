#include "HpText.h"
#include <GameEngine/GameEngineRenderer.h>
#include"ContentsEnums.h"

HpText::HpText() 
{
}

HpText::~HpText() 
{
}

void HpText::Start()
{
	HpRenderer = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	HpRenderer->SetImage("Hp.bmp");
	HpRenderer->SetTransColor(RGB(0, 0, 0));
}

void HpText::Update()
{
}

void HpText::Render()
{
}
