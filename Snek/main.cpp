#include "Header.h"

static void keyCallback(GLFWwindow *window, int button, int scancode, int action, int mods);


class game

{

private:

	int framesPassed = 0;

public:

	int windowSize;
	int width;
	int height;
	int gameOver;
	int pause;

	grid mapGrid;
	snek snekky;
	snekfood snekfd;


	void init(int windowSize_)

	{

		windowSize = windowSize_;
		mapGrid.init(20, 20);
		snekfd.init(&mapGrid, 4, 15);
		snekky.init(&mapGrid, &snekfd, 4, 10, 10, 1);
		gameOver = 0;
		pause = 1;
		framesPassed = 0;
		std::cout << "\nYou started a new game! Spacebar to unpause it!" << std::endl;


	}
	
	void update()

	{



		if (framesPassed < 7)

		{

			framesPassed++;
			return;

		}

		if (gameOver != 1 && pause != 1)

		{

			gameOver = snekky.update();
			pause = gameOver;
			snekfd.update();
		}

		else

		{

			if (gameOver == 1)

			{

				std::cout << "\rGame Over you ded snek! Your score was " << snekky.snekscore;

			}

			if (pause == 0)

			{

				init(700);
				gameOver = 0;

			}

			
		}

		framesPassed = 0;

	}

	void draw()

	{


		mapGrid.draw();
	

	}

	void controlCallback(int direction)

	{

		switch (direction)

		{

			case (1):

			{

				if (snekky.dir == 3)
				
				{

					break;

				}

				snekky.dir = 1;
				//std::cout << "Up\n";
				break;

			}

			case (2):

			{
				
				if (snekky.dir == 4)

				{

					break;

				}

				snekky.dir = 2;
				//std::cout << "Right\n";
				break;

			}

			case (3):

			{

				if (snekky.dir == 1)

				{

					break;

				}

				snekky.dir = 3;
				//std::cout << "Down\n";
				break;

			}

			case (4):

			{

				if (snekky.dir == 2)

				{

					break;

				}

				snekky.dir = 4;
				//std::cout << "Left\n";
				break;
			}

			case (5):

			{

				pause = 0;
				break;

			}

			default:

			{

				break;

			}

		}

	}

};


int main()

{

	
	game g;
	int start = 1;

	g.init(700);

	//Checks glfw has initialised
	if (!glfwInit())

	{

		exit(EXIT_FAILURE);

	}

	//Initialise Window
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	GLFWwindow* window = glfwCreateWindow(g.windowSize, g.windowSize, "Snek", NULL, NULL);


	//Sets the pointer of the window to a pointer to the game g
	glfwSetWindowUserPointer(window, &g);

	if (!window)

	{

		glfwTerminate();
		exit(EXIT_FAILURE);

	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	while (!glfwWindowShouldClose(window))

	{

		//Setup Frame
		glfwGetFramebufferSize(window, &g.width, &g.height);
		glViewport(0, 0, g.width, g.height);
		glDisable(GL_DEPTH_TEST);
		glClearColor(0.0, 0.0, 0.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);


		//Update Snek
		g.update();


		//Draw Snek
		g.draw();

		//Events

		glfwSetKeyCallback(window, keyCallback);

		glfwSwapBuffers(window);
		glfwPollEvents();



	}



	return 0;

}


void keyCallback(GLFWwindow *window, int button, int scancode, int action, int mods)

{

	void *ptr = glfwGetWindowUserPointer(window);
	game *gptr = static_cast<game*>(ptr);

	if (button == GLFW_KEY_UP && action == GLFW_PRESS)

	{

		gptr->controlCallback(1);

	}

	if (button == GLFW_KEY_RIGHT && action == GLFW_PRESS)


	{

		gptr->controlCallback(2);

	}

	if (button == GLFW_KEY_DOWN && action == GLFW_PRESS)

	{

		gptr->controlCallback(3);

	}

	if (button == GLFW_KEY_LEFT && action == GLFW_PRESS)


	{

		gptr->controlCallback(4);

	}

	if (button == GLFW_KEY_SPACE && action == GLFW_PRESS)

	{

		gptr->controlCallback(5);

	}

}