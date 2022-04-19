#pragma once
#include <GameEngine/GameEngineActor.h>

// Ό³Έν :
class TitleTime : public GameEngineActor
{
public:
	static float TitleTime_;
public:
	// constrcuter destructer
	TitleTime();
	~TitleTime();

	// delete Function
	TitleTime(const TitleTime& _Other) = delete;
	TitleTime(TitleTime&& _Other) noexcept = delete;
	TitleTime& operator=(const TitleTime& _Other) = delete;
	TitleTime& operator=(TitleTime&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
private:

};

