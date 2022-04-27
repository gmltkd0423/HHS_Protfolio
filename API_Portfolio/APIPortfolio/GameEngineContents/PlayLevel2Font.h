#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>


// Ό³Έν :
class PlayLevel2Font :public GameEngineActor
{
public:
	// constrcuter destructer
	PlayLevel2Font();
	~PlayLevel2Font();

	// delete Function
	PlayLevel2Font(const PlayLevel2Font& _Other) = delete;
	PlayLevel2Font(PlayLevel2Font&& _Other) noexcept = delete;
	PlayLevel2Font& operator=(const PlayLevel2Font& _Other) = delete;
	PlayLevel2Font& operator=(PlayLevel2Font&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:

	GameEngineFont TextFont_;

	float Time_;
	float Timer_;
	std::wstring Text_;
	std::wstring RealText_;

	bool IsAllTextOut;
	int TextCount_;
	int Count_;
	bool IsTalkEnd_;



	void Texts();

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

	inline void SetIsTalkEndFalse()
	{
		IsTalkEnd_ = false;
	}

	bool GetTalkEnd()
	{
		return IsTalkEnd_;
	}

	bool GetIsAllTextOut()
	{
		return IsAllTextOut;
	}
};

