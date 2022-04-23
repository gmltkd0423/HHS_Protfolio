#include "TitleFont.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>


TitleFont::TitleFont() 
{
}

TitleFont::~TitleFont() 
{
}

void TitleFont::Start()
{
	GameEngineDirectory Dir;
	Dir.MoveParent("API_Portfolio");
	Dir.Move("APIPortfolio");
	Dir.Move("Resources");
	Dir.Move("Fonts");

	std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("ttf");


	TextFont.Load(AllImageFileList[1].GetFullPath());
}

void TitleFont::Update()
{
}

void TitleFont::Render()
{
	TextFont.Draw("´Ù¶÷Áã Çå ÃÂ¹ÙÄû Å¸°íÆÄ", { 100.0f,100.0f }, 100, 50);

}

