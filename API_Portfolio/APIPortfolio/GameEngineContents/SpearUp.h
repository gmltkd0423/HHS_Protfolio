#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>
#include <GameEngine/GameEngineRenderer.h>


// Ό³Έν :
class SpearUp :public GameEngineActor
{
public:
	// constrcuter destructer
	SpearUp();
	~SpearUp();

	// delete Function
	SpearUp(const SpearUp& _Other) = delete;
	SpearUp(SpearUp&& _Other) noexcept = delete;
	SpearUp& operator=(const SpearUp& _Other) = delete;
	SpearUp& operator=(SpearUp&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* SpearRenderer;
	GameEngineSound SpearSound;

	float Timer_;
	float Angle;

	float4 MoveDir_;
	int Value;
	bool LookPlayer;
};

