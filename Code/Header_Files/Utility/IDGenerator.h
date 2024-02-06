// Fill out your copyright notice in the Description page of Project Settings.
#ifndef IDGENERATOR_H
#define IDGENERATOR_H

////////////////////////////////////////////////////////////
// Represents a template to generate a unique id per type //
////////////////////////////////////////////////////////////
template<class Type>
class CIDGenerator
{
private:

	static uint m_count;
public:

	static  uint GenerateNewID()
	{
		return  ++m_count;
	}

	static void Reset()
	{
		m_count = 0;
	}
};
template<class Type>
uint CIDGenerator<Type>::m_count = 0;


#endif