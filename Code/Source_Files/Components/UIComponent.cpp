// Fill out your copyright notice here.

#include "StdAfx.h"
#include "Header_Files/Components/UIComponent.h"
#include "Header_Files/Components/Util.h"

CRY_STATIC_AUTO_REGISTER_FUNCTION(&SUtil::RegisterComponent<CUIComponent>);
Cry::Entity::EventFlags CUIComponent::GetEventMask() const
{
	return Cry::Entity::EEvent::GameplayStarted | Cry::Entity::EEvent::Update | EEntityEvent::EditorPropertyChanged | Cry::Entity::EEvent::Reset;
}

void CUIComponent::ProcessEvent(const SEntityEvent& event)
{
	switch (event.event)
	{
		case EEntityEvent::Update:
		{
			const float frameTime = event.fParam[0];
	
		}
		break;
		case EEntityEvent::GameplayStarted:
		{		
			UpdateTextureID();
			uint32 length = m_ButtonWithTextParamsList.Size();
			if (length > 0)
			{
				for (size_t i = 0; i < length; i++)
				{
					m_pButtonWithText = std::make_unique<CButtonWithText>();
					CButtonWithText* pButtonWithText = m_pButtonWithText.get();
					pButtonWithText->SetButtonWidthAndHeight(m_width, m_height);
					pButtonWithText->SetButtonPosition(m_screenPosition.x + m_padding + (i * m_width), m_screenPosition.y);
					pButtonWithText->SetText(m_ButtonWithTextParamsList.At(i).m_text);
					pButtonWithText->SetVisible(true);
				}
			}
			length = m_ButtonWithImageParamsList.Size();
			if (uint32 length = m_ButtonWithImageParamsList.Size() > 0)
			{
				for (size_t i = 0; i < m_ButtonWithImageParamsList.Size(); i++)
				{
					m_pButtonWithImage = std::make_unique<CButtonWithImage>();
					CButtonWithImage* pButtonWithImage = m_pButtonWithImage.get();
					pButtonWithImage->SetDefaultWidthAndHeight(m_width, m_height);
					pButtonWithImage->SetButtonPosition(m_screenPosition.x, m_screenPosition.y);
					pButtonWithImage->SetTextureID(m_ButtonWithImageParamsList.At(i).m_textureID);
					pButtonWithImage->SetVisible(true);
				}
			}
		}
		break;
		case EEntityEvent::Reset:
		{
		
		}
		break;
		case  EEntityEvent::EditorPropertyChanged:
		{	  	  				 

		}
		break;
		default:
		{
		}
	}
}

void CUIComponent::UpdateTextureID()
{
	uint32 length = m_ButtonWithImageParamsList.Size();
	for (uint32 i = 0; i < length; i++)
	{
		SButtonWithImageParameters& entry = m_ButtonWithImageParamsList.At(i);
		ITexture* pTexture = gEnv->pRenderer->EF_GetTextureByName(entry.m_texture.value);
		if (!pTexture)
		{
			pTexture = gEnv->pRenderer->EF_LoadTexture(entry.m_texture.value, FT_DONT_STREAM | FT_NOMIPS);
		}
		if (pTexture)
		{
			entry.m_textureID = pTexture->GetTextureID();

		}
	}
}
