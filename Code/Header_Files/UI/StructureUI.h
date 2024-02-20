// Fill out your copyright notice here.

#ifndef STRUCTURE_UI_H
#define STRUCTURE_UI_H

#include "Button.h"
#include <CrySystem/Scaleform/IFlashUI.h> 
#include <Header_Files/UI/ButtonWithImage.h>
#include "CrySchematyc/ResourceTypes.h"

class ResourceCost
{
public:
	int m_Count;

};
enum class ECStructureType
{
	House
	, Quarry
	, Count
};
static void ReflectType(Schematyc::CTypeDesc<ECStructureType>& desc)
{
	desc.SetGUID("{C8B4EF78-3F15-4259-8404-80B55EE45AFE}"_cry_guid);
	desc.SetLabel("StructureType");
	desc.SetDefaultValue(ECStructureType::House);
	desc.AddConstant(ECStructureType::House, "House", "House");
	desc.AddConstant(ECStructureType::Quarry, "Quarry", "Quarry");
}

struct SStructureButtonParameters
{
	Schematyc::TextureFileName m_texture;
	
	ECStructureType m_Type;
	
	SStructureButtonParameters() = default;
	
	inline bool operator==(const SStructureButtonParameters& rhs) const { return 0 == memcmp(this, &rhs, sizeof(rhs)); }


	void Serialize(Serialization::IArchive& archive)
	{
		archive(m_texture, "Texture", "Texture");
		archive.doc("Texture");
	}
	static void ReflectType(Schematyc::CTypeDesc<SStructureButtonParameters>& desc)
	{
		desc.SetGUID("{B878CBFE-8036-4CEB-8C06-1D538F4E1296}"_cry_guid);
	}
};

////////////////////////////////////////////////////////
// Represents a Structure's Button
// Work in Progress @todo
////////////////////////////////////////////////////////
class CStructureUI: public CButtonWithImage
{
private:
	SStructureButtonParameters m_StructureDescription;

public:
	CStructureUI();
	CStructureUI(string gfxName);
	~CStructureUI() = default;
	
	virtual void OnUIEvent(struct IUIElement* pSender, const SUIEventDesc& event, const SUIArguments& args) override;
	virtual void OnUIEventEx(struct IUIElement* pSender, const char* fscommand, const SUIArguments& args, void* pUserData) override;
	
	static void ReflectType(Schematyc::CTypeDesc<CStructureUI>& desc)
	{
		desc.SetGUID("{22D17C7F-A18B-4C87-A754-D9DD748CC8B8}"_cry_guid);
		desc.SetLabel("Structure UI");
	}

private:
	friend inline bool Serialize(Serialization::IArchive& archive, CStructureUI& value, const char* szName, const char* szLabel)
	{
		const bool result = archive(value.m_StructureDescription, "structuredescription", "StructureDescription");
		archive.doc("Structure Description");

		return result;
	}
};

#endif