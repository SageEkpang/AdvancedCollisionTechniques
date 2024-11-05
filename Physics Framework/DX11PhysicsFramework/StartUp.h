#pragma once
#ifndef START_UP_H
#define START_UP_H

#include "Structures.h"

// BASE SCREEN CLASS
#include "Screen.h"

// FORWARD DEC(s)
class BasicScreen;

class StartUp
{
private:

	// BASE VARIABLE(s)
	std::vector<Screen> m_Screens;

public:

	// CLASS FUNCTION(s)
	StartUp();

	~StartUp();


	// BASE FUNCTION(s)
	std::vector<Screen> GetScreenVector() { return m_Screens; }

};

#endif

