// Fill out your copyright notice in the Description page of Project Settings.
#pragma once

#include <CrySchematyc/Env/Elements/EnvComponent.h>

////////////////////////////////////////////////////////
// Represents a utility Class
////////////////////////////////////////////////////////
struct SUtil final 
{
	SUtil() = default;
	virtual ~SUtil() = default;

	/**************************
 	 * Implemented this as template to save time copying this everywhere
	 */
	template<typename TComponentType>
	static void RegisterComponent(Schematyc::IEnvRegistrar& registrar)
	{
		Schematyc::CEnvRegistrationScope scope = registrar.Scope(IEntity::GetEntityScopeGUID());
		{
			Schematyc::CEnvRegistrationScope componentScope = scope.Register(SCHEMATYC_MAKE_ENV_COMPONENT(TComponentType));
		}
	}
};
