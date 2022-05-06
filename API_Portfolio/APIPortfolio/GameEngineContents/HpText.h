#pragma once
#include <GameEngine/GameEngineActor.h>



// Ό³Έν :
class HpText	:public GameEngineActor
{
public:
	// constrcuter destructer
	HpText();
	~HpText();

	// delete Function
	HpText(const HpText& _Other) = delete;
	HpText(HpText&& _Other) noexcept = delete;
	HpText& operator=(const HpText& _Other) = delete;
	HpText& operator=(HpText&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* HpRenderer;
};

