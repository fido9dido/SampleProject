// Fill out your copyright notice here.

#ifndef CANIMATION_COMPONENT_H
#define CANIMATION_COMPONENT_H

#include <CryEntitySystem/IEntityComponent.h>
#include <DefaultComponents/Physics/CharacterControllerComponent.h>
#include <DefaultComponents/Geometry/AdvancedAnimationComponent.h>

enum class ECLocomotionState
{
	Idle
	, Jump_UP
	, Jump_Down
	, Walk
	, Count
};

////////////////////////////////////////////////////////
// Represents an Animation Component
////////////////////////////////////////////////////////
class CAnimationComponent  : public IEntityComponent
{
private:
	Cry::DefaultComponents::CAdvancedAnimationComponent* m_pAnimationComponent;
	Cry::DefaultComponents::CCharacterControllerComponent* m_pPlayerController = nullptr;

	FragmentID m_idleFragmentID;
	FragmentID m_walkFragmentID;
	FragmentID m_JumpUPFragmentID;
	FragmentID m_JumpDownFragmentID;

	IActionPtr m_idleAction = nullptr;
	
	ECLocomotionState m_locomotionState = ECLocomotionState::Idle;
	ECLocomotionState m_locomotionStateCache = ECLocomotionState::Idle;

	std::map<ECLocomotionState, IActionPtr> m_ActionMap;

public:
	CAnimationComponent() = default;
	virtual ~CAnimationComponent() = default;

	void SetPlayerController(Cry::DefaultComponents::CCharacterControllerComponent* playerController);
	bool SetFragmentID(FragmentID& fragmentID, const char* szFragmentName);
	
	//IEntityComponent
	virtual void Initialize() override;
	//~IEntityComponent

	void InitializeFragments();
	void OnReset();
	void OnBeginPlay();
	void OnUpdate(float deltaTime);

	ECLocomotionState UpdateLocomotionState();
	IActionPtr RequestNewState(ECLocomotionState state);
	
	// Reflect type to set a unique identifier for this component
	// and provide additional information to expose it in the sandbox
	static void ReflectType(Schematyc::CTypeDesc<CAnimationComponent>& desc)
	{
		desc.SetGUID("{7B8A9B9F-AC38-4446-B832-4EEDBB9B91F2}"_cry_guid);
		desc.SetEditorCategory("Player");
		desc.SetLabel("Animation Component");
		desc.SetDescription("Animation Component");
		desc.SetComponentFlags({IEntityComponent::EFlags::Socket, IEntityComponent::EFlags::Attach });
		
	}
};

#endif