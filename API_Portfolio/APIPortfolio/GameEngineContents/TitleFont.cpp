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

	//��Ʈ���� �׽�Ʈ�� �ؽ�Ʈ
	/*TestFont.Load("enbrodwy.ttf");
	TestFont2.Load("arial.ttf");*/
}

void TitleFont::Update()
{
	Time_ += GameEngineTime::GetDeltaTime();
}

void TitleFont::Render()
{

	TitleText();


}


void TitleFont::TitleText()
{


}
