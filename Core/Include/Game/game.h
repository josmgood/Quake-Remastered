#pragma once

/*Standard Library*/
#include <Windows.h>
#include <map>
#include <iostream>

/*Custom Library*/
#include "..\common.h"
#include "window.h"

#include "..\..\..\Container\Include\qstring.h"

namespace sys
{
	std::string workingDir					(void);
	StringVec parseCmdLine					(char** argv, UINT32 argc);
}

/*
==================================

CVAR

==================================
*/

class Game;

struct Cvar
{
	Cvar(Game* gme);
	QString name;
	QString string;
	bool archive;
	float value;
	Game* game;
};

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
	std::map<QString, Cvar> _variables;
};
