#pragma once

// ���� :
class PlayLevel2BackGround
{
public:
	// constrcuter destructer
	PlayLevel2BackGround();
	~PlayLevel2BackGround();

	// delete Function
	PlayLevel2BackGround(const PlayLevel2BackGround& _Other) = delete;
	PlayLevel2BackGround(PlayLevel2BackGround&& _Other) noexcept = delete;
	PlayLevel2BackGround& operator=(const PlayLevel2BackGround& _Other) = delete;
	PlayLevel2BackGround& operator=(PlayLevel2BackGround&& _Other) noexcept = delete;

protected:

private:

};

