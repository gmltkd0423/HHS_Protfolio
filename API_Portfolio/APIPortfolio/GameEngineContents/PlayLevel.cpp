#include "PlayLevel.h"
#include "Player.h"
#include "PlayBackGround.h"

enum class ORDER
{
	BACKGROUND,
	PLAYER,
	MONSTER,
	UI
};


PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	CreateActor<PlayBackGround>(0, "Level1");
}

void PlayLevel::Update()
{

}


void PlayLevel::LevelChangeStart()
{
	

}