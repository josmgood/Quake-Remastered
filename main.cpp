
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>

#include <iostream>

#include "Container/Include/base.hpp"
#include "Container/Include/qstack.hpp"
#include "Container/Include/qarray.hpp"
#include "Container/Include/qforward_list.hpp"
#include "Container/Include/qstring.hpp"

#include "Math/Include/math.h"
#include "Math/Include/vector2.hpp"

#include "Memory/Include/Allocator/pool_allocator.hpp"

#include "Auxiliary/Include/string_aux.h"

int main()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glfwInit();

	char* str = "hello";
	char* dest = new char[qStrLen(str)];
	qStrCpy(str, dest, 3);
	qStrPrint(dest);
	
	std::cin.get();
	return 0;
}