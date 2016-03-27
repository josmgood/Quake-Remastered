
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>

#include <iostream>
#include <limits>
#include <functional>
#include <iomanip>

#include "Container/Include/base.hpp"
#include "Container/Include/qstack.hpp"
#include "Container/Include/qarray.hpp"
#include "Container/Include/qforward_list.hpp"
#include "Container/Include/qstring.h"

#include "Container/Include/iterator.hpp"

#include "Math/Include/math.h"
#include "Math/Include/vector2.hpp"

#include "Memory/Include/Allocator/pool_allocator.hpp"

#include "Auxiliary/Include/string_aux.h"
#include "Auxiliary/Include/algorithm.h"

#include "UI/Include/OpenGL/opengl_context.h"

#include <GTest\gtest.h>

#define GTEST

int main()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glfwInit();

#ifdef GTEST
	::testing::InitGoogleTest(&__argc, __argv);
	return RUN_ALL_TESTS() | std::cin.get();
#endif

	/*char* A = "Hello ";
	char* B = "World!";
	char* together = "Hello World!";
	char* cated = new char[12];
	Q_strCpy(A, cated);
	Q_strCat(B, cated);*/

	//char* cated = Q_strCat(A, B);
	//std::cout << cated << std::endl;
	//std::cout << Q_strCmp(together, cated) << std::endl;

	std::cout << Q_strCmp("Hello", "Hello") << std::endl;

	std::cin.get();
	return 0;
}