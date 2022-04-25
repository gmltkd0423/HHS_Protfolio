#pragma once
#include<GameEngine/GameEngineActor.h>


// Ό³Έν :
class FadeInOut	: public GameEngineActor
{
public:
	// constrcuter destructer
	FadeInOut();
	~FadeInOut();

	// delete Function
	FadeInOut(const FadeInOut& _Other) = delete;
	FadeInOut(FadeInOut&& _Other) noexcept = delete;
	FadeInOut& operator=(const FadeInOut& _Other) = delete;
	FadeInOut& operator=(FadeInOut&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	bool IsFadeIn_;
	bool IsFadeOut_;

	float FadeSpeed_;
	int Value_;

	GameEngineRenderer* Back;
public:

	void FadeIn()
	{
		IsFadeIn_ = true;
	}

	void FadeOut()
	{
		IsFadeOut_ = true;
	}
};

