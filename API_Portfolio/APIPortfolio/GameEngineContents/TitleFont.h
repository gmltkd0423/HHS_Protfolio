#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>

// Ό³Έν :
class TitleFont	:public GameEngineActor
{
public:
	// constrcuter destructer
	TitleFont();
	~TitleFont();

	// delete Function
	TitleFont(const TitleFont& _Other) = delete;
	TitleFont(TitleFont&& _Other) noexcept = delete;
	TitleFont& operator=(const TitleFont& _Other) = delete;
	TitleFont& operator=(TitleFont&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineFont TextFont;

};

