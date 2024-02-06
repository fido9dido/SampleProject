// Fill out your copyright notice in the Description page of Project Settings.

#include "StdAfx.h"
#include "Header_Files/Components/MainPlayerComponent.h"
#include "Header_Files/Components/MovementComponent.h"
#include "Header_Files/Utility/Util.h"
#include "Header_Files/Utility/IDGenerator.h"
#include "GamePlugin.h"

#include <CrySchematyc/Env/IEnvRegistrar.h>
#include <CryCore/StaticInstanceList.h>

CRY_STATIC_AUTO_REGISTER_FUNCTION(&SUtil::RegisterComponent<CMainPlayerComponent>);

void CMainPlayerComponent::Initialize()
{
	m_pCharacterControllerComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCharacterControllerComponent>();
	m_pInputComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CInputComponent>();
	m_pCameraComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CCameraComponent>();
	m_pAdvancedAnimationComponent = m_pEntity->GetOrCreateComponent<Cry::DefaultComponents::CAdvancedAnimationComponent>();
	m_pMovementComponent = m_pEntity->GetOrCreateComponent<CMovementComponent>();
	m_pMovementComponent->SetOwner(this);
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
}

void CMainPlayerComponent::OnUpdate(float deltaTime)
{
	m_pMovementComponent->Update(deltaTime);
}

void CMainPlayerComponent::OnReset()
{
	m_pMovementComponent->Reset();
}
