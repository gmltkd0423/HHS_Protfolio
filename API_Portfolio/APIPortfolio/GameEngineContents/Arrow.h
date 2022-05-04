#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngineBase/GameEngineRandom.h>


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


	float4 Pos_[4];
	float Timer_;
	float Angle;
	float Angle2;
	int ArrowType;
	int IsYellow;
	bool ColorYellow;
	float len;

	bool IsUp;
	float4 MoveDir_;
	float4 MoveDirDown;
	float4 MoveDirUp;
	int Value;
	bool LookPlayer;
};

