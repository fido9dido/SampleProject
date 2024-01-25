// Copyright 2017-2019 Crytek GmbH / Crytek Group. All rights reserved.
#include "StdAfx.h"
#include "Header_Files/Components/UIComponent.h"
#include "Header_Files/Components/Util.h"

CRY_STATIC_AUTO_REGISTER_FUNCTION(&SUtil::RegisterComponent<CUIComponent>);
Cry::Entity::EventFlags CUIComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::GameplayStarted | Cry::Entity::EEvent::Update | Cry::Entity::EEvent::Reset;
}

void CUIComponent::ProcessEvent(const SEntityEvent& event)
{
	switch (event.event)
	{
		case Cry::Entity::EEvent::Update:
		{
			const float frameTime = event.fParam[0];
	
		}
		break;
		case Cry::Entity::EEvent::GameplayStarted:
		{
			m_pButtonWithText = std::make_unique<CButtonWithText>();
			m_pButtonWithText->SetWidth(300);
			m_pButtonWithText->SetHeight(100);
			m_pButtonWithText->SetText(m_buttonText.c_str());
		
			m_pButtonWithText->SetVisible(true);
		}
		break;
		case Cry::Entity::EEvent::Reset:
		{
		
		}
		break;
		default:
		{
		}
	}
}