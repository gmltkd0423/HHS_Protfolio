#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :

class Trigger :public GameEngineActor
{
public:
	// constrcuter destructer
	Trigger();
	~Trigger();

	// delete Function
	Trigger(const Trigger& _Other) = delete;
	Trigger(Trigger&& _Other) noexcept = delete;
	Trigger& operator=(const Trigger& _Other) = delete;
	Trigger& operator=(Trigger&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	bool FireDeath_;


	GameEngineCollision* Fire_Trigger;


public:

	bool GetFireDeath()
	{
		return FireDeath_;
	}
};

