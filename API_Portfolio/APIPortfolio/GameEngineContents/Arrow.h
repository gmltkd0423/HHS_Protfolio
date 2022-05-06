#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>
#include <GameEngine/GameEngineCollision.h>
#include <GameEngineBase/GameEngineSound.h>


// Ό³Έν :
class Arrow :public GameEngineActor
{
public:
	// constrcuter destructer
	Arrow();
	~Arrow();

	// delete Function
	Arrow(const Arrow& _Other) = delete;
	Arrow(Arrow&& _Other) noexcept = delete;
	Arrow& operator=(const Arrow& _Other) = delete;
	Arrow& operator=(Arrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* ArrowRenderer;
	GameEngineSound SpearSound;
	GameEngineRandom Ran;
	GameEngineRandom Yellow;
	GameEngineCollision* ArrowCol;

	float4 PlayerPos;
	float4 Pos_[4];
	float Timer_;
	float Angle;
	float UpDownAngle;
	float Angle2;
	int ArrowType;
	int IsYellow;
	bool ColorYellow;
	float len;
	bool IsSpin;

	bool IsUp;
	float4 MoveDir_;
	float4 MoveDirDown;
	float4 MoveDirUp;
	GameEngineSound Sound_;
	int Value;
	bool LookPlayer;

	void CheckCol();
};

