// Fill out your copyright notice here.

#ifndef MAIN_PLAYER_COMPONENT_H
#define MAIN_PLAYER_COMPONENT_H

#include <CryEntitySystem/IEntityComponent.h>
#include <DefaultComponents/Physics/CharacterControllerComponent.h>
#include <DefaultComponents/Physics/RigidBodyComponent.h>
#include <DefaultComponents/Cameras/CameraComponent.h>
#include <DefaultComponents/Input/InputComponent.h>

////////////////////////////////////////////////////////
// Represents the main player
////////////////////////////////////////////////////////
class CMainPlayerComponent final : public IEntityComponent
{

private:
	Cry::DefaultComponents::CCharacterControllerComponent* m_pCharacterControllerComponent = nullptr;
	Cry::DefaultComponents::CInputComponent* m_pInputComponent = nullptr;
	Cry::DefaultComponents::CCameraComponent* m_pCameraComponent = nullptr;
	class CAnimationComponent* m_pAnimationComponent = nullptr;
	class CMovementComponent* m_pMovementComponent = nullptr;
	
public:
	IEntity* m_pCameraEntity = nullptr;

	CMainPlayerComponent() = default;
	virtual ~CMainPlayerComponent() = default;
	
	Cry::DefaultComponents::CCharacterControllerComponent* GetCharacterController() { return m_pCharacterControllerComponent; }
	Cry::DefaultComponents::CCameraComponent* GetCameraComponent();

	//IEntityComponent
	virtual void Initialize() override;
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event);
	//~IEntityComponent

	void InitalizeInput();
	void OnBeginPlay();
	void OnUpdate(float deltaTime);
	void OnReset();
	
	// Reflect type to set a unique identifier for this component
	static void ReflectType(Schematyc::CTypeDesc<CMainPlayerComponent>& desc)
	{
		desc.SetGUID("{DEC4E907-9FFD-4A89-9364-910A4994DDBD}"_cry_guid);
		desc.SetEditorCategory("Player");
		desc.SetLabel("MainPlayer Component");
	}
};

#endif