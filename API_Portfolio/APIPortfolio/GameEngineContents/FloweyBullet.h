#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

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
	GameEngineCollision* BulletCol_;
	GameEngineRenderer* AniRender_;
	float4 Pos_;
	float4 MoveDir_;
	float Speed_;
	int KeyCount_;
	int SpeedCount_;
	bool IsCheckPos_;
	int Count_;
	bool DeathCheck_;
	bool IsCircleBullet;
	float len;
	bool PhaseStart_;
	bool PhaseEnd_;


	float4 BulletPos_[5];
	float4 Count10Dir_[5];



public:
	GameEngineRenderer* GetRenderer()
	{
		return AniRender_;
	}

	inline void SetDeathCheck()
	{
		DeathCheck_ = false;
	}

	inline void SetRendererOrder(int _Order)
	{
		AniRender_->SetOrder(_Order);
	}

	bool GetDeathCheck()
	{
		return DeathCheck_;
	}

	void SetPhaseStart()
	{
		PhaseStart_ = true;
	}

	bool GetPhaseEnd()
	{
		return PhaseEnd_;
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
	void NormalBullet();
	void CircleBullet();
	void CheckDeath();
};

