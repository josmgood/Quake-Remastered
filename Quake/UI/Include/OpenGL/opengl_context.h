#pragma once

#include <windows.h>

#include <GL/glew.h>
#include <GL/wglew.h>

#include "../../../Container/Include\qbool.h"
#include "../../../Math\Include/vector2.hpp"

#include "../Windows/windows_defs.h"

UINT g_VAO;
UINT g_VBO;

//void initScene()
//{
//	float fVert[9];
//	fVert[0] = -5; fVert[1] = 0; fVert[2] = 0;
//	fVert[3] = 5;  fVert[4] = 0; fVert[5] = 0;
//	fVert[6] = 0;  fVert[7] = 5; fVert[8] = 0;
//
//	glGenVertexArrays(1, &g_VAO);
//	glBindVertexArray(g_VAO);
//	glGenBuffers(1, &g_VBO);
//	glBindBuffer(GL_ARRAY_BUFFER, )
//}

#define CLASS_NAME "OpenGL Class"

class OpenGLContext
{
public:
	//OpenGLContext(HINSTANCE hInstance, HWND* hwnd, int major, int minor, void (*);

	static void registerClass(HINSTANCE hInstance);
	static void unregisterClass(HINSTANCE hInstance);

	void makeCurrent();
	void swapBuffers();
private:
	QBool _initGLEW(HINSTANCE hInstance);

	void(*InitScene)(LPVOID lpParam);
	void(*RenderScene)(LPVOID lpParam);
	void(*ReleaseScene)(LPVOID lpParam);

	HDC _hdc;
	HWND* _hwnd;
	HGLRC _hrc;
	int _majorVersion;
	int _minorVersion;
	static QBool _isRegistered;
	static QBool _isInitialized;
};

LRESULT CALLBACK classHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);