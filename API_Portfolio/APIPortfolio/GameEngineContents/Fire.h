#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineRenderer.h>
#include <GameEngine/GameEngineCollision.h>

// Ό³Έν :

class Fire :public GameEngineActor
{
public:
	// constrcuter destructer
	Fire();
	~Fire();

	// delete Function
	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	float BlinkTimer_;
	float BlinkTime_;
	bool IsBlink_;
	float4 MoveDir_;


	GameEngineCollision* FireCol_;
	GameEngineRenderer* FireRenderer;


public:
	void Blink();

};

