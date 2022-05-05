#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class Shield	:public GameEngineActor
{
public:
	// constrcuter destructer
	Shield();
	~Shield();

	// delete Function
	Shield(const Shield& _Other) = delete;
	Shield(Shield&& _Other) noexcept = delete;
	Shield& operator=(const Shield& _Other) = delete;
	Shield& operator=(Shield&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* ShieldRenderer;
};

