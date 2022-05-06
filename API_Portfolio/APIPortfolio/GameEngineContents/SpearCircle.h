#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class SpearCircle	:public GameEngineActor
{
public:
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

	bool LookPlayer;
	float Angle;
	float MoveAngle;
	float Timer_;

	float4 Dir;
	float4 PlayerPos;
};

