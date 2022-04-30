#include "Undertale.h"
#include "PlayLevel.h"
#include "EndingLevel.h"
#include "TitleLevel.h"
#include "PlayLevel2.h"
#include "BattleLevel.h"
#include "FloweyBattleLevel.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineBase/GameEngineFile.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineFont.h>

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


	//몬스터 : 플라위
	{


		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Images");
		Dir.Move("Flowey");

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		GameEngineImage* Idle = GameEngineImageManager::GetInst()->Find("Flowey_Idle.bmp");
		Idle->Cut({ 21,21 });

		GameEngineImage* Talk_Idle = GameEngineImageManager::GetInst()->Find("Flowey_Talk_Idle.bmp");
		Talk_Idle->Cut({ 43,44 });

		GameEngineImage* Side = GameEngineImageManager::GetInst()->Find("Flowey_Talk_Side.bmp");
		Side->Cut({ 43,44 });

		GameEngineImage* Wink = GameEngineImageManager::GetInst()->Find("Flowey_Talk_Wink.bmp");
		Wink->Cut({ 43,44 });

		GameEngineImage* Sassy = GameEngineImageManager::GetInst()->Find("Flowey_Talk_Sassy.bmp");
		Sassy->Cut({ 43,44 });

		GameEngineImage* Mad = GameEngineImageManager::GetInst()->Find("Flowey_Talk_Mad.bmp");
		Mad->Cut({ 43,44 });

		GameEngineImage* Evil = GameEngineImageManager::GetInst()->Find("Flowey_Talk_Evil.bmp");
		Evil->Cut({ 43,44 });

		GameEngineImage* Laugh = GameEngineImageManager::GetInst()->Find("Flowey_Laugh.bmp");
		Laugh->Cut({ 43,44 });

		GameEngineImage* WinkStar = GameEngineImageManager::GetInst()->Find("WinkStar.bmp");
		WinkStar->Cut({ 58,55 });

		GameEngineImage* Bullet = GameEngineImageManager::GetInst()->Find("Flowey_Bullet.bmp");
		Bullet->Cut({ 15,14 });


	}


	{


		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Images");
		Dir.Move("Undyne");
		

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}


		GameEngineImage* Idle = GameEngineImageManager::GetInst()->Find("Undyne_Idle.bmp");
		Idle->Cut({ 477,364 });

	}



	GameEngineDirectory Dir;
	Dir.MoveParent("API_Portfolio");
	Dir.Move("APIPortfolio");
	Dir.Move("Resources");
	Dir.Move("Images");
	Dir.Move("Bullets");


	std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

	for (size_t i = 0; i < AllImageFileList.size(); i++)
	{
		GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
	}


	GameEngineImage* Fire = GameEngineImageManager::GetInst()->Find("Fire.bmp");
	Fire->Cut({ 20,30 });


	// UI
	{
		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Images");
		Dir.Move("UI");

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}
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
		GameEngineInput::GetInst()->CreateKey("ChangePlayLevel", VK_RETURN);
		GameEngineInput::GetInst()->CreateKey("ChangeTitleLevel", '1');
		GameEngineInput::GetInst()->CreateKey("ChangePlayLevel2", '2');
		GameEngineInput::GetInst()->CreateKey("ChangeFloweyBattleLevel", '3');
		GameEngineInput::GetInst()->CreateKey("ChangeDebug", '0');


	}


	CreateLevel<TitleLevel>("TitleLevel");
	CreateLevel<PlayLevel>("PlayLevel");
	CreateLevel<PlayLevel2>("PlayLevel2");
	CreateLevel<BattleLevel>("BattleLevel");
	CreateLevel<EndingLevel>("EndingLevel");
	CreateLevel<FloweyBattleLevel>("FloweyBattleLevel");
	ChangeLevel("TitleLevel");

}

void Undertale::GameLoop()
{

}
void Undertale::GameEnd()
{

}