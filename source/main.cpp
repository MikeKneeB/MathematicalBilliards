#include <cstdio>
#include <iostream>
#include <cmath>

#include "StadiumTable.h"
#include "EllipseTable.h"
#include "CircleTable.h"
#include "RectangleTable.h"
#include "Vector.h"

void RunStadium(int n);

void RunEllipse(int n);

void RunCircle(int n);

void RunRectangle(int n);

void InnerRun(ITable & table, Vector & position, Vector & velocity, int n, FILE * file);

void GetArgs(Vector & initial, Vector & velocity);

void Help();

int main()
{
	while (true)
	{
		printf("\n########################\n");
		printf("# Billiards Simulation #\n");
		printf("########################\n\n");

		printf("(1) Stadium Table\n");
		printf("(2) Elliptical Table\n");
		printf("(3) Circular Table\n");
		printf("(4) Rectangular Table\n");
		printf("(5) Help\n");
		printf("(6) Exit\n");

		printf("Please enter a choice: ");
		int choice;

		while (!(std::cin >> choice) || choice < 1 || choice > 6)
		{
			printf("Enter a valid choice.\n");
			std::cin.clear();
			std::cin.ignore();
		}
		
		if (choice == 6) break;

		int n = 0;

		if (choice != 5)
		{
			printf("Please enter number of iterations: ");
			std::cin >> n;
		}

		switch (choice)
		{
			case 1:
				RunStadium(n);
				break;
			case 2:
				RunEllipse(n);
				break;
			case 3:
				RunCircle(n);
				break;
			case 4:
				RunRectangle(n);
				break;
			case 5:
				Help();
				break;
		}
	}
}

void RunStadium(int n)
{
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	StadiumTable table = StadiumTable(x, y);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("stadout", "w");

	printf("\nWriting to 'stadout'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void RunEllipse(int n)
{
	double y, x, r;
	printf("Please enter y coefficient: ");
	std::cin >> y;
	printf("Please enter x coefficient: ");
	std::cin >> x;
	printf("Please enter radius: ");
	std::cin >> r;

	EllipseTable table = EllipseTable(r, x, y);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("elipout", "w");

	printf("\nWriting to 'elipout'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void RunCircle(int n)
{
	double r;
	printf("Please enter radius: ");
	std::cin >> r;

	CircleTable table = CircleTable(r);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("circout", "w");

	printf("\nWriting to 'circout'...\n");

	InnerRun(table, initial, velocity, n, file);
	
	fclose(file);

	printf("Done!\n");

	return;
}

void RunRectangle(int n)
{
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	RectangleTable table = RectangleTable(x, y);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("rectout", "w");

	printf("\nWriting to 'rectout'...\n");

	InnerRun(table, initial, velocity, n, file);
	
	fclose(file);

	printf("Done!\n");

	return;
}

void InnerRun(ITable & table, Vector & position, Vector & velocity, int n, FILE * file)
{
	double angle = velocity.Arg();

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "mp", "a", "vx", "vy");

	for (int i = 0; i != n; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", i, position.fX, position.fY, position.Mod(), angle, velocity.fX, velocity.fY);
		position = table.CollisionPoint(position, velocity);
		angle = std::fmod(table.AngleIncidence(position, velocity), 2*M_PI);
		velocity = table.ReflectVector(position, velocity);
	}
}

void GetArgs(Vector & initial, Vector & velocity)
{
	double iX, iY, vX, vY;

	printf("Please enter initial x: ");
	std::cin >> iX;
	printf("Initial y: ");
	std::cin >> iY;
	printf("Initial x velocity: ");
	std::cin >> vX;
	printf("Initial y velocity: ");
	std::cin >> vY;

	initial = Vector(iX, iY);
	velocity = Vector(vX, vY);

	return; 
}

void Help()
{
	printf("\nThis program simulates billiard balls bouncing off the walls of a billiards"); 
	printf("\ntable. The four options correspond to the different types of table available.");
	printf("\nEach table has a seperate geometry which you will be asked to specify, although");
	printf("\nevery table has a centre at (0,0).");
	printf("\n");
	printf("\nEnter a menu choice (1 - 6) to see details or to exit help: ");
	while (true)
	{
		int choice;
		while (!(std::cin >> choice) || choice < 1 || choice > 6)
		{
			printf("Enter a valid choice.\n");
			std::cin.clear();
			std::cin.ignore();
		}
	
		if (choice == 6) break;

		switch (choice)
		{
			case 1:
				printf("\nThe stadium table is a rectangular table with semi-circles attached to each end\n");
				printf("(the x axis ends, see this handy diagram: (|||) ).\n");
				printf("\n");
				printf("The x and y geometry of the table (which is input by the user) corresponds to\n");
				printf("the poisition of the top most corner of the rectangular part of the table.\n");
				printf("I.e. the length of the rectangular table is 2x, and the width is 2y. The radius\n");
				printf("of the semi-circles is then y, and the maximum length of the table is 2xy.\n\n");
				break;				
			case 2:
				printf("\nThe elliptical table is parameterised by two coefficients and a radius,\n");
				printf("following the equation (x/a)^2 + (y/b)^2 = r^2. With a and b as the x and y\n");
				printf("coefficients respectively.\n\n");
				break;
			case 3:
				printf("\nThe circular table's geometry is parameterised by a single value, its radius.\n");
				printf("The circle then follows the equation x^2 + y^2 = r^2.\n\n");
				break;
			case 4:
				printf("\nThe rectangular table's geometry is specified by the coordinate of its top right\n");
				printf("coordinate. I.e. x and y are input, which corresponds to a table with length 2x\n");
				printf("and width 2y.\n\n");
				break;
			case 5:
				printf("\n'Help' displays above message and then prompts for further help or to quit.\n\n");
				break;
		}
		
		printf("Enter a menu choice (1 - 6) to see details for a table or to exit help: ");
	}
}
