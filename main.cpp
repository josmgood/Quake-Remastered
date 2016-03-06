
#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include <GLM\glm.hpp>

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

	/*std::cout << mem::internal::alignToPowerofTwo(50) << std::endl;*/

	/*mem::PoolAllocator<double> pool(sizeof(double) * 10);
	mem::Block block = pool.allocate(32);
	pool.owns(block);*/

	/*math::Vector3f fVec(100, 15, 400);
	math::Vector3f fVec2(400, 100, 1);
	float32 dot = fVec ^ fVec2;
	std::cout << dot << std::endl;*/

	mem::PoolAllocator<int> pool(sizeof(int) * 100);
	pool.allocate(sizeof(int) * 10);

	std::cin.get();
	return 0;
}