#pragma once
#include<GameEngine/GameEngineActor.h>
#include<GameEngine/GameEngineRenderer.h>

// Ό³Έν :
class FloweyBullet	:public GameEngineActor
{
public:
	// constrcuter destructer
	FloweyBullet();
	~FloweyBullet();

	// delete Function
	FloweyBullet(const FloweyBullet& _Other) = delete;
	FloweyBullet(FloweyBullet&& _Other) noexcept = delete;
	FloweyBullet& operator=(const FloweyBullet& _Other) = delete;
	FloweyBullet& operator=(FloweyBullet&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* AniRender_;
	float4 Pos_;
	float4 MoveDir_;
	float Speed_;
	int KeyCount_;
	int SpeedCount_;
	bool IsCheckPos_;



public:
	GameEngineRenderer* GetRenderer()
	{
		return AniRender_;
	}

	void SetSpeedCount(int _SpeedCount)
	{
		SpeedCount_ = _SpeedCount;
	}

	int GetSpeedCount()
	{
		return SpeedCount_;
	}

private:
	void CheckDeath();
};

