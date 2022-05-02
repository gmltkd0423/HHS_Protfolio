#pragma once
#include <GameEngine/GameEngineActor.h>


enum class BoxState
{
	Text,
	Battle
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

private:
	void Shake();

	void TextStateStart();
	void TextStateUpdate();
	
	void BattleStateStart();
	void BattleStateUpdate();

	void ChangeState(BoxState _State);
	void StateUpdate();

public:
	inline void SetIsShakeTrue()
	{
		IsShake = true;
	}

	inline void SetState(BoxState _State)
	{
		ChangeState(_State);
	}
};
