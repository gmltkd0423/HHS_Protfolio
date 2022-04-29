#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>
#include <GameEngineBase/GameEngineSound.h>

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

	GameEngineFont TextFont_;
	GameEngineSound TextSound_;

	float Time_;
	float Timer_;
	float SoundTime_;
	std::wstring Text_;
	std::wstring RealText_;

	int TextCount_;
	int Count_;


	void Texts();
};

