
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>

#include "Container/Include/base.hpp"
#include "Container/Include/qstack.hpp"

#include "Math/Include/math.h"
#include "Math/Include/vector.hpp"

int main()
{
	glewExperimental = GL_TRUE;
	glewInit();
	glfwInit();

	/*PoolAllocator<int> pool(100);
	Block* blocks = pool.allocate(10);
	int* nums = (int*)blocks->address;
	for (size_t i = 0; i < 10; i++)
	{
		nums[i] = (int)i * glfwGetTime();
		std::cout << (void*)nums[i] << std::endl;
	}*/


	std::cin.get();
	return 0;
}