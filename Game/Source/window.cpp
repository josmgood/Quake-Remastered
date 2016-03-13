#include "..\Include\window.h"

/*
==================================

WINDOW

==================================
*/

namespace sys
{
	Window::Window(void)
		: _glfwWindow(nullptr), _title(), _size(), _isOpen(false)
	{
	}
	Window::~Window(void)
	{
		close();
	}
	bool Window::create(glm::ivec2 size, const std::string& title)
	{
		_glfwWindow = glfwCreateWindow(size.x, size.y, title.c_str(), nullptr, nullptr);
		if (_glfwWindow)
		{
			_isOpen = true;
			_size = size;
			_title = title;
			glfwMakeContextCurrent(_glfwWindow);
			return true;
		}
		else
		{
			return false;
		}
	}
	bool Window::create(int width, int height, const std::string& title)
	{
		_glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
		if (_glfwWindow)
		{
			_isOpen = true;
			_size = glm::ivec2(width, height);
			_title = title;
			glfwMakeContextCurrent(_glfwWindow);
			return true;
		}
		else
		{
			return false;
		}
	}
	void Window::close(void)
	{
		if (_glfwWindow)
		{
			_isOpen = false;
			_size = glm::ivec2();
			glfwDestroyWindow(_glfwWindow);
		}
	}
	void Window::pollEvents(void)
	{
		glfwPollEvents();
	}
	void Window::swapBuffers(void)
	{
		glfwSwapBuffers(_glfwWindow);
	}
	void Window::setTitle(const std::string& title)
	{
		_title = title;
	}
	void Window::setSize(glm::ivec2 size)
	{
		_size = size;
	}
	void Window::setWidth(int width)
	{
		_size.x = width;
	}
	void Window::setHeight(int height)
	{
		_size.y = height;
	}
	GLFWwindow* Window::getWindow(void) const
	{
		return _glfwWindow;
	}
	const std::string& Window::getTitle(void) const
	{
		return _title;
	}
	glm::vec2 Window::getSize(void) const
	{
		return _size;
	}
	int Window::getWidth(void) const
	{
		return _size.x;
	}
	int Window::getHeight(void) const
	{
		return _size.y;
	}
	bool Window::isOpen(void) const
	{
		return _isOpen;
	}
}