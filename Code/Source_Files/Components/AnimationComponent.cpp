// Fill out your copyright notice here.
 
#include "Header_Files/Components/AnimationComponent.h"
#include "Header_Files/Utility/Util.h"
#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CryCore/StaticInstanceList.h>

CRY_STATIC_AUTO_REGISTER_FUNCTION(&SUtil::RegisterComponent<CAnimationComponent>);

void CAnimationComponent::SetPlayerController(Cry::DefaultComponents::CCharacterControllerComponent* playerController)
{
	m_pPlayerController = playerController;
}

bool CAnimationComponent::SetFragmentID(FragmentID& fragmentID, const char* szFragmentName)
{
	if (!szFragmentName) { return false; }
	fragmentID = m_pAnimationComponent->GetFragmentId(szFragmentName);

	if (fragmentID == FRAGMENT_ID_INVALID)
	{
		CryWarning(VALIDATOR_MODULE_GAME, VALIDATOR_ERROR, "Failed to find Mannequin fragment %s in controller definition", szFragmentName);
		return false;
	}
	return true;
}

void CAnimationComponent::Initialize()
{
	m_pAnimationComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CAdvancedAnimationComponent>();
	InitializeFragments();
}

void CAnimationComponent::InitializeFragments()
{
	if (!m_idleAction && SetFragmentID(m_idleFragmentID, "Idle"))
	{
		m_idleAction = RequestNewState(ECLocomotionState::Idle);
		m_pAnimationComponent->QueueCustomFragment(*m_idleAction);
	}

	if (SetFragmentID(m_walkFragmentID, "Walk"))
	{
		m_ActionMap[ECLocomotionState::Walk] = RequestNewState(ECLocomotionState::Walk);
	}

	if (SetFragmentID(m_JumpUPFragmentID, "Jump_UP"))
	{
		m_ActionMap[ECLocomotionState::Jump_UP] = RequestNewState(ECLocomotionState::Jump_UP);
	}

	if (SetFragmentID(m_JumpDownFragmentID, "Jump_Down"))
	{
		m_ActionMap[ECLocomotionState::Jump_Down] = RequestNewState(ECLocomotionState::Jump_Down);
	}
}

void CAnimationComponent::OnReset()
{
	for (const std::pair<ECLocomotionState, IActionPtr>& entry : m_ActionMap)
	{
		if (IActionPtr action= entry.second)
		{
			action->Stop();
		}
	}
}

void CAnimationComponent::OnBeginPlay()
{
	InitializeFragments();
}

void CAnimationComponent::OnUpdate(float deltaTime)
{

	m_locomotionState = UpdateLocomotionState();

	if (m_locomotionStateCache != m_locomotionState)
	{
		if (m_locomotionStateCache != ECLocomotionState::Idle)
		{			
			m_ActionMap[m_locomotionStateCache]->Stop();
			
		}
		if (m_locomotionState != ECLocomotionState::Idle)
		{
			m_ActionMap[m_locomotionState] = RequestNewState(m_locomotionState);
			m_pAnimationComponent->QueueCustomFragment(*m_ActionMap[m_locomotionState]);
			//m_pAnimationComponent->GetActionController()->Requeue(*m_ActionMap[m_locomotionState]);
		}
	}
	m_locomotionStateCache = m_locomotionState;
}

ECLocomotionState CAnimationComponent::UpdateLocomotionState()
{
	const bool bOnGround = m_pPlayerController->IsOnGround();
	const bool bWalking = m_pPlayerController->IsWalking();
	if (!bOnGround)
	{
		return ECLocomotionState::Jump_UP;
	}

	if (m_locomotionStateCache == ECLocomotionState::Jump_UP)
	{
		return ECLocomotionState::Jump_Down;
	}

	if (bWalking)
	{
		return ECLocomotionState::Walk;
	}
	else
	{
		return ECLocomotionState::Idle;
	}
}

IActionPtr CAnimationComponent::RequestNewState(ECLocomotionState state)
{
	switch (state)
	{
		case ECLocomotionState::Walk:
		{
			return new TAction<SAnimationContext>(20U, m_walkFragmentID);
		}
		break;
		case ECLocomotionState::Jump_UP:
		{										 
			return new TAction<SAnimationContext>(30U, m_JumpUPFragmentID);;
		}
		break;
		case ECLocomotionState::Jump_Down:
		{
			return new TAction<SAnimationContext>(10U, m_JumpDownFragmentID);
		}
		break;
		default:
		{
			return new TAction<SAnimationContext>(0U, m_idleFragmentID, TAG_STATE_EMPTY, IAction::EFlags::Interruptable);
		}
	}
}
