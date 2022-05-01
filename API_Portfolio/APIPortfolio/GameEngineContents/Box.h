#pragma once
#include <GameEngine/GameEngineActor.h>


// Ό³Έν :
class Box :public GameEngineActor
{
public:
	// constrcuter destructer
	Box();
	~Box();

	// delete Function
	Box(const Box& _Other) = delete;
	Box(Box&& _Other) noexcept = delete;
	Box& operator=(const Box& _Other) = delete;
	Box& operator=(Box&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* TextBox;
};
