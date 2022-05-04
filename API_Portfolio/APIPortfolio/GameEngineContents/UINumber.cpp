#include "UINumber.h"
#include <GameEngine/GameEngineRenderer.h>
#include "ContentsEnums.h"

UINumber::UINumber() 
{
}

UINumber::~UINumber() 
{
}

void UINumber::Start()
{

	//10의자리
	Number1 = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	Number1->SetImage("UI_Number.bmp");
	Number1->SetIndex(0);
	Number1->SetTransColor(RGB(241, 95, 241));
	

	//1의자리
	Number2 = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	Number2->SetImage("UI_Number.bmp");
	Number2->SetIndex(1);
	Number2->SetPivot({ GetPosition().x+28.0f,GetPosition().y});
	Number2->SetTransColor(RGB(241, 95, 241));



}

void UINumber::Update()
{
}

void UINumber::Render()
{
}
