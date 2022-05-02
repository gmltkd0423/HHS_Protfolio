#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>
#include <GameEngineBase/GameEngineSound.h>


// Ό³Έν :
class BattleLevelFont :public GameEngineActor
{
public:
	// constrcuter destructer
	BattleLevelFont();
	~BattleLevelFont();

	// delete Function
	BattleLevelFont(const BattleLevelFont& _Other) = delete;
	BattleLevelFont(BattleLevelFont&& _Other) noexcept = delete;
	BattleLevelFont& operator=(const BattleLevelFont& _Other) = delete;
	BattleLevelFont& operator=(BattleLevelFont&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineFont TextFont_;
	GameEngineSound TextSound_;

	float TextTime_;
	float Timer_;
	int TextCount_;
	int Count_;
	bool IsAllTextOut;

	std::wstring Text_;
	std::wstring RealText_;

	void Texts();
	void TextSounds();

public:
	inline void SetCount(int _Count)
	{
		Count_ = _Count;
	}

	inline void SetTextCount(int _TextCount)
	{
		TextCount_ = _TextCount;
	}


	inline void IsAllTextOutFalse()
	{
		IsAllTextOut = false;
	}

	inline void IsAllTextOutTrue()
	{
		IsAllTextOut = true;
	}

	bool GetIsAllTextOut()
	{
		return IsAllTextOut;
	}

};

