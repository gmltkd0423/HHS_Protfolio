#pragma once
#include<GameEngine/GameEngineActor.h>

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

};

