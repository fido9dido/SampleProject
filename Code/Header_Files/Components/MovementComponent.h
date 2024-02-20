// Fill out your copyright notice here.

#ifndef MOVEMENT_COMPONENT_H
#define MOVEMENT_COMPONENT_H

#include <CryEntitySystem/IEntityComponent.h>
#include <CrySchematyc/Utils/EnumFlags.h>
#include <ICryMannequin.h>

////////////////////////////////////////////////////////
// Represents a Movement Component
////////////////////////////////////////////////////////

enum class ECInputFlag : uint8
{
	MoveLeft	= 1 << 0,
	MoveRight	= 1 << 1,
	MoveForward = 1 << 2,
	MoveBack	= 1 << 3,
	Sprint		= 1 << 4,
	Jump		= 1 << 5,
	
};	 
enum class ECCameraFlag : uint8
{
	Rotate	= 1 << 0, //with middle click
	Move	= 1 << 1, //with right click
	Zoom	= 1 << 2 //with scroll (@todo)
};	

enum class ECInputFlagType
{
	Hold = 0
	, Toggle
};

class CMovementComponent : public IEntityComponent
{
private:
	class CMainPlayerComponent* m_pOwner = nullptr;
	CEnumFlags<ECInputFlag> m_inputFlags ;
	CEnumFlags<ECCameraFlag> m_cameraflags ;

	//Camera
	Matrix33 m_cameraRotation = ZERO;
	Matrix33 m_pitchRotation = ZERO;
	Matrix33 m_yawRotation = ZERO;
	Vec2 m_mouseDelta = ZERO;

	//local space
	Vec3 m_cameraDefaultPosition = Vec3(0.f, -2.f, 1.f);
	Vec3 m_cameraDefaultAngle = Vec3(0.f, -0.2f, 0.f);
	Vec3 m_cameraLocalPosition = ZERO;

	//world  space
	Matrix34 m_cameraWorldMatrix = ZERO;
	Vec3 m_cameraWorldPosition = ZERO;
	
	//player 
	Quat m_playerRotation = Quat(0.f, 0.f, 0.f, 0.f);
	Vec3 m_jumpVelocity = Vec3(0, 0, 10.f);
	Vec3 m_velocity = ZERO;

	float m_minYawRotation = -1.f;
	float m_maxYawRotation = 1.f;
	float m_cameraSpeed = 10.f;
	float m_airSpeed = 10.f;
	float m_sprintSpeed = 40.f;
	float m_moveSpeed = 40.f;
	float m_rotationSpeed = .002f;

public:
	CMovementComponent() = default;
	virtual ~CMovementComponent() = default;

	const Vec3& GetCameraPosition() const { return m_cameraLocalPosition; };
	const Matrix33& GetCameraRotation() const { return m_cameraRotation; };
	const Vec3& GetVelocity() const { return m_velocity; };
	const Vec3& GetJumpVelocity() const { return m_jumpVelocity; };

	void SetOwner(class CMainPlayerComponent* playerComponent);
	void OnReset();
	//Reset Camera transform to the default
	void ResetCameraTransform();
	void OnBeginPlay();
	void OnUpdate(float deltaTime);
	void UpdateCharacterMovement(float frameTime);

	void SyncCameraWithPlayer();
	
	// reset velocity before passing it unless you want that effect
	void CalculateVelocity(Vec3& velocity, float moveSpeed, float deltaTime);
	void HandleInputFlagChange(const CEnumFlags<ECInputFlag> flags, const CEnumFlags<EActionActivationMode> activationMode, ECInputFlagType type = ECInputFlagType::Hold);

	// Camera
	void HandleCameraInputChange(const CEnumFlags<ECCameraFlag> flags, const CEnumFlags<EActionActivationMode> activationMode, ECInputFlagType type = ECInputFlagType::Hold);
	void UpdateCameraMovement(float deltaTime);
	void UpdateCameraRotation(float deltaTime);
	void UpdateLookAt(const Ang3& cameraRotation);
	void UpdateTurn(const Ang3& rotation);
	void SetCameraTransform(const Vec3& localTranslation, const Matrix33& LocalRotation);

	void Turn(int activationMode, float value);
	void LookUp(int activationMode, float value);
	// ~Camera

	static void ReflectType(Schematyc::CTypeDesc<CMovementComponent>& desc)
	{
		desc.SetGUID("{DBFFD540-BE47-4927-ABAD-2DD358FCD810}"_cry_guid);
		desc.SetEditorCategory("Player");
		desc.SetLabel("Movement Component");
		desc.SetDescription("Represent Settings for the Movement Components");
		//desc.SetIcon("icons:General/*.ico");
		desc.SetComponentFlags({ IEntityComponent::EFlags::Transform, IEntityComponent::EFlags::Socket, IEntityComponent::EFlags::Attach, IEntityComponent::EFlags::ClientOnly });

		desc.AddMember(&CMovementComponent::m_rotationSpeed, 'rspd', "rotationspeed", "Rotation Speed", "Set Rotation Speed", .002f);
		desc.AddMember(&CMovementComponent::m_cameraDefaultPosition, 'cpos', "cameradefaultposition", "Camera Default Position", "Set Initial Camera Position", ZERO);
		desc.AddMember(&CMovementComponent::m_cameraDefaultAngle, 'cang', "cameradefaultangle", "Camera Default Angle", "Set Default Camera Angle", Vec3(0.f, 0.f, 0.f));
		desc.AddMember(&CMovementComponent::m_moveSpeed, 'mspd', "movementspeed", "Movement Speed", "Set Movement Speed", 2.f);
		desc.AddMember(&CMovementComponent::m_minYawRotation, 'miny', "minyawrotation", "Min Yaw Rotation", "Set Minimum Yaw Rotation", -1.f);
		desc.AddMember(&CMovementComponent::m_maxYawRotation, 'mxny', "maxyawrotation", "Max Yaw Rotation", "Set Maximum Yaw Rotation", 1.f);
		desc.AddMember(&CMovementComponent::m_jumpVelocity, 'jvel', "jumpvelocity", "Jump Velocity", "Set Jump velocity vector", false);
	}
};

#endif