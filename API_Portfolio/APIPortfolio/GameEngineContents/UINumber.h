#pragma once
#include<GameEngine/GameEngineActor.h>

// Ό³Έν :
class UINumber	:public GameEngineActor
{
public:
	// constrcuter destructer
	UINumber();
	~UINumber();

	// delete Function
	UINumber(const UINumber& _Other) = delete;
	UINumber(UINumber&& _Other) noexcept = delete;
	UINumber& operator=(const UINumber& _Other) = delete;
	UINumber& operator=(UINumber&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update() override;
	void Render() override;
private:
	GameEngineRenderer* Number[3];
	GameEngineRenderer* Number2[2];
	GameEngineRenderer* Number3;

	int value_;

	 
public:
	void SetValue(int _value)
	{
		value_ = _value;
	}
};

