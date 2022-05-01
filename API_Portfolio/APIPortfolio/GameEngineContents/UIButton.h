#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class UIButton :public GameEngineActor
{
public:
	// constrcuter destructer
	UIButton();
	~UIButton();

	// delete Function
	UIButton(const UIButton& _Other) = delete;
	UIButton(UIButton&& _Other) noexcept = delete;
	UIButton& operator=(const UIButton& _Other) = delete;
	UIButton& operator=(UIButton&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* FightButton;
	GameEngineCollision* FightButtonCollision;

	GameEngineRenderer* ActionButton;
	GameEngineCollision* ActionButtonCollision;

	GameEngineRenderer* MercyButton;
	GameEngineCollision* MercyButtonCollision;

	GameEngineRenderer* ItemButton;
	GameEngineCollision* ItemButtonCollision;

	float4 ButtonSize;


private:
	void CheckCollision();
};
