#include "BattleLevel.h"
#include "ContentsEnums.h"
#include "BattleLevelActor.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>

BattleLevel::BattleLevel() 
{
}

BattleLevel::~BattleLevel() 
{
}

void BattleLevel::Loading()
{
	GameEngineActor* BackGround = CreateActor<BattleLevelActor>((int)BATTLELEVELORDER::BACKGROUND);
	GameEngineRenderer* Back = BackGround->CreateRenderer("BattleLevelBackGround.bmp",  (int)BATTLELEVELORDER::BACKGROUND);
	float4 Half = Back->GetImage()->GetScale().Half();
	Back->SetPivot(Half);
}

void BattleLevel::Update()
{
	BattleStateUpdate(CurState_);
}

void BattleLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	if (nullptr == Player::MainPlayer)
	{
		Player::MainPlayer = CreateActor<Player>((int)PLAYLEVELORDER::PLAYER);
	}

	Player::MainPlayer->IsHeart();
	Player::MainPlayer->SetSpeed(150.0f);
	Player::MainPlayer->CollisionImage("Level2_ColMap.bmp");
	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->CamPosOff();
	Player::MainPlayer->SetPosition({ GameEngineWindow::GetScale().Half().x,  500 });

	

	CurState_ = BATTLELEVELSTATE::FLOWEY;

}

void BattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void BattleLevel::BattleStateUpdate(BATTLELEVELSTATE _State)
{




	switch (_State)
	{
	case BATTLELEVELSTATE::FLOWEY:
		Battle_Flowey();
		break;
	case BATTLELEVELSTATE::NONE:
		return;
	}

	CurState_ = BATTLELEVELSTATE::NONE;
	
}

void BattleLevel::Battle_Flowey()
{




}

void BattleLevel::UISetting()
{


}



