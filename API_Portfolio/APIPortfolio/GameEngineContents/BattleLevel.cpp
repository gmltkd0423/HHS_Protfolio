#include "BattleLevel.h"
#include "ContentsEnums.h"
#include "BattleLevelActor.h"
#include "Player.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>

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
	Player::MainPlayer->GetLevel()->SetCameraPos({ 0,0 });
	Player::MainPlayer->CamPosOff();

	

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



