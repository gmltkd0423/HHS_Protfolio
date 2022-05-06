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

	Number3 = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
	Number3->SetImage("UI_Number.bmp");
	Number3->SetTransColor(RGB(241, 95, 241));
	Number3->SetPivot({ GetPosition().x + 56.0f,GetPosition().y });
	Number3->Off();

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
		Number[i]->Off();
	}
	for (size_t i = 0; i < 3; i++)
	{
		Number2[i] = CreateRenderer((int)BATTLELEVELORDER::ACTOR);
		Number2[i]->SetImage("UI_Number.bmp");
		if (i == 1)
		{
			Number2[i]->SetPivot({ GetPosition().x + 28.0f,GetPosition().y });
		}
		else if (i == 2)
		{
			Number2[i]->SetPivot({ GetPosition().x + 56.0f,GetPosition().y });
		}
		Number2[i]->SetTransColor(RGB(241, 95, 241));
		Number2[i]->Off();
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
		if (Arr.size() == 1)
		{
			int Value = Arr[i] - '0';
			Number3->SetIndex(Value);
			Number3->On();
		}
		else if (Arr.size() == 2)
		{
			int Value = Arr[i] - '0';
			Number2[i]->SetIndex(Value);
			Number2[i]->On();
		}
		else if (Arr.size() == 3)
		{
			int Value = Arr[i] - '0';
			Number[i]->SetIndex(Value);
			Number[i]->On();
		}
	}
}

void UINumber::Render()
{
}
