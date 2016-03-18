#include "../../Include/OpenGL/opengl_context.h"

OpenGLContext::OpenGLContext()
	: _hrc(), _hdc(), _hwnd(), _size()
{
}

OpenGLContext::OpenGLContext(Hwnd hwnd)
	: _hrc(), _hdc(), _hwnd(), _size()
{
	createContext(hwnd);
}

OpenGLContext::~OpenGLContext()
{
	wglMakeCurrent(_hdc, 0);
	wglDeleteContext(_hrc);
	ReleaseDC(_hwnd, _hdc);
}

QBool OpenGLContext::createContext(Hwnd hwnd)
{
	_hwnd = hwnd;
	_hdc = GetDC(hwnd);

	PixelFormatDescriptor pfd;
	std::memset(&pfd, 0, sizeof(PixelFormatDescriptor));

	pfd.nSize = sizeof(PixelFormatDescriptor);
	pfd.dwFlags = PFD_DOUBLEBUFFER | PFD_SUPPORT_OPENGL | PFD_DRAW_TO_WINDOW;
	pfd.iPixelType = PFD_TYPE_RGBA;
	pfd.cColorBits = 32;
	pfd.cDepthBits = 32;
	pfd.iLayerType = PFD_MAIN_PLANE;

	int pixelFormat = ChoosePixelFormat(_hdc, &pfd);
	QBool result = SetPixelFormat(_hdc, pixelFormat, &pfd);
	if (!pixelFormat || !result)
	{
		return false;
	}

	HGLRC dummyContext = wglCreateContext(_hdc);
	wglMakeCurrent(_hdc, dummyContext);
	if (glewInit() != GLEW_OK)
	{
		return false;
	}

	int attributes[] =
	{
		WGL_CONTEXT_MAJOR_VERSION_ARB, 3,
		WGL_CONTEXT_MINOR_VERSION_ARB, 2,
		WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_FORWARD_COMPATIBLE_BIT_ARB, 0
	};

	if (wglewIsSupported("WGL_ARB_create_context"))
	{
		_hrc = wglCreateContextAttribsARB(_hdc, nullptr, attributes);
		wglMakeCurrent(nullptr, nullptr);
		wglDeleteContext(dummyContext);
		wglMakeCurrent(_hdc, _hrc);
	}
	else
	{
		_hrc = dummyContext;
	}
	int glVersion[2] = { -1, 1 };
	glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]);
	glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]);
	std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
	return true;
}

void OpenGLContext::setupScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

void OpenGLContext::resizeWindow(int32 x, int32 y)
{
	_size.x = x;
	_size.y = y;
}

void OpenGLContext::resizeWindow(const math::Vector2i& size)
{
	_size.x = size.x;
	_size.y = size.y;
}

void OpenGLContext::renderScene()
{
	glViewport(0, 0, _size.x, _size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	SwapBuffers(_hdc);
}