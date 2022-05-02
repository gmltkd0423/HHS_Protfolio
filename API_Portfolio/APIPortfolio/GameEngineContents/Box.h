#pragma once
#include <GameEngine/GameEngineActor.h>


enum class BoxState
{
	Text,
	Battle1,
	Battle2,
	Battle3,
};




// Ό³Έν :
class Box :public GameEngineActor
{
public:
	// constrcuter destructer
	Box();
	~Box();

	// delete Function
	Box(const Box& _Other) = delete;
	Box(Box&& _Other) noexcept = delete;
	Box& operator=(const Box& _Other) = delete;
	Box& operator=(Box&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TextBox;
	GameEngineCollision* BoxCol;

	float Timer_;
	float Time_;
	float4 MoveDir_;
	float4 MoveDir2_;
	float4 RightDownPos_;
	float4 LeftTopPos_;
	float4 Pos_;

	bool IsShake;
	bool SetPos;

	bool IsRightDown;
	bool IsLeftTop;

	BoxState CurState_;
	float4 MyScale;

	float SizeX;
	float SizeY;
	float Speed;
	bool IsChange;

	int Pattern;

private:
	void Shake();

	void TextStateStart();
	void TextStateUpdate();
	
	void Battle1StateStart();
	void Battle1StateUpdate();

	void Battle2StateStart();
	void Battle2StateUpdate();

	void Battle3StateStart();
	void Battle3StateUpdate();

	void ChangeState(BoxState _State);
	void StateUpdate();

	

public:
	inline void SetIsShakeTrue()
	{
		IsShake = true;
	}

	bool GetIsChange()
	{
		return IsChange;
	}

	void SetIsChangeFalse()
	{
		IsChange = false;
	}

	inline void SetState(BoxState _State)
	{
		ChangeState(_State);
	}
};
