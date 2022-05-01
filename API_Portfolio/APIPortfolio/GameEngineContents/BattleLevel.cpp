#include "BattleLevel.h"
#include "ContentsEnums.h"
#include "BattleLevelActor.h"
#include "Player.h"
#include "Undyne.h";
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

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

	Undyne_ = CreateActor<Undyne>((int)BATTLELEVELORDER::BACKGROUND);
	Undyne_->SetPosition({ 690,175 });

	Button_ = CreateActor<UIButton>((int)BATTLELEVELORDER::BOX);
	Button_->SetPosition({ 250,650 });



	//Å°»ý¼º
	{
		if (false == GameEngineInput::GetInst()->IsKey("UI_Left"))
		{
			GameEngineInput::GetInst()->CreateKey("UI_Left", VK_LEFT);
			GameEngineInput::GetInst()->CreateKey("UI_Right", VK_RIGHT);
			GameEngineInput::GetInst()->CreateKey("UI_Up", VK_UP);
			GameEngineInput::GetInst()->CreateKey("UI_Down", VK_DOWN);
			GameEngineInput::GetInst()->CreateKey("UI_Action", 'Z');
		}
	}

}

void BattleLevel::Update()
{
	BattleStateUpdate(CurState_);

	if (true == GameEngineInput::GetInst()->IsPress("ChangeDebug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

	CheckPlayerKey();
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
	Player::MainPlayer->SetPosition({ 191.0f, 650.0f });
	Player::MainPlayer->Stop();
	

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

void BattleLevel::CheckPlayerKey()
{
	if (true == GameEngineInput::GetInst()->IsDown("UI_Left"))
	{
		float4 Dir = Player::MainPlayer->GetPosition();
		Dir.x -= 265.0f;
		Player::MainPlayer->SetPosition(Dir);

		if (191.0f >= Player::MainPlayer->GetPosition().x)
		{
			Player::MainPlayer->SetPosition({ 191,650 });
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("UI_Right"))
	{
		float4 Dir = Player::MainPlayer->GetPosition();
		Dir.x += 265.0f;
		Player::MainPlayer->SetPosition(Dir);

		if (986.0f <= Player::MainPlayer->GetPosition().x)
		{
			Player::MainPlayer->SetPosition({ 986,650 });
		}
	}




}



