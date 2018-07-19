#include <iostream>
#include <vector>
#include <GLFW/glfw3.h>
#include <ctime>
#include <thread>
#define PI 3.1459

class grid

{

private:

	std::vector<std::vector<double>> color;


public:

	int height;
	int width;


	void init(int width_, int height_)

	{

		height = height_;
		width = width_;

		color.clear();

		color.resize(width);

		for (int i = 0; i < width; i++)

		{

			color[i].resize(height);

		}


	}

	void setGrid(int i, int j, double value)

	{

		color[i][j] = value;

	}

	int convertPos(int i)

	{

		

	}

	void gridReset()

	{

		for (int i = 0; i < width; i++)

		{

			std::vector <double>zeroArray;

			for (int j = 0; j < height; j++)

			{

				zeroArray.push_back(0.0);

			}

			color[i] = zeroArray;

			zeroArray.clear();

		}

	}


	void draw()

	{

		glColor3f(0.1, 0.1, 0.1);
		glBegin(GL_LINES);
		for (int i = 0; i < width; i++)

		{

			
			glVertex2d(-1.0 + 2*(i / (double)width), -1);
			glVertex2d(-1.0 + 2*(i / (double)width), 1);
	

		}
		for (int i = 0; i < height; i++)

		{


			glVertex2d(-1, -1.0 + 2 * (i / (double)width));
			glVertex2d(1, -1.0 + 2 * (i / (double)width));


		}
		glEnd();


		for (int i = 0; i < width; i++)

		{

			for (int j = 0; j < height; j++)

			{

				if (color[i][j] == 0.5)

				{

					glColor3f(0.5, 0.0, 0.1);

				}

				else if (color[i][j] == 1.0)

				{

					glColor3f(0.1, 0.5, 0.1);

				}

				if (color[i][j] != 0)

				{
					double offSetX = (-1.0 + 1.0 / (double)width) + i * (2.0 / (double)width);
					double offSetY = (- 1.0 + 1.0 / (double)width) + j * (2.0 / (double)height);

					glBegin(GL_POLYGON);
					for (int k = 0; k < 20; k++)

					{

						glVertex2d((0.9 / width)*cos(2 * PI*k / 20.0) + offSetX, (0.9 / height)*sin(2 * PI*k / 20.0) + offSetY);

					}
					glEnd();

					

				}

			}

		}



	}




};

class snekfood

{

private:

	grid *gridptr;
	int spawned;


public:

	int posX;
	int posY;

	void init(grid *gridptr_, int posX_, int posY_)

	{

		gridptr = gridptr_;
		posX = posX_;
		posY = posY_;
		gridptr->setGrid(posX, posY, 0.5);
		spawned = 1;


	}

	void update()

	{

		if (spawned == 1)

		{
			
			gridptr->setGrid(posX, posY, 0.5);

		}

		else

		{

			posX = rand() % (19 + 1);
			srand(clock());

			posY = rand() % (19 + 1);
			srand(clock());

			spawned = 1;

		}

	}

	int checkFood(int x, int y)

	{

		if (x == posX && y == posY && spawned == 1)

		{

			return 1;

		}

		else

		{

			return 0;

		}

	}

	void eaten()

	{

		spawned = 0;

	}

};

class snek


{

private:

	grid *gridptr;
	snekfood *snekfdptr;

public:

	int dir;
	int posX;
	int posY;
	int length;
	int start;
	int snekscore;
	std::vector<std::vector<int>> tailNew;
	std::vector<std::vector<int>> tailOld;


	void init(grid *gridptr_,snekfood *snekfdptr_, int length_, int posX_, int posY_, int dir_)

	{

		gridptr = gridptr_;
		snekfdptr = snekfdptr_;
		dir = dir_;
		posX = posX_;
		posY = posY_;
		length = length_;
		start = 1;
		snekscore = 0;

		tailNew.clear();
		tailOld.clear();

		tailNew.resize(length);
		tailOld.resize(length);

		for (int i = 0; i < length; i++)

		{

			tailNew[i].resize(2);
			tailOld[i].resize(2);

		}



	}

	int update()

	{


		//End Game Condition
		if (posX >= gridptr->width || posX < 0 || posY >= gridptr->height || posY < 0)

		{

			return 1;

		}

		tailNew.resize(length);
		tailOld.resize(length);

		for (int i = 0; i < length; i++)

		{

			tailNew[i].resize(2);
			tailOld[i].resize(2);

		}

		for (int i = 1; i < length; i++)

		{

			if (posX == tailNew[i][0] && posY == tailNew[i][1] && start != 1)

			{

				return 1;

			}

		}

		start = 0;

		gridptr->gridReset();

		for (int i = 0; i < length; i++)

		{

			gridptr->setGrid(tailOld[i][0], tailOld[i][1], 0.0);

		}

		gridptr->setGrid(posX, posY, 1.0);

		for (int i = 0; i < length; i++)

		{

			gridptr->setGrid(tailNew[i][0], tailNew[i][1], 1.0);

		}

		switch (dir)

		{

			case (1):

			{

				posY += 1;
				break;

			}

			case (2):

			{

				posX += 1;
				break;

			}

			case (3):

			{

				posY += -1;
				break;

			}

			case (4):

			{

				posX += -1;
				break;

			}

		}

		tailOld = tailNew;

		tailNew[0][0] = posX;
		tailNew[0][1] = posY;

		for (int i = 1; i < length; i++)

		{

			tailNew[i][0] = tailOld[i-1][0];
			tailNew[i][1] = tailOld[i-1][1];

		}

		if (snekfdptr->checkFood(posX, posY) == 1)

		{

			snekfdptr->eaten();
			snekscore++;
			std::cout << "\rScore: " << snekscore;
			length++;

		}


		return 0;



	}

};

