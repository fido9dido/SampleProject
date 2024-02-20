// Fill out your copyright notice here.

#ifndef UI_COMPONENT_H
#define UI_COMPONENT_H

#include <CryEntitySystem/IEntitySystem.h>
#include <CrySchematyc/Utils/Array.h>
#include "CrySerialization/SerializationUtils.h"

struct SButtonWithTextParameters
{
	string m_text;

	SButtonWithTextParameters() = default;
	inline bool operator==(const SButtonWithTextParameters& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SButtonWithTextParameters& rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	void Serialize(Serialization::IArchive& archive)
	{
		archive(m_text, "text", "Text");
		archive.doc("Text");		
	
	}
	static void ReflectType(Schematyc::CTypeDesc<SButtonWithTextParameters>& desc)
	{
		desc.SetGUID("{DB5A596E-A760-44D6-BB3D-CFAF75037A82}"_cry_guid);
	}
};

struct SButtonWithImageParameters
{
	int m_textureID;
	Schematyc::TextureFileName m_texture;
	SButtonWithImageParameters() = default;
	inline bool operator==(const SButtonWithImageParameters& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }
	inline bool operator!=(const SButtonWithImageParameters& rhs) const { return 0 != memcmp(this, &rhs, sizeof(rhs)); }

	void Serialize(Serialization::IArchive& archive)
	{
		archive(m_texture, "texture", "Texture");
		archive.doc("Texture");
	}

	static void ReflectType(Schematyc::CTypeDesc<SButtonWithImageParameters>& desc)
	{
		desc.SetGUID("{66C5F08A-A122-471D-A737-D9396EE0B3FF}"_cry_guid);
	}
};
enum class ECAlignment
{
	Vertical,
	Horizontal
};

static void ReflectType(Schematyc::CTypeDesc<ECAlignment>& desc)
{
	desc.SetGUID("{32C14C12-E48F-4E35-A570-2A6AD43F8718}"_cry_guid);
	desc.SetLabel("ButtonAlignment");
	desc.SetDefaultValue(ECAlignment::Vertical);
	desc.AddConstant(ECAlignment::Vertical, "Vertical", "Vertical");
	desc.AddConstant(ECAlignment::Horizontal, "Horizontal", "Horizontal");
}

////////////////////////////////////////////////////////
// Represents a UI Component
// For now I am using this class to test whether buttons works
////////////////////////////////////////////////////////
class CUIComponent final : public IEntityComponent
{
public:
	
	CUIComponent(const CUIComponent& other)
		: m_ButtonWithTextParamsList(std::move(other.m_ButtonWithTextParamsList))
		, m_ButtonWithImageParamsList(std::move(other.m_ButtonWithImageParamsList))
	{
		CRY_ASSERT_MESSAGE(false, "Check the callstack to find out who is triggering this");
		m_screenPosition = other.m_screenPosition;
		m_width = other.m_width;
		m_height = other.m_height;
		m_alignment = other.m_alignment;				   
		m_padding = other.m_padding;
	}
	CUIComponent& operator =(const CUIComponent& other)
	{
		CRY_ASSERT_MESSAGE(false, "Check the callstack to find out who is triggering this");
		while (m_ButtonWithTextParamsList.Size() != 0)
		{
			m_ButtonWithTextParamsList.PopBack();
		}	

		while (m_ButtonWithImageParamsList.Size() != 0)
		{
			m_ButtonWithImageParamsList.PopBack();
		}

		m_ButtonWithTextParamsList = Schematyc::CArray<SButtonWithTextParameters>(other.m_ButtonWithTextParamsList);
		m_ButtonWithImageParamsList = Schematyc::CArray<SButtonWithImageParameters>(other.m_ButtonWithImageParamsList);

		m_screenPosition = other.m_screenPosition;
		m_width = other.m_width;
		m_height = other.m_height;
		m_alignment = other.m_alignment;
		m_padding = other.m_padding;
		return *this;
	}
	std::vector<std::unique_ptr<class CButtonWithText>> m_pButtonWithText;
	std::vector<std::unique_ptr<class CButtonWithImage>> m_pButtonWithImage;
	
	Schematyc::CArray<SButtonWithTextParameters> m_ButtonWithTextParamsList;
	Schematyc::CArray<SButtonWithImageParameters> m_ButtonWithImageParamsList;

	// to help position buttons for testing
	Vec2 m_screenPosition = ZERO;
	int m_width;
	int m_height;
	ECAlignment m_alignment;
	float m_padding;
public:
	CUIComponent() = default;
	virtual ~CUIComponent() = default;
	
	//IEntityComponent
	virtual Cry::Entity::EventFlags GetEventMask() const override;
	virtual void ProcessEvent(const SEntityEvent& event);
	void UpdateTextureID();
	//~IEntityComponent
	 
	// Reflect type to set a unique identifier for this component
	// and provide additional information to expose it in the sandbox
	static void ReflectType(Schematyc::CTypeDesc<CUIComponent>& desc)
	{
		desc.SetGUID("{0D382720-1C0C-49DE-BDFA-C5AEF492FDDF}"_cry_guid);
		desc.SetEditorCategory("UI");
		desc.SetLabel("UIComponent");
		desc.SetDescription("UI Component to Display Buttons");
		desc.SetComponentFlags({IEntityComponent::EFlags::Socket, IEntityComponent::EFlags::Attach });
		desc.AddMember(&CUIComponent::m_screenPosition, 'bsp', "buttonscreenPosition", "Button Screen Position", "Set Button Screen Position", ZERO);
		desc.AddMember(&CUIComponent::m_ButtonWithTextParamsList, 'bwtp', "buttonwithtextparams", "Button + Text Params", "Create only one for now", Schematyc::CArray<SButtonWithTextParameters>());
		desc.AddMember(&CUIComponent::m_ButtonWithImageParamsList, 'bwip', "buttonwithimageparams", "Button + Image Params", "Create only one for now", Schematyc::CArray<SButtonWithImageParameters>());
		desc.AddMember(&CUIComponent::m_alignment, 'btna', "buttonalignment", "Button Alignment", "Set Button Alignment", ECAlignment::Vertical);
		desc.AddMember(&CUIComponent::m_padding, 'btnp', "buttonpadding", "Button Padding", "Set Padding", 0);
		desc.AddMember(&CUIComponent::m_width, 'btnw', "buttonwidth", "Button Width", "Set Button Width", ZERO);
		desc.AddMember(&CUIComponent::m_height, 'btnh', "buttonheight", "Button Height", "Set Button Height", ZERO);
	}

};

#endif