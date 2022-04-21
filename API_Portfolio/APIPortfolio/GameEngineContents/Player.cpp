#include "Player.h"
#include <GameEngineBase/GameEngineWindow.h>
#include <GameEngineBase/GameEngineInput.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineImageManager.h>
#include <GameEngineBase/GameEngineTime.h>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngine/GameEngineLevel.h>
#include <GameEngine/GameEngine.h>


Player::Player() :
	MoveDir_(float4::ZERO)
{
}



Player::~Player()
{
}



void Player::Start()
{

	SetScale({ 60,60 });

	AniRender_ = CreateRenderer();
	AniRender_->SetScale({ 60,60 });

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


	if (false == GameEngineInput::GetInst()->IsKey("MoveLeft"))
	{
		GameEngineInput::GetInst()->CreateKey("MoveLeft", 'A');
		GameEngineInput::GetInst()->CreateKey("MoveRight", 'D');
		GameEngineInput::GetInst()->CreateKey("MoveUp", 'W');
		GameEngineInput::GetInst()->CreateKey("MoveDown", 'S');
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

	GetLevel()->SetCameraPos(GetPosition() - GameEngineWindow::GetScale().Half());
	CameraLock();
}



void Player::Render()
{
	//DebugRectRender();
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

void Player::CameraLock()
{
	float MapSizeX = 1280;
	float MapSizeY = 720;
	float CameraRectX = 300;
	float CameraRectY = 300;

	if (0 > GetLevel()->GetCameraPos().x)	// 카메라 x위치가 0보다 작아지면 카메라 좌표를 0으로 고정시킨다.
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (0 > GetLevel()->GetCameraPos().y)		// 카메라 y위치가 0보다 작아지면
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = 0;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeX < GetLevel()->GetCameraPos().x + CameraRectX)		// 카메라 x위치가 맵 크기보다 커지면
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.x = MapSizeX - CameraRectX;
		GetLevel()->SetCameraPos(CurCameraPos);
	}
	if (MapSizeY < GetLevel()->GetCameraPos().y + CameraRectY)		// 카메라 y위치가 맵 크기보다 커지면
	{
		float4 CurCameraPos = GetLevel()->GetCameraPos();
		CurCameraPos.y = MapSizeY - CameraRectY;
		GetLevel()->SetCameraPos(CurCameraPos);
	}

}
