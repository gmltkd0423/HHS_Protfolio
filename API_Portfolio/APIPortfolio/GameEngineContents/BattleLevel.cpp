#include "BattleLevel.h"
#include "ContentsEnums.h"
#include "BattleLevelActor.h"
#include "Player.h"
#include "Undyne.h"
#include "AttackBar.h"
#include "SoundPlayer.h"
#include "AttackEffect.h"
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImage.h>
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>

BattleLevel::BattleLevel() :
	FightButtonDir_({}),
	ActionButtonDir_({}),
	MercyButtonDir_({}),
	ItemButtonDir_({}),
	Timer_(0.2f),
	BarTime_(0.4f),
	BarCount_(0)
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
	Undyne_->SetPosition({ 720,185 });

	Button_ = CreateActor<UIButton>((int)BATTLELEVELORDER::BOX);
	Button_->SetPosition({ 250,680 });

	TextBox = CreateActor<Box>((int)BATTLELEVELORDER::BOX);
	TextBox->SetPosition({ 640,490 });

	AttackBar_ = CreateActor<AttackBar>((int)BATTLELEVELORDER::BOX);
	AttackBar_->SetPosition({ 640,490 });
	AttackBar_->Off();

	Effect_ = CreateActor< AttackEffect>((int)BATTLELEVELORDER::ACTOR);
	Effect_->SetPosition({ 650,185 });
	Effect_->Off();
	//키생성
	{
		if (false == GameEngineInput::GetInst()->IsKey("UI_Left"))
		{
			GameEngineInput::GetInst()->CreateKey("UI_Left", VK_LEFT);
			GameEngineInput::GetInst()->CreateKey("UI_Right", VK_RIGHT);
			GameEngineInput::GetInst()->CreateKey("UI_Up", VK_UP);
			GameEngineInput::GetInst()->CreateKey("UI_Down", VK_DOWN);
			GameEngineInput::GetInst()->CreateKey("UI_Esc", VK_ESCAPE);
			GameEngineInput::GetInst()->CreateKey("UI_Action", 'Z');
		}
	}

	ChangeMenuState(MENUSTATE::SELECTMENU);
}

void BattleLevel::Update()
{
	MenuStateUpdate();

	if (true == GameEngineInput::GetInst()->IsPress("ChangeDebug"))
	{
		GameEngineLevel::IsDebugModeSwitch();
	}

	CheckEscape();
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
	Player::MainPlayer->SetPosition({ 191.0f, 680.0f });
	Player::MainPlayer->Stop();

	SoundPlayer::Bgm_ = GameEngineSound::SoundPlayControl("mus_x_undyne.ogg");
}

void BattleLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

}

void BattleLevel::ChangeMenuState(MENUSTATE _State)
{
	if (_State != CurMenuState_)
	{
		switch (_State)
		{
		case MENUSTATE::SELECTMENU:
			MenuSelectStart();
			break;
		case MENUSTATE::FIGHTMENU:
			FightMenuStart();
			break;
		case MENUSTATE::ACTIONMENU:
			ActionMenuStart();
			break;
		case MENUSTATE::MERCYMENU:
			break;
		case MENUSTATE::ITEMMENU:
			break;
		default:
			break;
		}

		CurMenuState_ = _State;
	}
}

void BattleLevel::MenuStateUpdate()
{
	switch (CurMenuState_)
	{
	case MENUSTATE::SELECTMENU:
		MenuSelectUpdate();
		break;
	case MENUSTATE::FIGHTMENU:
		FightMenuUpdate();
		break;
	case MENUSTATE::MERCYMENU:
		break;
	case MENUSTATE::ACTIONMENU:
		ActionMenuUpdate();
		break;
	case MENUSTATE::ITEMMENU:
		break;
	default:
		break;
	}
}

void BattleLevel::UISetting()
{
}

void BattleLevel::CreateBar()
{
	if (3 <= Count_)
	{
		return;
	}

	Timer_ -= GameEngineTime::GetDeltaTime();

	if (0 >= Timer_)
	{
		Judge_Bar = CreateActor<Bar>((int)BATTLELEVELORDER::ACTOR);
		Judge_Bar->SetPosition({ 100,490 });
		BarList[Count_] = Judge_Bar;
		Count_++;
		if (Count_ == 1)
		{
			Timer_ = 0.1f;
		}
		else
		{
			Timer_ = 0.2f;
		}
	}


}

