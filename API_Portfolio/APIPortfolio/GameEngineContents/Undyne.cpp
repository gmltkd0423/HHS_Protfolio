#include "Undyne.h"
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsEnums.h"

Undyne::Undyne()
{
}

Undyne::~Undyne()
{
}

void Undyne::Start()
{
	UndyneRenderer = CreateRenderer((int)BATTLELEVELORDER::BACKGROUND);
	UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle", 0, 67, 0.03f, true);
	UndyneRenderer->CreateAnimation("Undyne_Idle.bmp", "Idle_Stop", 0, 0, 0, false);
	UndyneRenderer->ChangeAnimation("Idle");
	UndyneRenderer->SetScale({ 500,320 });
}

void Undyne::Update()
{

}

void Undyne::Render()
{
}
