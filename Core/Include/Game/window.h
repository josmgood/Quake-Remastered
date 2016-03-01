#pragma once

/*OpenGL Libraries*/
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>

/*Standard Libraries*/
#include <string>

/*Custom Library*/
#include "..\common.h"

/*
==================================

WINDOW

==================================
*/

namespace sys
{
#define WINDOW_WIDTH	800
#define WINDOW_HEIGHT	600

	class Window
	{
	public:
		Window								(void);
		~Window								(void);

		bool create							(glm::ivec2 size, const std::string& title);
		bool create							(int width, int height, const std::string& title);
		void close							(void);

		void pollEvents						(void);
		void swapBuffers					(void);

		void setTitle						(const std::string& title);
		void setSize						(glm::ivec2 size);
		void setWidth						(int width);
		void setHeight						(int height);

		GLFWwindow* getWindow				(void) const;
		const std::string& getTitle			(void) const;
		glm::vec2 getSize					(void) const;
		int getWidth						(void) const;
		int getHeight						(void) const;
		bool isOpen							(void) const;
	private:
		GLFWwindow*				_glfwWindow;
		std::string				_title;
		glm::ivec2				_size;
		bool					_isOpen;
	};
}