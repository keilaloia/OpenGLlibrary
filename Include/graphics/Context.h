#pragma once
#pragma once

struct GLFWwindow;

class Context
{
private:
	GLFWwindow *handle;

public:
	bool bInitialize(size_t width = 800, size_t height = 600, const char *title = "Graphics");

	bool bgetkey(int key);

	bool bgetMouseButton(int button);
	void getMousePosition(double &x_out, double &y_out);
	double dgetTime();
	bool bUpdate();

	bool bTerminate();

};


