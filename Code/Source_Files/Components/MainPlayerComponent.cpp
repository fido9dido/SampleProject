// Fill out your copyright notice here.

#include "StdAfx.h"
#include "Header_Files/Components/MainPlayerComponent.h"
#include "Header_Files/Components/MovementComponent.h"
#include "Header_Files/Components/AnimationComponent.h"
#include "Header_Files/Utility/Util.h"

#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CryCore/StaticInstanceList.h>

CRY_STATIC_AUTO_REGISTER_FUNCTION(&SUtil::RegisterComponent<CMainPlayerComponent>);

Cry::DefaultComponents::CCameraComponent* CMainPlayerComponent::GetCameraComponent()
{
	return m_pCameraComponent;
}

void CMainPlayerComponent::Initialize()
{
	m_pCharacterControllerComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCharacterControllerComponent>();
	m_pInputComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CInputComponent>();
	m_pAnimationComponent = m_pEntity->GetOrCreateComponent<CAnimationComponent>();
	m_pMovementComponent = m_pEntity->GetOrCreateComponent<CMovementComponent>();

	SEntitySpawnParams spawnParams;
	if (IEntity* pEntity = gEnv->pEntitySystem->SpawnEntity(spawnParams, false))
	{
		// Create an instance of our component and attach it to the entity
		m_pCameraComponent = pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCameraComponent>();
		gEnv->pEntitySystem->InitEntity(pEntity, spawnParams);
		m_pCameraEntity = pEntity;
	}

	if (!m_pCameraEntity)																																   
	{
		CryLog("Entity class 'CTopDownCameraComponent' failed to spawn (entity name: %s)", GetEntity()->GetName());
	}

	m_pMovementComponent->SetOwner(this);
	
	if (m_pAnimationComponent)
	{
		m_pAnimationComponent->SetPlayerController(m_pCharacterControllerComponent);
	}
}

Cry::Entity::EventFlags CMainPlayerComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::GameplayStarted | Cry::Entity::EEvent::Update | Cry::Entity::EEvent::Reset;
}

void CMainPlayerComponent::ProcessEvent(const SEntityEvent& event)
{
	switch (event.event)
	{
		case Cry::Entity::EEvent::Update:
		{			  
			const float frameTime = event.fParam[0];
			OnUpdate(frameTime);
		}
		break;
		case Cry::Entity::EEvent::GameplayStarted:
		{
			OnBeginPlay();
		}
		break;
		case Cry::Entity::EEvent::Reset:
		{
			OnReset();
		}
		break;
		default:
		{
		}
	}
}

void CMainPlayerComponent::InitalizeInput()
{
	if (m_pInputComponent)
	{
		m_pInputComponent->RegisterAction("player", "moveforward", [this](int activationMode, float value) { m_pMovementComponent->HandleInputFlagChange(ECInputFlag::MoveForward, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "moveforward", eAID_KeyboardMouse, eKI_W);
		m_pInputComponent->RegisterAction("player", "movebackward", [this](int activationMode, float value) { m_pMovementComponent->HandleInputFlagChange(ECInputFlag::MoveBack, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "movebackward", eAID_KeyboardMouse, eKI_S);
		m_pInputComponent->RegisterAction("player", "moveRight", [this](int activationMode, float value) { m_pMovementComponent->HandleInputFlagChange(ECInputFlag::MoveRight, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "moveRight", eAID_KeyboardMouse, eKI_D);
		m_pInputComponent->RegisterAction("player", "moveLeft", [this](int activationMode, float value) { m_pMovementComponent->HandleInputFlagChange(ECInputFlag::MoveLeft, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "moveLeft", eAID_KeyboardMouse, eKI_A);
		m_pInputComponent->RegisterAction("player", "keyboard_sprint", [this](int activationMode, float value) { m_pMovementComponent->HandleInputFlagChange(ECInputFlag::Sprint, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "keyboard_sprint", eAID_KeyboardMouse, EKeyId::eKI_LShift);
		m_pInputComponent->RegisterAction("player", "keyboard_jump", [this](int activationMode, float value) { m_pMovementComponent->HandleInputFlagChange(ECInputFlag::Jump, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "keyboard_jump", eAID_KeyboardMouse, EKeyId::eKI_Space);
		//Camera
		m_pInputComponent->RegisterAction("player", "resetcamera", [this](int activationMode, float value) { m_pMovementComponent->ResetCameraTransform(); });
		m_pInputComponent->BindAction("player", "resetcamera", eAID_KeyboardMouse, EKeyId::eKI_Tab);
	    m_pInputComponent->RegisterAction("player", "movecamera", [this](int activationMode, float value) { m_pMovementComponent->HandleCameraInputChange(ECCameraFlag::Move, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "movecamera", eAID_KeyboardMouse, EKeyId::eKI_Mouse2);//right click
	    m_pInputComponent->RegisterAction("player", "rotatecamera", [this](int activationMode, float value) { m_pMovementComponent->HandleCameraInputChange(ECCameraFlag::Rotate, (EActionActivationMode)activationMode); });
		m_pInputComponent->BindAction("player", "rotatecamera", eAID_KeyboardMouse, EKeyId::eKI_Mouse3);//middle click
		m_pInputComponent->RegisterAction("player", "turn", [this](int activationMode, float value) { m_pMovementComponent->Turn(activationMode, -value); });
		m_pInputComponent->BindAction("player", "turn", eAID_KeyboardMouse, eKI_MouseX);  //Yaw
		m_pInputComponent->RegisterAction("player", "lookUp", [this](int activationMode, float value) { m_pMovementComponent->LookUp(activationMode, -value); });
		m_pInputComponent->BindAction("player", "lookUp", eAID_KeyboardMouse, eKI_MouseY);//Pitch
	}
}

void CMainPlayerComponent::OnBeginPlay()
{
	InitalizeInput();
	m_pMovementComponent->OnBeginPlay();
	m_pAnimationComponent->OnBeginPlay();

}

void CMainPlayerComponent::OnUpdate(float deltaTime)
{
	m_pMovementComponent->OnUpdate(deltaTime);
	m_pAnimationComponent->OnUpdate(deltaTime);
}

void CMainPlayerComponent::OnReset()
{
	m_pMovementComponent->OnReset();
	m_pAnimationComponent->OnReset();
}
