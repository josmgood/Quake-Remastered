#include "..\..\Include\Game\game.h"

namespace sys
{
	/*std::string workingDir(void)
	{
		char dir[1024] = "";
		GetCurrentDirectory(sizeof(dir), dir);
		return std::string(dir);
	}*/
	StringVec parseCmdLine(char** argv, UINT32 argc)
	{
		StringVec vec = StringVec();
		for (UINT32 i = 1; i < argc; i++)
		{
			vec.push_back(argv[i]);
		}
		return vec;
	}
}

/*
==================================

CVAR

==================================
*/
Cvar::Cvar(Game* gme)
	: game(gme)
{
}

/*
==================================

Game

==================================
*/

Game::Game(const StringVec& argv)
	: _argv(argv), _window()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLFW_VERSION_MAJOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	_window.create(WINDOW_WIDTH, WINDOW_HEIGHT, "Quake 1.0");
}

void Game::init(void)
{
	double newTime = 0.0f;
	double oldTime = 0.0f;
	double deltaTime = 0.0f;
	while (_window.isOpen())
	{
		newTime = glfwGetTime();
		deltaTime = newTime - oldTime;
		oldTime = newTime;
	}
}