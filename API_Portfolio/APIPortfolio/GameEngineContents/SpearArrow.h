#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class SpearArrow	:public GameEngineActor
{
public:
	// constrcuter destructer
	SpearArrow();
	~SpearArrow();

	// delete Function
	SpearArrow(const SpearArrow& _Other) = delete;
	SpearArrow(SpearArrow&& _Other) noexcept = delete;
	SpearArrow& operator=(const SpearArrow& _Other) = delete;
	SpearArrow& operator=(SpearArrow&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* SpearRenderer;

	float Angle;
};

