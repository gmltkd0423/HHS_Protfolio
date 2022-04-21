#pragma once
#include <GameEngine/GameEngineLevel.h>
#include "Player.h"
#include "Flowey.h"

// ���� :
class PlayLevel2 :public GameEngineLevel
{
public:
	// constrcuter destructer
	PlayLevel2();
	~PlayLevel2();

	// delete Function
	PlayLevel2(const PlayLevel2& _Other) = delete;
	PlayLevel2(PlayLevel2&& _Other) noexcept = delete;
	PlayLevel2& operator=(const PlayLevel2& _Other) = delete;
	PlayLevel2& operator=(PlayLevel2&& _Other) noexcept = delete;

protected:
	void Loading() override;
	void Update() override;
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
	void LevelChangeEnd(GameEngineLevel* _NextLevel) override;
private:
	Player* Player_;
	Flowey* Flowey_;

private:
	void Init();
	void CheckPlayerPosition();
	bool CheckPos;
};

