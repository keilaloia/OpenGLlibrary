#include "graphics\Context.h"
#include <iostream>
int main()
{
	Context context;
	context.bInitialize();
	double x = 0;
	double y = 0;
	while (context.bUpdate())//game loop
	{
		std::cout << " Q is pushed" << context.bgetkey('Q') << std::endl;
		std::cout << "mouse button 0 was pushed" << context.bgetMouseButton(0) << std::endl;
		context.getMousePosition(x, y);

		std::cout << "X" << x << std::endl;
		std::cout << "y" << y << std::endl;
		std::cout << "time is:" << context.dgetTime() << std::endl;

	}
	context.bTerminate();
	return 0;
}

