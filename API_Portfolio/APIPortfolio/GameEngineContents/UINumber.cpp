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

	for (size_t i = 0; i < 3; i++)
	{
		Number[i] = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
		Number[i]->SetImage("UI_Number.bmp");
		if (i == 1)
		{
			Number[i]->SetPivot({ GetPosition().x + 28.0f,GetPosition().y });
		}
		else if (i == 2)
		{
			Number[i]->SetPivot({ GetPosition().x + 56.0f,GetPosition().y });
		}
		Number[i]->SetTransColor(RGB(241, 95, 241));
	}

}

void UINumber::Update()
{
	std::string Arr = std::to_string(value_);

	if (Arr.size() == 0)
	{
		return;
	}

	//0100
	for (size_t i = 0; i < Arr.size(); i++)
	{

		int Value = Arr[i] - '0';
		Number[i]->SetIndex(Value);

	}
}

void UINumber::Render()
{
}
