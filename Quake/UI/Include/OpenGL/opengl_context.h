#pragma once

#include <windows.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include "../../../Container/Include\qbool.h"
#include "../../../Math\Include/vector2.hpp"

#include "../Windows/windows_defs.h"

class OpenGLContext
{
public:
	OpenGLContext();
	OpenGLContext(Hwnd hwnd);
	~OpenGLContext();

	QBool createContext(Hwnd hwnd);
	void setupScene();
	void resizeWindow(int32 x, int32 y);
	void resizeWindow(const math::Vector2i& size);
	void renderScene();
private:
	HGLRC _hrc;
	HDC _hdc;
	Hwnd _hwnd;
	math::Vector2i _size;
};