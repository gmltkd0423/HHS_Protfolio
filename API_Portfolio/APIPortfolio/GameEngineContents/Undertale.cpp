#include "Undertale.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>

Undertale::Undertale()
{
}

Undertale::~Undertale()
{
}

void Undertale::GameInit()
{
	GameEngineWindow::GetInst().SetWindowScaleAndPosition({ 100, 100 }, { 1280, 720 });

	{
		//맵
		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Images");
		Dir.Move("Maps");

		// 폴더안에 모든 이미지 파일을 찾는다.
		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
	}

	{
		//플레이어
	}

	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	CreateLevel<EndingLevel>("EndingLevel");
	ChangeLevel("TitleLevel");
}

void Undertale::GameLoop()
{

}
void Undertale::GameEnd()
{

}