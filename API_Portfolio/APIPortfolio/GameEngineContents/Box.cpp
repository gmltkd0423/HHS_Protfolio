#include "Box.h"
#include "ContentsEnums.h"
#include <GameEngine/GameEngineCollision.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineTime.h>

Box::Box() :
	Time_(0.2f),
	Timer_(1.0f),
	IsShake(false),
	SetPos(false),
	Speed(50.0f),
	IsChange(false),
	SizeX(0),
	SizeY(0),
	IsFirst(false)
{
}

Box::~Box()
{
}

void Box::Start()
{
	TextBox = CreateRendererToScale("TextBox.bmp", { 1000,230 }, (int)BATTLELEVELORDER::BOX);
	BoxCol = CreateCollision("BoxCol", { SizeX,SizeY });
	ChangeState(BoxState::Text);
}

void Box::Update()
{
	StateUpdate();
	Shake();
}

void Box::Render()
{
}


void Box::Shake()
{
	if (true == IsShake)
	{
		if (false == SetPos)
		{
			float4 RanPos_ = { 3.0f,3.0f };


			Pos_ = GetPosition();
			RightDownPos_ = GetPosition() + RanPos_;
			LeftTopPos_ = GetPosition() - RanPos_;

		}


		SetPos = true;

		if (0.0f <= Timer_)
		{
			Timer_ -= GameEngineTime::GetDeltaTime();
			Time_ += GameEngineTime::GetDeltaTime();

			if (0.0f <= Time_ && false == IsRightDown)
			{
				MoveDir_ = float4::RIGHT * GameEngineTime::GetDeltaTime() * 100.0f;
				MoveDir2_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 100.0f;
				SetMove(MoveDir_);
				SetMove(MoveDir2_);

				if (GetPosition().x >= RightDownPos_.x && GetPosition().y >= RightDownPos_.y)
				{
					IsRightDown = true;
					RightDownPos_.x -= 1.0f;
					RightDownPos_.y -= 1.0f;
					//MoveDir_.x = GetPosition().x + 50.0f - Pos_.x;

					IsLeftTop = false;
				}
			}
			else if (0.1f <= Time_ && false == IsLeftTop)
			{
				MoveDir_ = float4::LEFT * GameEngineTime::GetDeltaTime() * 100.0f;
				MoveDir2_ = float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
				SetMove(MoveDir_);
				SetMove(MoveDir2_);
				if (GetPosition().x <= LeftTopPos_.x && GetPosition().y <= LeftTopPos_.y)
				{
					IsLeftTop = true;
					IsRightDown = false;
					LeftTopPos_.x += 1.0f;
					LeftTopPos_.y += 1.0f;
					Time_ = 0.0f;
				}


			}

			if (0.0f >= Timer_)
			{
				Timer_ = 1.0f;
				SetPosition(Pos_);
				IsShake = false;
				SetPos = false;
			}
		}
	}
}

void Box::TextStateStart()
{
	MyScale = TextBox->GetScale();
	SizeX = 0;
	SizeY = 0;
	IsChange = false;
}

void Box::TextStateUpdate()
{

	if (TextBox->GetScale().x >= 1000.0f && TextBox->GetScale().y >= 230.0f)
	{

		if (TextBox->GetScale().y >= 230.0f && IsFirst==true)
		{
			SizeY = GameEngineTime::GetDeltaTime() * 600;
			TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y - SizeY });
		}
	


		if (false == IsChange && GetPosition().y <= 490.0f && false == IsShake)
		{
			MoveDir_ = float4::DOWN * GameEngineTime::GetDeltaTime() * 600.0f;
			SetMove(MoveDir_);

			if (GetPosition().y >= 490.0f)
			{
				BoxCol->SetScale(TextBox->GetScale());
				IsChange = true;
			}
		}
		else if (false == IsChange && GetPosition().y >= 490.0f && false == IsShake)
		{
				BoxCol->SetScale(TextBox->GetScale());
				IsChange = true;
		}

		return;
	}




	if (TextBox->GetScale().x <= 1000.0f)
	{
		SizeX = GameEngineTime::GetDeltaTime() * 1200;
		TextBox->SetScale({ TextBox->GetScale().x + SizeX, TextBox->GetScale().y });
	}
	else
	{

		SizeY = GameEngineTime::GetDeltaTime() * 600;
		TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y + SizeY });

	}
}





void Box::Battle2StateStart()
{
	MyScale = TextBox->GetScale();
	SizeX = 0;
	SizeY = 0;
	IsChange=false;
}


