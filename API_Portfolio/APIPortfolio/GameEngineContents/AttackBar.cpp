#include "AttackBar.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineRenderer.h>


AttackBar::AttackBar()
{
}

AttackBar::~AttackBar()
{
}

void AttackBar::Start()
{
	AttackBarRenderer = CreateRendererToScale("AttackBar.bmp", { 920,210 }, (int)BATTLELEVELORDER::BOX);
	AttackBarRenderer->SetTransColor(RGB(255, 255, 255));
}

void AttackBar::Update()
{
}

void AttackBar::Render()
{
}