void BattleLevel::UIKeyMove()
{

	if (true == GameEngineInput::GetInst()->IsDown("UI_Left"))
	{
		float4 Dir = Player::MainPlayer->GetPosition();
		Dir.x -= 265.0f;
		Player::MainPlayer->SetPosition(Dir);

		if (191.0f >= Player::MainPlayer->GetPosition().x)
		{
			Player::MainPlayer->SetPosition({ 191,680 });
		}
	}

	if (true == GameEngineInput::GetInst()->IsDown("UI_Right"))
	{
		float4 Dir = Player::MainPlayer->GetPosition();
		Dir.x += 265.0f;
		Player::MainPlayer->SetPosition(Dir);

		if (986.0f <= Player::MainPlayer->GetPosition().x)
		{
			Player::MainPlayer->SetPosition({ 986,680 });
		}
	}
}

void BattleLevel::SelectButton()
{
	//Fight버튼을 눌럿다면
	if (true == Button_->GetbFightButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		ChangeMenuState(MENUSTATE::FIGHTMENU);
		FightButtonDir_ = Player::MainPlayer->GetPosition();
	}
	else if (true == Button_->GetbActionButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		ChangeMenuState(MENUSTATE::ACTIONMENU);
		ActionButtonDir_ = Player::MainPlayer->GetPosition();
	}
	else if (true == Button_->GetbMercyButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		ChangeMenuState(MENUSTATE::MERCYMENU);
		MercyButtonDir_ = Player::MainPlayer->GetPosition();
	}
	else if (true == Button_->GetbItemButton() && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		ChangeMenuState(MENUSTATE::ITEMMENU);
		ItemButtonDir_ = Player::MainPlayer->GetPosition();
	}

}

void BattleLevel::CheckEscape()
{
	if (MENUSTATE::ACTIONMENU == CurMenuState_	||
		MENUSTATE::FIGHTMENU == CurMenuState_	||
		MENUSTATE::MERCYMENU == CurMenuState_ || 
		MENUSTATE::ITEMMENU == CurMenuState_)
	{
		if (true == GameEngineInput::GetInst()->IsDown("UI_Esc"))
		{
			if (MENUSTATE::FIGHTMENU == CurMenuState_)
			{
				AttackBar_->Off();
				Judge_Bar->Off();
			}


			PrevMenuState_ = CurMenuState_;
			ChangeMenuState(MENUSTATE::SELECTMENU);

			
		}
	}


}

void BattleLevel::MenuSelectStart()
{
	if (MENUSTATE::FIGHTMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(FightButtonDir_);
	}
	else if (MENUSTATE::ACTIONMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(ActionButtonDir_);
	}
	else if (MENUSTATE::MERCYMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(MercyButtonDir_);
	}
	else if (MENUSTATE::ITEMMENU == PrevMenuState_)
	{
		Player::MainPlayer->SetPosition(ItemButtonDir_);

	}


	Player::MainPlayer->Stop();
}


void BattleLevel::MenuSelectUpdate()
{
	UIKeyMove();
	SelectButton();
}

void BattleLevel::FightMenuStart()
{
	Count_ = 0;
	AttackBar_->On();
	Bar::BarCount_ = 0;
	Bar::KeyDownCount_ = 0;
	Bar::Damage_ = 0;
	Timer_ = 0.4f;
	HurtEnd = false;
	BarCount_ = 0;
}

void BattleLevel::FightMenuUpdate()
{
	CreateBar();
	/*for (size_t i = 0; i < 3; i++)
	{
		if (BarList[i] != nullptr)
		{
			if (1000 <= BarList[i]->GetPosition().x)
			{
				BarList[i]->Off();
				Bar::KeyDownCount_++;
			}
		}
	}*/

	if (BarCount_ == 2 && HurtEnd ==false )
	{
		Effect_->On();
		Timer_ -= GameEngineTime::GetDeltaTime();
		if (0 >= Timer_)
		{
			Effect_->Off();
			Undyne_->Hurt();
			HurtEnd = true;
		}
	}

	if (3 <= Count_ && 6>Count_ && true == GameEngineInput::GetInst()->IsDown("UI_Action"))
	{
		BarCount_ = Count_ - 3;
		BarList[BarCount_]->SetIsKeyDownTrue();
		Count_++;
	}

	int a = Bar::Damage_;


}

void BattleLevel::ActionMenuStart()
{
}

void BattleLevel::ActionMenuUpdate()
{
	int a = 0;
}