//창위로올라는패턴
void Box::Battle2StateUpdate()
{
	if (TextBox->GetScale().x <= 100.0f && TextBox->GetScale().y <= 100.0f)
	{
		if (false == IsChange && GetPosition().y >= 490.0f && false == IsShake)
		{

			BoxCol->SetScale(TextBox->GetScale());
			IsChange = true;
		}

		return;
	}

	if (TextBox->GetScale().x >= 100.0f)
	{
		SizeX = GameEngineTime::GetDeltaTime() * 1200;
		TextBox->SetScale({ TextBox->GetScale().x - SizeX, TextBox->GetScale().y });
	}
	else
	{

		SizeY = GameEngineTime::GetDeltaTime() * 600;
		TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y - SizeY });

	}
}

void Box::Battle3StateStart()
{
	MyScale = TextBox->GetScale();
	SizeX = 0;
	SizeY = 0;
	IsChange = false;
}

void Box::Battle3StateUpdate()
{
	if (TextBox->GetScale().x <= 100.0f && TextBox->GetScale().y <= 100.0f)
	{
		if (false == IsChange && GetPosition().y >= 360.0f && false == IsShake)
		{
			MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 500.0f;
			SetMove(MoveDir_);

			if (GetPosition().y <= 360.0f)
			{
				BoxCol->SetScale(TextBox->GetScale());
				IsChange = true;
			}
		}
		return;
	}
	if (TextBox->GetScale().x >= 100.0f)
	{
		SizeX = GameEngineTime::GetDeltaTime() * 1200;
		TextBox->SetScale({ TextBox->GetScale().x - SizeX, TextBox->GetScale().y });
	}
	else
	{

		SizeY = GameEngineTime::GetDeltaTime() * 600;
		TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y - SizeY });

	}
}

void Box::Battle4StateStart()
{
	IsChange = false;
	MyScale = TextBox->GetScale();
	SizeX = 0;
	SizeY = 0;
}

void Box::Battle4StateUpdate()
{
	if (TextBox->GetScale().x >= 1000.0f)
	{
		if (false == IsChange && GetPosition().y >= 350.0f && false == IsShake)
		{
			MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 400.0f;
			SetMove(MoveDir_);

			if (GetPosition().y <= 350.0f)
			{
				BoxCol->SetScale(TextBox->GetScale());
				IsChange = true;
			}
		}

	}

	if (TextBox->GetScale().x <= 1000.0f)
	{
		SizeX = GameEngineTime::GetDeltaTime() * 1200;
		TextBox->SetScale({ TextBox->GetScale().x + SizeX, TextBox->GetScale().y });
	}
	else if(TextBox->GetScale().y<=450)
	{

		SizeY = GameEngineTime::GetDeltaTime() * 600;
		TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y + SizeY });

	}
}

void Box::Battle1StateStart()
{
	IsChange = false;
	MyScale = TextBox->GetScale();
	SizeX = 0;
	SizeY = 0;
}

void Box::Battle1StateUpdate()
{
	if (TextBox->GetScale().x <= 300.0f && TextBox->GetScale().y <= 300.0f)
	{
		if (false == IsChange && GetPosition().y >= 450.0f && false == IsShake)
		{
			MoveDir_ = float4::UP * GameEngineTime::GetDeltaTime() * 100.0f;
			SetMove(MoveDir_);

			if (GetPosition().y <= 450.0f)
			{
				BoxCol->SetScale(TextBox->GetScale());
				IsChange = true;
			}
		}

		return;
	}

	if (TextBox->GetScale().x >= 300.0f)
	{
		SizeX = GameEngineTime::GetDeltaTime() * 1200;
		TextBox->SetScale({ TextBox->GetScale().x - SizeX, TextBox->GetScale().y });
	}
	else
	{

		SizeY = GameEngineTime::GetDeltaTime() * 600;
		TextBox->SetScale({ TextBox->GetScale().x , TextBox->GetScale().y - SizeY });

	}
	
}


void Box::ChangeState(BoxState _State)
{
	if (_State != CurState_)
	{
		switch (_State)
		{
		case BoxState::Text:
			TextStateStart();
			break;
		case BoxState::Battle1:
			Battle1StateStart();
			break;
		case BoxState::Battle2:
			Battle2StateStart();
			break;
		case BoxState::Battle3:
			Battle3StateStart();
			break;
		case BoxState::Battle4:
			Battle4StateStart();
			break;
		case BoxState::None:
			IsFirst = true;
			break;
		default:
			break;
		}

		CurState_ = _State;
	}
}

void Box::StateUpdate()
{
	switch (CurState_)
	{
	case BoxState::Text:
		TextStateUpdate();
		break;
	case BoxState::Battle1:
		Battle1StateUpdate();
		break;
	case BoxState::Battle2:
		Battle2StateUpdate();
		break;
	case BoxState::Battle3:
		Battle3StateUpdate();
		break;
	case BoxState::Battle4:
		Battle4StateUpdate();
		break;
	case BoxState::None:
		return;
	default:
		break;
	}
}
