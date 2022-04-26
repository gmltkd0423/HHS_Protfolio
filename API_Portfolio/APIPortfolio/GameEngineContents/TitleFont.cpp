#include "TitleFont.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineTime.h>


TitleFont::TitleFont() :
	Time_(0.0f),
	FontSizeX_(80.0f),
	FontSizeY_(80.0f),
	Title1TextOn(true),
	Count_(0),
	TextPos_({235 , 470})
{
}

TitleFont::~TitleFont() 
{
}

void TitleFont::Start()
{
	Count_ = 0;

	GameEngineDirectory Dir;
	Dir.MoveParent("API_Portfolio");
	Dir.Move("APIPortfolio");
	Dir.Move("Resources");
	Dir.Move("Fonts");

	std::vector<GameEngineFile> AllFontFileList = Dir.GetAllFile("ttf");

	TextFont_.Load(AllFontFileList[1].GetFullPath());

	//폰트변경 테스트용 텍스트
	/*TestFont.Load("enbrodwy.ttf");
	TestFont2.Load("arial.ttf");*/
}

void TitleFont::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();
}

void TitleFont::Render()
{
	/*static float Time = 0.1f;
	static std::wstring Text = L"차례대로 출력\n되게 해보겠습니다.";
	static int Count = 0;

	Time -= GameEngineTime::GetDeltaTime();
	if (0 >= Time)
	{
		Count++;
		Time = 0.5f;
	}

	std::wstring RealText = Text.substr(0, Count);

	TextFont.Draw(RealText, { 100.0f, 100.0f }, RGB(255, 0, 0), 100, 50);*/
	TitleText();


}


void TitleFont::TitleText()
{


}
