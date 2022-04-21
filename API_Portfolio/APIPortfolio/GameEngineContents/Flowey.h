#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class Flowey	: public GameEngineActor
{
public:
	// constrcuter destructer
	Flowey();
	~Flowey();

	// delete Function
	Flowey(const Flowey& _Other) = delete;
	Flowey(Flowey&& _Other) noexcept = delete;
	Flowey& operator=(const Flowey& _Other) = delete;
	Flowey& operator=(Flowey&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* AniRender_;
};

