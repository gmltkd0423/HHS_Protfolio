#pragma once
#include "GameEngineActorSubObject.h"
#include "GameEngineEnum.h"
#include <map>


// ���� : 
class GameEngineImage;
class GameEngineFolderImage;
class GameEngineRenderer : public GameEngineActorSubObject
{
	friend GameEngineActor;
	friend GameEngineLevel;

public:
	// constrcuter destructer
	GameEngineRenderer();
	~GameEngineRenderer();

	// delete Function
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;

	inline void SetTransColor(unsigned int _Color)
	{
		TransColor_ = _Color;
	}

	inline void SetPivot(const float4& _Pos)
	{
		RenderPivot_ = _Pos;
	}

	inline void SetPivotType(const RenderPivot& _Type)
	{
		PivotType_ = _Type;
	}

	inline void SetScaleMode(const RenderScaleMode& _Mode)
	{
		ScaleMode_ = _Mode;
	}

	// ������ �����ϰ� �̹��� �������� ���� ������, SetImage()���� ȣ���Ͽ� ����Ѵ�.
	void SetImageScale();

	inline void SetScale(const float4& _Scale)
	{
		ScaleMode_ = RenderScaleMode::User;
		RenderScale_ = _Scale;
	}

	inline GameEngineImage* GetImage()
	{
		return Image_;
	}

	void SetImage(const std::string& _Name);

	void SetIndex(size_t _Index, float4 _Scale = { -1.0f, -1.0f });

	void CameraEffectOff()
	{
		IsCameraEffect_ = false;
	}

	void CameraEffectOn()
	{
		IsCameraEffect_ = true;
	}

	void SetOrder(int _Order) override;

protected:
	// EngineImage�� TransCopy �� �̹����� ����ۿ� �׸���.
	void Render();

private:
	friend class FrameAnimation;

	GameEngineImage* Image_;	
	RenderPivot PivotType_;		// ���� bot ��, �̹��� ������� �߽����� ����Ұ��ΰ�
	RenderScaleMode ScaleMode_;	// ENUM(Image, User), ������ �������� �⺻������ �����ΰ�, ���α׷��Ӱ� ������ USER������ �����ΰ�.

	// ȭ�鿡�� ����� ��ǥ�� ũ��
	float4 RenderPivot_;		// �׷��� DC�� ������
	float4 RenderScale_;		// ��� ũ��� �׸����ΰ�.

	// �̹������� �߶� ��ǥ�� ũ��
	float4 RenderImagePivot_;	// ����������� �̹��� ���� ��ǥ
	float4 RenderImageScale_;	// ����������� �̹��� ��ĭ�� ũ��

	unsigned int TransColor_;	// TransParents ���� �� ������ RGB ��

	bool IsCameraEffect_;		// �ش� �������� ī�޶��� ������ �޴°� �ȹ޴°�, EX) UI �� ī�޶��� ������ �ȹ޴´�.

	//////////////////////////////////////////////////
	//// Animation
	//////////////////////////////////////////////////
private:
	class FrameAnimation : public GameEngineNameObject
	{
	public:
		GameEngineRenderer* Renderer_;
		GameEngineImage* Image_;
		GameEngineFolderImage* FolderImage_;

		int TimeKey;
		int CurrentFrame_;
		int StartFrame_;
		int EndFrame_;
		float CurrentInterTime_;
		float InterTime_;
		bool Loop_ = false;
		bool IsEnd;

	public:
		FrameAnimation()
			:	Image_(nullptr),
			CurrentFrame_(-1),
			StartFrame_(-1),
			EndFrame_(-1),
			CurrentInterTime_(0.1f),
			InterTime_(0.1f),
			Loop_(true),
			TimeKey(0)
		{
		}

	public:

		void Update();

		// ó�� ������·� ����°�.
		void Reset()
		{
			IsEnd = false;
			CurrentFrame_ = StartFrame_;
			CurrentInterTime_ = InterTime_;

		}
	};

public:
	// �ִϸ��̼��� �����.
	void CreateAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimation(const std::string& _Image, const std::string& _Name, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	void CreateFolderAnimationTimeKey(const std::string& _Image, const std::string& _Name, int _TimeScaleKey, int _StartIndex, int _EndIndex, float _InterTime, bool _Loop = true);

	// �ִϸ��̼��� ����Ѵ�.
	void ChangeAnimation(const std::string& _Name);

	bool IsEndAnimation();

	bool IsAnimationName(const std::string& _Name);

private:
	std::map<std::string, FrameAnimation> Animations_;
	FrameAnimation* CurrentAnimation_;

};
