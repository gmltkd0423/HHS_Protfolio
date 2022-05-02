#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngineBase/GameEngineSound.h>

// Ό³Έν :
class AttackEffect	:public GameEngineActor
{
public:
	// constrcuter destructer
	AttackEffect();
	~AttackEffect();

	// delete Function
	AttackEffect(const AttackEffect& _Other) = delete;
	AttackEffect(AttackEffect&& _Other) noexcept = delete;
	AttackEffect& operator=(const AttackEffect& _Other) = delete;
	AttackEffect& operator=(AttackEffect&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* EffectRenderer;
	GameEngineSound EffectSound_;

private:
	bool IsHurt;
	bool IsIdle;

private:
	void Shake();
};

