#include "Undertale.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>

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
		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Images");
		Dir.Move("Player");

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		GameEngineImage* MoveDown = GameEngineImageManager::GetInst()->Find("Move_Down.bmp");
		MoveDown->Cut({ 25,30 });
		GameEngineImage* MoveUp = GameEngineImageManager::GetInst()->Find("Move_Up.bmp");
		MoveUp->Cut({ 25,30 });
		GameEngineImage* MoveLeft = GameEngineImageManager::GetInst()->Find("Move_Left.bmp");
		MoveLeft->Cut({ 20,30 });
		GameEngineImage* MoveRight = GameEngineImageManager::GetInst()->Find("Move_Right.bmp");
		MoveRight->Cut({ 20,30 });
	}

	{
		//사운드
		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Sounds");

		std::vector<GameEngineFile> SoundList = Dir.GetAllFile();

		for (size_t i = 0; i < SoundList.size(); ++i)
		{
			GameEngineSound::LoadRes(SoundList[i].GetFullPath());
		}

	}

	{
		GameEngineInput::GetInst()->CreateKey("ChangeLevel", VK_RETURN);


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