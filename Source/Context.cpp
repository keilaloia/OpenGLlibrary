#include "..\Include\graphics\Context.h"
#include "glinc.h"

#ifdef _DEBUG
#include <iostream>
void APIENTRY GL_errorCallback(GLenum source, GLenum type, GLuint id, GLenum severity,
	GLsizei length, const GLchar *message, const void *userParam)
{
	std::cerr << message << std::endl;
}
#endif

bool Context::bInitialize(size_t w, size_t h, const char * title)
{
	glfwInit();
	handle = glfwCreateWindow(w, h, title, 0, 0);
	glfwMakeContextCurrent(handle);

	glewExperimental = true;
	glewInit();

#ifdef _DEBUG
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);

	glDebugMessageCallback(GL_errorCallback, 0);
	glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, 0, true);
#endif

	return true;
}

bool Context::bgetkey(int key)
{
	return glfwGetKey(handle, key);
}

bool Context::bgetMouseButton(int button)
{
	return glfwGetMouseButton(handle,button);
}

void Context::getMousePosition(double & x_out, double & y_out)
{
	return glfwGetCursorPos(handle, &x_out, &y_out);
}

double Context::dgetTime()
{
	return glfwGetTime();
}

bool Context::bUpdate()
{
	glfwPollEvents();

	glfwSwapBuffers(handle);

	return !glfwWindowShouldClose(handle);
}

bool Context::bTerminate()
{
	glfwTerminate();
	handle = nullptr;
	return true;
}


