#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class SpearCircle	:public GameEngineActor
{
public:
	static int SpearCount;
	// constrcuter destructer
	SpearCircle();
	~SpearCircle();

	// delete Function
	SpearCircle(const SpearCircle& _Other) = delete;
	SpearCircle(SpearCircle&& _Other) noexcept = delete;
	SpearCircle& operator=(const SpearCircle& _Other) = delete;
	SpearCircle& operator=(SpearCircle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* SpearRenderer;
	GameEngineCollision* SpearCol;

	bool LookPlayer;
	bool IsSpin;
	bool Alpha;
	float Angle;
	float MoveAngle;
	float Timer_;
	float Speed_;
	int Value;

	float4 MoveDir;
	float4 PlayerPos;

};

