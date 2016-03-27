#pragma once

/*Standard Library*/
#include <Windows.h>
#include <map>
#include <iostream>

/*Custom Library*/
#include "..\..\common.h"
#include "window.h"

/*
==================================

Game

==================================
*/

class Game
{
public:
	Game			(const StringVec& argv);
	void init		(void);

	//void registerVariable(Cvar variable);
private:
	StringVec		_argv;
	sys::Window		_window;
};
