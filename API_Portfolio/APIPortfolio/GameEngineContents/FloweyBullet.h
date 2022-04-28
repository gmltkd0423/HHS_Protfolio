#pragma once
#include<GameEngine/GameEngineActor.h>
#include<GameEngine/GameEngineRenderer.h>

// ���� :
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
	int Count_;

	float4 BulletPos_[5];
	float4 Count10Dir_[5];



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

	inline void SetCount(int _Count)
	{
		Count_ = _Count;
	}

private:
	void CheckDeath();
};

