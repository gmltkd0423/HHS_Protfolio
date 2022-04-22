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


	GameEngineActor* FirstLineActor_;
	GameEngineActor* SecondLineActor_;
	GameEngineActor* ThirdLineActor_;
	GameEngineRenderer* FirstLineText_;
	GameEngineRenderer* SecondLineText_;
	GameEngineRenderer* ThirdLineText_;


	GameEngineActor* WordActor_[10];
	GameEngineRenderer* WordRenderer_[10];

	GameEngineActor* Word1Actor_;
	GameEngineActor* Word2Actor_;
	GameEngineActor* Word3Actor_;
	GameEngineActor* Word4Actor_;
	GameEngineRenderer* Word1Renderer_;
	GameEngineRenderer* Word2Renderer_;
	GameEngineRenderer* Word3Renderer_;
	GameEngineRenderer* Word4Renderer_;



	GameEngineSoundPlayer Bgm_;

private:
	void Init();
	void CheckPlayerPosition();

	void FloweyTalkEvent();
};

