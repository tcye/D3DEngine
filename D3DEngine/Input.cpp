#include "stdafx.h"
#include "Input.h"

bool Input::Init()
{
	int i;

	for (i = 0; i < 256; i++)
	{
		m_keys[i] = false;
	}

	return true;
}

void Input::Cleanup()
{

}


void Input::KeyDown(unsigned int input)
{
	m_keys[input] = true;
}


void Input::KeyUp(unsigned int input)
{
	m_keys[input] = false;
}


bool Input::IsKeyDown(unsigned int key)
{
	return m_keys[key];
}