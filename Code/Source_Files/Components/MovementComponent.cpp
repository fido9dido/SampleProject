// Fill out your copyright notice in the Description page of Project Settings.

#include "StdAfx.h"
#include "Header_Files/Components/MovementComponent.h"
#include "Header_Files/Utility/Util.h"

CRY_STATIC_AUTO_REGISTER_FUNCTION(&SUtil::RegisterComponent<CMovementComponent>);

void CMovementComponent::SetOwner(CMainPlayerComponent* playerComponent)
{
	m_pOwner = playerComponent;
}

void CMovementComponent::Reset()
{
	m_mouseDelta.zero();
	ResetCameraTransform();
}

void CMovementComponent::ResetCameraTransform()
{
	m_cameraPosition = m_cameraDefaultPosition;
	m_cameraRotation = Quat(CCamera::CreateOrientationYPR(m_cameraDefaultAngle));
	SetCameraTransform(m_cameraDefaultPosition, m_cameraRotation);
}

void CMovementComponent::Update(float deltaTime)
{
	if (m_cameraflags & ECCameraFlag::Rotate)
	{
		UpdateCameraRotation(deltaTime);
	}

	if (m_inputFlags)
	{
		if (m_cameraflags & ECCameraFlag::Move)
		{
			UpdateCameraMovement(deltaTime);
		}
		else
		{
			UpdateCharacterMovement(deltaTime);
		}
	}
}

void CMovementComponent::UpdateCharacterMovement(float deltaTime)
{
	float moveSpeed = m_moveSpeed;
	bool bOnGround = m_pOwner->GetCharacterController()->IsOnGround();

	//unfortuantely you can't sprint on air
	if (!bOnGround)
	{
		moveSpeed = m_airSpeed;
	}
	else if (m_inputFlags & ECInputFlag::Sprint)
	{
		moveSpeed = m_sprintSpeed;
	}	

	if (m_inputFlags & ECInputFlag::Jump && bOnGround)
	{
		Vec3 jumpVelocity = Vec3(0, 0, 10.f);
		m_pOwner->GetCharacterController()->ChangeVelocity(jumpVelocity, Cry::DefaultComponents::CCharacterControllerComponent::EChangeVelocityMode::Jump);
	}

	CalculateVelocity(m_velocity = ZERO, moveSpeed, deltaTime);

	Quat playerRotation(m_pOwner->GetCameraComponent()->GetWorldTransformMatrix());
	m_pOwner->GetCharacterController()->AddVelocity(playerRotation * m_velocity);
}

void CMovementComponent::CalculateVelocity(Vec3& velocity, float moveSpeed, float deltaTime)
{
	if (m_inputFlags & ECInputFlag::MoveLeft)
	{
		velocity.x -= moveSpeed * deltaTime;
	}
	if (m_inputFlags & ECInputFlag::MoveRight)
	{
		velocity.x += moveSpeed * deltaTime;
	}
	if (m_inputFlags & ECInputFlag::MoveForward)
	{
		velocity.y += moveSpeed * deltaTime;
	}
	if (m_inputFlags & ECInputFlag::MoveBack)
	{
		velocity.y -= moveSpeed * deltaTime;
	}  
}

void CMovementComponent::UpdateCameraMovement(float deltaTime)
{
	Vec3 velocity = ZERO;
	CalculateVelocity(velocity, m_cameraSpeed, deltaTime);
	
	m_cameraPosition += m_pitchRotation * velocity;
	SetCameraTransform(m_cameraPosition, Quat(m_pitchRotation));
}

void CMovementComponent::UpdateCameraRotation(float deltaTime)
{
	Ang3 rotationAngle = CCamera::CreateAnglesYPR(Matrix33(m_cameraRotation));
	rotationAngle.y = crymath::clamp<f32>(rotationAngle.y += m_mouseDelta.y * m_rotationSpeed, m_minYawRotation, m_maxYawRotation);
	rotationAngle.x += m_mouseDelta.x * m_rotationSpeed;
	rotationAngle.z = 0;
	UpdateTurn(rotationAngle);
	UpdateLookAt(rotationAngle);
	m_cameraRotation = Quat(CCamera::CreateOrientationYPR(rotationAngle));
}

void CMovementComponent::UpdateLookAt(const Ang3& cameraRotation)
{
	Ang3 pitchAngle = cameraRotation;
	pitchAngle.x = 0;
	pitchAngle.z = 0;
	m_pitchRotation = Quat(CCamera::CreateOrientationYPR(pitchAngle));
	SetCameraTransform(m_cameraPosition, m_pitchRotation);
}

void CMovementComponent::UpdateTurn(const Ang3& cameraRotation)
{
	Ang3 yawAngle = cameraRotation;
	yawAngle.y = 0;
	yawAngle.z = 0;
	m_yawRotation = Quat(CCamera::CreateOrientationYPR(yawAngle));
	m_pOwner->GetEntity()->SetRotation(Quat(m_yawRotation));
}

void CMovementComponent::SetCameraTransform(const Vec3& localTranslation, const Quat& LocalRotation)
{
	Matrix34 newTransform;
	newTransform.SetTranslation(localTranslation);
	newTransform.SetRotation33(Matrix33(LocalRotation));
	m_pOwner->GetCameraComponent()->SetTransformMatrix(newTransform);
}	   

void CMovementComponent::Turn(int activationMode, float value)
{
	m_mouseDelta.x = value;
}

void CMovementComponent::LookUp(int activationMode, float value)
{
	m_mouseDelta.y = value;
}

void CMovementComponent::HandleInputFlagChange(const CEnumFlags<ECInputFlag> flags, const CEnumFlags<EActionActivationMode> activationMode, ECInputFlagType type)
{
	switch (type)
	{
	case ECInputFlagType::Hold:
	{
		if (activationMode == eAAM_OnRelease)
		{
			m_inputFlags &= ~flags;
		}
		else
		{
			m_inputFlags |= flags;
		}
	}
	break;
	case ECInputFlagType::Toggle:
	{
		if (activationMode == eAAM_OnRelease)
		{
			// Toggle the bit(s)
			m_inputFlags ^= flags;
		}
	}
	break;

	}
}

void CMovementComponent::HandleCameraInputChange(const CEnumFlags<ECCameraFlag> flags, const CEnumFlags<EActionActivationMode> activationMode, ECInputFlagType type)
{
	switch (type)
	{
	case ECInputFlagType::Hold:
	{
		if (activationMode == eAAM_OnRelease)
		{
			m_cameraflags &= ~flags;
		}
		else
		{
			m_cameraflags |= flags;
		}
	}
	break;
	case ECInputFlagType::Toggle:
	{
		if (activationMode == eAAM_OnRelease)
		{
			// Toggle the bit(s)
			m_cameraflags ^= flags;
		}
	}
	break;

	}
}