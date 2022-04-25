#include "Player.h"
#include "ContentsEnums.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngine.h>

Player* Player::MainPlayer = nullptr;


Player::Player() :
	MoveDir_(float4::ZERO),
	IsMove_(false),
	MapSizeX(0),
	MapSizeY(0),
	CamRectX(0),
	CamRectY(0),
	CamPos_(true),
	Speed_(500.0f),
	IsBlink_(false),
	BlinkTime_(1.0f),
	IsAlphaOn_(true)

{
}



Player::~Player()
{
}



void Player::Start()
{
	IsMove_ = true;

	//SetScale({ 60,60 });

	{
		Heart_ = CreateRendererToScale("Heart.bmp", { 20,20 }, (int)BATTLELEVELORDER::ACTOR);
		Heart_->SetTransColor(RGB(255, 102, 255));
	}



	//애니메이션
	{
		AniRender_ = CreateRenderer();
		AniRender_->SetScale({ 70,90 });

		AniRender_->CreateAnimation("Move_Down.bmp", "MoveDown", 0, 3, 0.15f, true);
		AniRender_->CreateAnimation("Move_Down.bmp", "MoveDownIdle", 0, 0, 0.15f, true);
		AniRender_->CreateAnimation("Move_Up.bmp", "MoveUp", 0, 3, 0.15f, true);
		AniRender_->CreateAnimation("Move_Up.bmp", "MoveUpIdle", 0, 0, 0.15f, true);
		AniRender_->CreateAnimation("Move_Right.bmp", "MoveRight", 0, 1, 0.15f, true);
		AniRender_->CreateAnimation("Move_Right.bmp", "MoveRightIdle", 0, 0, 0.15f, true);
		AniRender_->CreateAnimation("Move_Left.bmp", "MoveLeft", 0, 1, 0.15f, true);
		AniRender_->CreateAnimation("Move_Left.bmp", "MoveLeftIdle", 0, 0, 0.15f, true);
		AniRender_->ChangeAnimation("MoveDownIdle");
		AniRender_->SetTransColor(RGB(255, 255, 255));

	}



	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", VK_LEFT);
		GameEngineInput::GetInst()->CreateKey("MoveRight", VK_RIGHT);
		GameEngineInput::GetInst()->CreateKey("MoveUp", VK_UP);
		GameEngineInput::GetInst()->CreateKey("MoveDown", VK_DOWN);
		GameEngineInput::GetInst()->CreateKey("Action", 'Z');
	}

	CurState_ = PlayerState::Idle;

	MapColImage_ = GameEngineImageManager::GetInst()->Find("Level1_ColMap.bmp");

	if (nullptr == MapColImage_)
	{
		MsgBoxAssert("맵 충돌용 이미지를 찾지 못했습니다.");
	}

	LevelRegist("MainPlayer");
}


void Player::Update()
{
	StateUpdate();

	if (CamPos_ == true)
	{
		GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());
		CameraLock();
	}

	CheckLevel();

	Blink();
}



void Player::Render()
{
	//DebugRectRender();
}

void Player::CollisionImage(const std::string& _Name)
{
	MapColImage_ = GameEngineImageManager::GetInst()->Find(_Name);
}

void Player::ChangeState(PlayerState _State)
{
	



	if (_State != CurState_)
	{
		switch (_State)
		{
		case PlayerState::Idle:
			IdleStart();
			break;
		case PlayerState::Move:
			MoveStart();
			break;
		default:
			break;
		}

		CurState_ = _State;
	}
}

void Player::StateUpdate()
{
	switch (CurState_)
	{
	case PlayerState::Idle:
		IdleUpdate();
		break;
	case PlayerState::Move:
		MoveUpdate();
		break;
	default:
		break;
	}
}

bool Player::IsActionKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown("Action"))
	{
		return false;
	}
	return true;
}

bool Player::IsPressAnyMoveKey()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight")
		)
	{
		return false;
	}
	return true;
}

bool Player::IsKeyDown()
{
	if (false == GameEngineInput::GetInst()->IsDown("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsDown("MoveUp") &&
		false == GameEngineInput::GetInst()->IsDown("MoveDown") &&
		false == GameEngineInput::GetInst()->IsDown("MoveRight") 
		)
	{
		return false;
	}
	return true;
}

bool Player::IsKeyPress()
{
	if (false == GameEngineInput::GetInst()->IsPress("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsPress("MoveUp") &&
		false == GameEngineInput::GetInst()->IsPress("MoveDown") &&
		false == GameEngineInput::GetInst()->IsPress("MoveRight") 
		)
	{
		return false;
	}
	return true;
}

bool Player::IsKeyUp()
{
	if (false == GameEngineInput::GetInst()->IsUp("MoveLeft") &&
		false == GameEngineInput::GetInst()->IsUp("MoveUP") &&
		false == GameEngineInput::GetInst()->IsUp("MoveDown") &&
		false == GameEngineInput::GetInst()->IsUp("MoveRight") 
		)
	{
		return false;
	}

	return true;
}

void Player::CheckWall(float4 _Value)
{
	float4 NextPos = GetPosition() + _Value;
	int Color = MapColImage_->GetImagePixel(NextPos);
	if (RGB(0, 0, 0) != Color)
	{
		SetMove(_Value);
	}
}

void Player::Blink()
{
	

}

void Player::CheckLevel()
{
	if (strcmp(GetLevel()->GetNameConstPtr(), "BattleLevel") == 0 || strcmp(GetLevel()->GetNameConstPtr(), "FloweyBattleLevel") == 0)
	{
		AniRender_->Off();
		Heart_->On();
	}
	else
	{
		AniRender_->On();
		Heart_->Off();
	}
}


void Player::Play()
{
	IsMove_ = true;
}

void Player::Stop()
{
	IsMove_ = false;
	MoveDir_ = float4::ZERO;
	AniRender_->ChangeAnimation("MoveUpIdle");
}

void Player::CameraLock()
{

	if (strcmp(GetLevel()->GetNameConstPtr(), "PlayLevel") == 0)
	{
		MapSizeX = 2300;
		MapSizeY = 1000;
		CamRectX = 1280;
		CamRectY = 720;
	}
	else if (strcmp(GetLevel()->GetNameConstPtr(), "PlayLevel2") == 0)
	{
		MapSizeX = 1280;
		MapSizeY = 1500;
		CamRectX = 1280;
		CamRectY = 720;
	}

	//float MapSizeX = 1280;
	//float MapSizeY = 720;
	//float CameraRectX = 300;
	//float CameraRectY = 400;
	float4 CurCameraPos = GetLevel()->GetCameraPos();

	if (0 > GetLevel()->GetCameraPos().x)	
	{
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)		
	{
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

	//if (GameEngineWindow::GetScale().Half().y - (MapSizeY / 2) > GetLevel()->GetCameraPos().y)		// 카메라 y위치가 맵보다 작아지면
	//{
	//	CurCameraPos.y = GameEngineWindow::GetScale().Half().y - (MapSizeY / 2) + CamRectY;
	//	GetLevel()->SetCameraPos(CurCameraPos);
	//}

	if (MapSizeX < GetLevel()->GetCameraPos().x + CamRectX)		// 카메라 x위치가 맵 크기보다 커지면
	{
		CurCameraPos.x = MapSizeX - CamRectX;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeY < GetLevel()->GetCameraPos().y + CamRectY)		// 카메라 y위치가 맵 크기보다 커지면
	{
		CurCameraPos.y = MapSizeY - CamRectY;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}



void Player::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	MainPlayer = this;
}