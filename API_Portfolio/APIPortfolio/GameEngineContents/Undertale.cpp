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

		GameEngineImage* Hurt = GameEngineImageManager::GetInst()->Find("Flowey_Hurt.bmp");
		Hurt->Cut({ 43,44 });

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

		GameEngineImage* Hurt = GameEngineImageManager::GetInst()->Find("Undyne_Hurt.bmp");
		Hurt->Cut({ 477,364 });


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

	GameEngineImage* Spear = GameEngineImageManager::GetInst()->Find("spear2.bmp");
	Spear->Cut({ 129,100 });

	GameEngineImage* ArrowRed = GameEngineImageManager::GetInst()->Find("Arrow_Red.bmp");
	ArrowRed->Cut({ 25,25 });

	GameEngineImage* ArrowBlue = GameEngineImageManager::GetInst()->Find("Arrow_Blue.bmp");
	ArrowBlue->Cut({ 25,25 });

	GameEngineImage* ArrowYellow = GameEngineImageManager::GetInst()->Find("Arrow_Yellow.bmp");
	ArrowYellow->Cut({ 21,22 });

	GameEngineImage* ShieldBlue = GameEngineImageManager::GetInst()->Find("Shield_Blue.bmp");
	ShieldBlue->Cut({ 75,75 });

	GameEngineImage* ShieldRed = GameEngineImageManager::GetInst()->Find("Shield_Red.bmp");
	ShieldRed->Cut({ 75,75 });

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


		GameEngineImage* FightButton = GameEngineImageManager::GetInst()->Find("FightButton.bmp");
		FightButton->Cut({ 110,42 });

		GameEngineImage* FightButton2 = GameEngineImageManager::GetInst()->Find("FightButton2.bmp");
		FightButton2->Cut({ 165,63 });

		GameEngineImage* MercyButton = GameEngineImageManager::GetInst()->Find("MercyButton.bmp");
		MercyButton->Cut({ 165,63 });

		GameEngineImage* ActionButton = GameEngineImageManager::GetInst()->Find("ActionButton.bmp");
		ActionButton->Cut({ 165,63 });

		GameEngineImage* ItemButton = GameEngineImageManager::GetInst()->Find("ItemButton.bmp");
		ItemButton->Cut({ 165,63 });

		GameEngineImage* JudgBar = GameEngineImageManager::GetInst()->Find("Judg_Bar.bmp");
		JudgBar->Cut({ 14,128 });

		GameEngineImage* Effect = GameEngineImageManager::GetInst()->Find("Attack_Effect.bmp");
		Effect->Cut({ 100,147 });

		GameEngineImage* Number = GameEngineImageManager::GetInst()->Find("UI_Number.bmp");
		Number->Cut({ 28,28 });

		GameEngineImage* Number2 = GameEngineImageManager::GetInst()->Find("Hp_Number.bmp");
		Number2->Cut({ 28,28 });

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
		GameEngineInput::GetInst()->CreateKey("ChangeFloweyTalk", '5');


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