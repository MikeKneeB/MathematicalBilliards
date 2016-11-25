#include <cstdio>
#include <iostream>

#include "StadiumTable.h"
#include "EllipseTable.h"
#include "CircleTable.h"
#include "RectangleTable.h"
#include "Vector.h"

void RunStadium(int n);

void RunEllipse(int n);

void RunCircle(int n);

void RunRectangle(int n);

void GetArgs(Vector & initial, Vector & velocity);

void Help();

int main()
{
	while (true)
	{
		printf("Wow really excellent and cool billiards table fun.\n\n");

		printf("(1) Stadium Table.\n");
		printf("(2) Elliptical Table.\n");
		printf("(3) Circular Table.\n");
		printf("(4) Rectangular Table.\n");
		printf("(5) Exit.\n");

		int choice;

		while (!(std::cin >> choice) || choice < 1 || choice > 5)
		{
			printf("Enter a valid choice.\n");
			std::cin.clear();
			std::cin.ignore();
		}
		
		if (choice == 5) break;

		int n;

		printf("Please enter number of iterations: ");
		cin >> n;

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
		}
	}
}

void RunStadium(int n)
{
	double y, x;
	printf("Please enter y size: ");
	cin >> y;
	printf("Please enter x size: ");
	cin >> x;

	StadiumTable table = StadiumTable(x, y);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("stadout", "w");

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "a", "vx", "vy");

	for (int i = 0; i != n; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", i, initial.fX, initial.fY, angle, velocity.fX, velocity.fY);
		initial = table.CollisionPoint(initial, velocity);
		angle = std::fmod(table.AngleIncidence(initial, velocity), 2*M_PI);
		velocity = table.ReflectVector(initial, velocity);
	}

	fclose(file);

	return;
}

void RunEllipse(int n)
{
	double y, x, r;
	printf("Please enter y coefficient: ");
	cin >> y;
	printf("Please enter x coefficient: ");
	cin >> x;
	printf("Please enter radius: ");
	cin >> r;

	EllipseTable table = EllipseTable(r, x, y);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("elipout", "w");

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "a", "vx", "vy");

	for (int i = 0; i != n; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", i, initial.fX, initial.fY, angle, velocity.fX, velocity.fY);
		initial = table.CollisionPoint(initial, velocity);
		angle = std::fmod(table.AngleIncidence(initial, velocity), 2*M_PI);
		velocity = table.ReflectVector(initial, velocity);
	}

	fclose(file);

	return;
}

void RunCirlce(int n)
{
	double r;
	printf("Please enter radius: ");
	cin >> r;
	printf("Please enter x size: ");
	cin >> x;

	CircleTable table = CirlceTable(r);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("circout", "w");

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "a", "vx", "vy");

	for (int i = 0; i != n; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", i, initial.fX, initial.fY, angle, velocity.fX, velocity.fY);
		initial = table.CollisionPoint(initial, velocity);
		angle = std::fmod(table.AngleIncidence(initial, velocity), 2*M_PI);
		velocity = table.ReflectVector(initial, velocity);
	}

	fclose(file);

	return;
}

void RunStadium(int n)
{
	double y, x;
	printf("Please enter y size: ");
	cin >> y;
	printf("Please enter x size: ");
	cin >> x;

	RectangleTable table = RectangleTable(x, y);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("rectout", "w");

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "a", "vx", "vy");

	for (int i = 0; i != n; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", i, initial.fX, initial.fY, angle, velocity.fX, velocity.fY);
		initial = table.CollisionPoint(initial, velocity);
		angle = std::fmod(table.AngleIncidence(initial, velocity), 2*M_PI);
		velocity = table.ReflectVector(initial, velocity);
	}

	fclose(file);

	return;
}

void GetArgs(Vector & initial, vector & velocity)
{
	double iX, iY, vX, vY;

	printf("Please enter initial x: ");
	cin >> iX;
	printf("Initial y: ");
	cin >> iY;
	printf("Initial x velocity: ");
	cin >> vX;
	printf("Initial y velocity: ");
	cin >> vY;

	intial = Vector(iX, iY);
	velocity = Vector(vX, vY);

	return; 
}

void Help()
{
	printf("\nThis program simulates billiard balls bouncing off the walls of a billiards 
		\ntable. The four options correspond to the different types of table available.
		\nEach table has a seperate geometry which you will be asked to specify, although
		\nevery table has a centre at (0,0).
		\n
		\nEnter a menu choice (1 - 5) to see details for a table or to exit help.\n");
	while (true)
	{
		int choice;
		while (!(std::cin >> choice) || choice < 1 || choice > 5)
		{
			printf("Enter a valid choice.\n");
			std::cin.clear();
			std::cin.ignore();
		}
	
		if (choice == 5) break;

		switch (choice)
		{
			case 1:
				printf("\nThe stadium table is a rectangular table with semi-circles attached to each end\n
					(the x axis ends, see this handy diagram: (|||) ).\n
					\n
					The x and y geometry of the table (which is input by the user) corresponds to\n
					the poisition of the top most corner of the rectangular part of the table.\n
					I.e. the length of the rectangular table is 2x, and the width is 2y. The radius\n
					of the semi-circles is then y, and the maximum length of the table is 2xy.\n\n");
				break;				
			case 2:
				printf("\nThe elliptical table is parameterised by two coefficients and a radius,\n
					following the equation (x/a)^2 + (y/b)^2 = r^2. With a and b as the x and y\n
					coefficients respectively.\n"
				break;
			case 3:
				printf("\nThe circular table's geometry is parameterised by a single value, its radius.\n
					The circle then follows the equation x^2 + y^2 = r^2.\n");
				break;
			case 4:
				printf("\nThe rectangular table's geometry is specified by the coordinate of its top right\n
					coordinate. I.e. x and y are input, which corresponds to a table with length 2x\n
					and width 2y.\n");
				break;
		}
		
		printf("Enter a menu choice (1 - 50 to see details for a table or to exit help.\n");
	}
}
