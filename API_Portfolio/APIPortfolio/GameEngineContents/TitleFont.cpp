#include "TitleFont.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngineBase/GameEngineTime.h>




TitleFont::TitleFont() :
	Time_(0.3f),
	Timer_(0.0f),
	Count_(0),
	TextCount_(0)

{
}

TitleFont::~TitleFont() 
{
}

void TitleFont::Start()
{
	Count_ = 0;

	//GameEngineDirectory Dir;
	//Dir.MoveParent("API_Portfolio");
	//Dir.Move("APIPortfolio");
	//Dir.Move("Resources");
	//Dir.Move("Fonts");

	//std::vector<GameEngineFile> AllFontFileList = Dir.GetAllFile("ttf");

	//TextFont_.Load(AllFontFileList[1].GetFullPath());

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

	Text_ = L"차례대로 출력\n되게 해보겠습니다.";


	Time_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Time_)
	{
		TextCount_++;
		Time_ = 0.1f;
	}

	RealText_ = Text_.substr(0, TextCount_);

	TextFont_.Draw(RealText_, { 300.0f, 300.0f }, RGB(255, 0, 0), 200, 200);

	//static float Time = 0.1f;
	//static std::wstring Text = L"차례대로 출력\n되게 해보겠습니다.";
	//static int Count = 0;

	//Time -= GameEngineTime::GetDeltaTime();
	//if (0 >= Time)
	//{
	//	Count++;
	//	Time = 0.5f;
	//}

	//std::wstring RealText = Text.substr(0, Count);

	//TextFont_.Draw(RealText, { 100.0f, 100.0f }, RGB(255, 0, 0), 100, 50);

}


void TitleFont::TitleText()
{


}
