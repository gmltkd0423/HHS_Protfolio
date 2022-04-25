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
	}



	//텍스트 , 말풍선
	{
		GameEngineDirectory Dir;
		Dir.MoveParent("API_Portfolio");
		Dir.Move("APIPortfolio");
		Dir.Move("Resources");
		Dir.Move("Images");
		Dir.Move("Text");

		std::vector<GameEngineFile> AllImageFileList = Dir.GetAllFile("Bmp");

		for (size_t i = 0; i < AllImageFileList.size(); i++)
		{
			GameEngineImageManager::GetInst()->Load(AllImageFileList[i].GetFullPath());
		}

		GameEngineImage* FirstLineText1 = GameEngineImageManager::GetInst()->Find("FirstLineText1.bmp");
		FirstLineText1->Cut({ 128,128 });

		GameEngineImage* SecondLineText1 = GameEngineImageManager::GetInst()->Find("SecondLineText1.bmp");
		SecondLineText1->Cut({ 128,128 });

		GameEngineImage* ThirdLineText1 = GameEngineImageManager::GetInst()->Find("ThirdLineText1.bmp");
		ThirdLineText1->Cut({ 128,128 });
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
		GameEngineInput::GetInst()->CreateKey("ChangeBattleLevel", '3');


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