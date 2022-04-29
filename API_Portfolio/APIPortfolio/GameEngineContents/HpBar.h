#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class HpBar	: public GameEngineActor
{
public:
	// constrcuter destructer
	HpBar();
	~HpBar();

	// delete Function
	HpBar(const HpBar& _Other) = delete;
	HpBar(HpBar&& _Other) noexcept = delete;
	HpBar& operator=(const HpBar& _Other) = delete;
	HpBar& operator=(HpBar&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* HpBarRed_;
	GameEngineRenderer* HpBarYellow_;

	int PlayerHp_;
	int PlayerMaxHp_;
	float FullHpBar_;

};

