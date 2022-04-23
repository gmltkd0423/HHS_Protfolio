#pragma once
#include <GameEngine/GameEngineLevel.h>
#include <GameEngineBase/GameEngineSound.h>
#include "Player.h"
#include "Flowey.h"

// Ό³Έν :
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
	bool TalkEvent_;
	bool CheckPos_;



	Player* Player_;
	Flowey* Flowey_;
	GameEngineActor* FloweyTalk;
	GameEngineActor* TextBox;
	GameEngineRenderer* FloweyTalkRenderer;
	GameEngineRenderer* TextBoxRenderer;
	GameEngineImage* MapColImage_;

	GameEngineSoundPlayer Bgm_;

private:
	void Init();
	void CheckPlayerPosition();
	void CheckChangeLevelKey();

	void FloweyTalkEvent();
	void MoveNextLevel();
};

