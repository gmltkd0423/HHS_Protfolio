#pragma once
#include <GameEngine/GameEngineActor.h>
#include <GameEngine/GameEngineFont.h>

// ���� :
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
	GameEngineFont TestFont;
	GameEngineFont TestFont2;

	GameEngineFont TextFont_;

	float Time_;

	float FontSizeX_;   //��Ʈx������
	float FontSizeY_;   //��Ʈy������

	float4 TextPos_;


	bool Title1TextOn;

	int Count_;


	void TitleText();

};

