
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <iostream>

#include "Container/Include/base.hpp"
#include "Container/Include/qstack.hpp"

#include "Math/Include/math.h"
#include "Math/Include/vector.hpp"

#include "Memory/Include/Internal/auxiliary.h"

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

	/*std::cout << mem::internal::alignToPowerofTwo(50) << std::endl;*/

	mem::PoolAllocator<double> pool(sizeof(double) * 10);
	pool.allocate(33);

	std::cin.get();
	return 0;
}