#include <cstdio>
#include <iostream>
#include <cmath>
#include <random>
#include <ctime>
#include <string>

#include "StadiumTable.h"
#include "EllipseTable.h"
#include "CircleTable.h"
#include "RectangleTable.h"
#include "LorentzTable.h"
#include "Vector.h"

/**
 * RunStadium creates a stadium billiards table from user supplied dimensions,
 * and then initialises the billiard balls position and velocity. It runs the
 * simulation for n iterations. Data is output to the file 'stadout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunStadium(int n);

void StadiumFractal(int n);

/**
 * RunEllipse similarly creates an elliptical table and initialises the
 * simulation, which is run n times with data output to 'elipout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunEllipse(int n);

void EllipticalFractal(int n);

/**
 * As above, circular table and data output to 'circout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunCircle(int n);

void CircularFractal(int n);

/**
 * As above, rectangular table and data output to 'rectout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunRectangle(int n);

void RectangularFractal(int n);

void RunLorentz(int n);

void LorentzFractal(int n);

/**
 * InnerRun is called iternally by each of the Run functions, and performs the
 * actual simulation once table and initial conditions have been initialised.
 * It takes in all the necessary components of the simulation, including the
 * number of iterations plus a file to output data to.
 *
 * Once this function has run the Vector position will contain the final
 * position of the ball, and velocity conatins its final velocity.
 *
 * ITable & table: billiard table for the simulation.
 * Vector & position: initial position of the billiard ball.
 * Vector & velocity: initial velocity of the billiard ball.
 * int n: number of iterations for the simulation.
 * FILE * file: file stream to write to.
 */
void InnerRun(ITable & table, Vector & position, Vector & velocity, int n, FILE * file);

void InnerFrac(ITable & table, Vector & position, Vector & velocity, int n, FILE * file);

/**
 * Initialises vector position and velocity of the billiard ball, by asking
 * for user input. initial and velocity will contain the values once the
 * function has run.
 *
 * Vector & initial: Vector to store initial position in.
 * Vector & velocity: Vector to store initial velocity in.
 */
void GetArgs(Vector & initial, Vector & velocity);

/**
 * Function to randomise initial conditions for a given table type with
 * supplied parameters. initial and velocity will contain the values once the
 * function has run.
 *
 * The type of billiard table must be specified using the parameter type. The
 * three options are: 1=circular 2= elliptical 3=rectangular 4=stadium. The
 * parameter params must contain the necessary number of parameters defining
 * the geometry of the table. For the rectangular and stadium tables this is
 * an array with two values, for the circular table just one and three for the
 * elliptical table.
 *
 * Vector & initial: Vector to store initial position in.
 * Vector & velocity: Vector to store initial velocity in.
 * int type: integer 1-4 specifying the type of table to generate values for.
 * double params[]: array specifying the geometry of the table.
 */
void RandomArgs(Vector & initial, Vector & velocity, int type, double params[]);

/**
 * Prints help messages!
 */
void Help();

int main()
{
	printf("\n########################\n");
	printf("# Billiards Simulation #\n");
	printf("########################\n");

	while (true)
	{
		printf("\n(1) Stadium Table\n");
		printf("(2) Elliptical Table\n");
		printf("(3) Circular Table\n");
		printf("(4) Rectangular Table\n");
		printf("(5) Lorentz Table\n");
		printf("(6) Help\n");
		printf("(0) Exit\n");

		printf("Please enter a choice: ");
		int choice, secondChoice;

		while (!(std::cin >> choice) || choice < 0 || choice > 6)
		{
			printf("Enter a valid choice: ");
			std::cin.clear();
			std::cin.ignore();
		}
		
		if (choice == 0) break;
		
		int n = 0;

		if (choice != 6)
		{		
			printf("Please enter 0 for regular plots, 1 for fractal plots: ");
			while (!(std::cin >> secondChoice) || secondChoice < 0 || secondChoice > 1)
			{
				printf("Enter a valid choice: ");
				std::cin.clear();
				std::cin.ignore();
			}

			printf("Please enter number of iterations: ");
			std::cin >> n;
		}

		switch (choice)
		{
			case 1:
				if (secondChoice == 0)
					RunStadium(n);
				else
					StadiumFractal(n);
				break;
			case 2:
				if (secondChoice == 0)
					RunEllipse(n);
				else
					EllipticalFractal(n);
				break;
			case 3:
				if (secondChoice == 0)
					RunCircle(n);
				else
					CircularFractal(n);
				break;
			case 4:
				if (secondChoice == 0)
					RunRectangle(n);
				else
					RectangularFractal(n);
				break;
			case 5:
				if (secondChoice == 0)
					RunLorentz(n);
				else
					LorentzFractal(n);
				break;
			case 6:
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

	bool choice;

	printf("Enter 1 for random args, and 0 for user-input args: ");

	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	if (choice)
	{
		double params[2] = {x, y};
		RandomArgs(initial, velocity, 4, params);
	}
	else
	{
		GetArgs(initial, velocity);
	}

	FILE * file;

	file = fopen("stadout.dat", "w");

	printf("\nWriting to 'stadout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void StadiumFractal(int n)
{
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	double offset;
	printf("Please enter offset from table edge (rec ~ 0.00001): ");
	std::cin >> offset;

	StadiumTable table = StadiumTable(x, y);

	Vector position(x + y - offset, 0);

	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fracstadout.dat", "w");
	printf("Writing to file fracstadout.dat...\n");

	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
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

	bool choice;

	printf("Enter 1 for random args, and 0 for user-input args: ");

	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	if (choice)
	{
		double params[3] = {r, x, y};
		RandomArgs(initial, velocity, 2, params);
	}
	else
	{
		GetArgs(initial, velocity);
	}

	FILE * file;

	file = fopen("elipout.dat", "w");

	printf("\nWriting to 'elipout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void EllipticalFractal(int n)
{
	double y, x, r;
	printf("Please enter y coefficient: ");
	std::cin >> y;
	printf("Please enter x coefficient: ");
	std::cin >> x;
	printf("Please enter radius: ");
	std::cin >> r;

	double offset;
	printf("Please enter offset from table edge (rec ~ 0.00001): ");
	std::cin >> offset;

	EllipseTable table = EllipseTable(r, x, y);

	Vector position(r*x - offset, 0);

	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fracelipout.dat", "w");
	printf("Writing to file fracelipout.dat...\n");

	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
}

void RunCircle(int n)
{
	double r;
	printf("Please enter radius: ");
	std::cin >> r;

	CircleTable table = CircleTable(r);

	Vector initial, velocity;

	bool choice;

	printf("Enter 1 for random args, and 0 for user-input args: ");

	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	if (choice)
	{
		double params[1] = {r};
		RandomArgs(initial, velocity, 1, params);
	}
	else
	{
		GetArgs(initial, velocity);
	}

	FILE * file;

	file = fopen("circout.dat", "w");

	printf("\nWriting to 'circout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);
	
	fclose(file);

	printf("Done!\n");

	return;
}

void CircularFractal(int n)
{
	double r;
	printf("Please enter radius: ");
	std::cin >> r;

	double offset;
	printf("Please enter offset from table edge (rec ~ 0.00001): ");
	std::cin >> offset;

	CircleTable table = CircleTable(r);

	Vector position(r - offset, 0);

	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fraccircout.dat", "w");
	printf("Writing to file fraccircout.dat...\n");

	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
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

	bool choice;

	printf("Enter 1 for random args, or 0 for user-input args: ");

	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	if (choice)
	{
		double params[2] = {x, y};
		RandomArgs(initial, velocity, 3, params);
	}
	else
	{
		GetArgs(initial, velocity);
	}


	FILE * file;

	file = fopen("rectout.dat", "w");

	printf("\nWriting to 'rectout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);
	
	fclose(file);

	printf("Done!\n");

	return;
}

void RectangularFractal(int n)
{
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	double offset;
	printf("Please enter offset from table edge (rec ~ 0.00001): ");
	std::cin >> offset;

	RectangleTable table = RectangleTable(x, y);

	Vector position(x - offset, 0);

	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fracrectout.dat", "w");
	printf("Writing to file fracrectout.dat...\n");

	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
}

void RunLorentz(int n)
{
	double y, x, r;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;
	printf("Please enter radius of inner circle: ");
	std::cin >> r;

	LorentzTable table = LorentzTable(x, y, r);

	Vector initial, velocity;

//	bool choice;

//	printf("Enter 1 for random args, and 0 for user-input args: ");

//	while (!(std::cin >> choice))
//	{
//		std::cin.clear();
//		std::cin.ignore();
//		printf("Please enter a valid choice: ");
//	}

//	if (choice)
//	{
//		double params[3] = {r, x, y};
//		RandomArgs(initial, velocity, 2, params);
//	}
//	else
//	{
		GetArgs(initial, velocity);
//	}

	FILE * file;

	file = fopen("loreout.dat", "w");

	printf("\nWriting to 'loreout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void LorentzFractal(int n)
{
	double y, x, r;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;
	printf("Please enter radius of inner circle: ");
	std::cin >> r;

	double offset;
	printf("Please enter offset from table edge (rec ~ 0.00001): ");
	std::cin >> offset;

	LorentzTable table = LorentzTable(x, y, r);

	Vector position(x - offset, 0);

	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fracloreout.dat", "w");
	printf("Writing to file fracloreout.dat...\n");

	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
}

void InnerRun(ITable & table, Vector & position, Vector & velocity, int n, FILE * file)
{
	double angle = velocity.Arg();

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "mp", "pa", "a", "vx", "vy", "mv", "va");

	for (int i = 0; i != n; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", 
			i, position.fX, position.fY, position.Mod(), std::fmod(position.Arg(), 2*M_PI),
			angle, velocity.fX, velocity.fY, velocity.Mod(), std::fmod(velocity.Arg(), 2*M_PI));
		position = table.CollisionPoint(position, velocity);
		angle = std::fmod(table.AngleIncidence(position, velocity), 2*M_PI);
		velocity = table.ReflectVector(position, velocity);
	}
}

void InnerFrac(ITable & table, Vector & position, Vector & velocity, int n, FILE * file)
{
	double tLength, pLength = 0, xLength = 0, yLength = 0, theta;

	Vector initial = position;
	Vector vInitial = velocity;

	Vector tPosition;
	
	fprintf(file, "%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "i", "pLength", "angle", "xLength", "yLength", "xVec", "yVec");
	
	for (int i = 0; i != n; i++)
	{
		theta = -M_PI + (2 * M_PI) * (1.0 * i / n);
		for (int j = 0; j != 50; j++)
		{
			tPosition = table.CollisionPoint(position, velocity);
			tLength = (position - tPosition).Mod();
			pLength += tLength;

			tPosition = Vector(pLength, 0);
			tPosition = tPosition.Rotate(theta);

			xLength += std::abs(position.fX - tPosition.fX);
			yLength += std::abs(position.fY - tPosition.fY);

			position = table.CollisionPoint(position, velocity);
			velocity = table.ReflectVector(position, velocity);
			fprintf(file, "%-20i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", j, pLength, theta, xLength, yLength, tPosition.fX, tPosition.fY);
		}
		position = initial;
		vInitial = vInitial.Rotate(-M_PI*2/n);
		velocity = vInitial;
		pLength = 0;
		xLength = 0;
		yLength = 0;
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

void RandomArgs(Vector & initial, Vector & velocity, int type, double params[])
{
	std::default_random_engine engine;
	engine.seed(std::time(0));

	double temp, iX, iY;
	
	if (type == 1)
	{
		std::uniform_real_distribution<double> rangeX(-params[0], params[0]);
		iX = rangeX(engine);

		temp = std::sqrt(params[0] * params[0] - iX * iX);

		std::uniform_real_distribution<double> rangeY(-temp, temp);
		iY = rangeY(engine);
	}
	else if (type == 2)
	{
		temp = params[0] * params[1];
		std::uniform_real_distribution<double> rangeX(-temp, temp);
		iX = rangeX(engine);

		temp = params[2] * std::sqrt(params[0] * params[0] - (iX * iX)/(params[1] * params[1]));

		std::uniform_real_distribution<double> rangeY(-temp, temp);
		iY = rangeY(engine);

	}
	else if (type == 3)
	{
		std::uniform_real_distribution<double> rangeX(-params[0], params[0]);
		std::uniform_real_distribution<double> rangeY(-params[1], params[1]);
		iX = rangeX(engine);
		iY = rangeY(engine);

	}
	else if (type == 4)
	{
		std::uniform_real_distribution<double> rangeX(-params[0] - params[1], params[0] + params[1]);

		iX = rangeX(engine);

		if (iX > params[0])
		{
			temp = iX - params[0];

			temp = std::sqrt(params[1] * params[1] - temp * temp);

			std::uniform_real_distribution<double> rangeY(-temp, temp);
			iY = rangeY(engine);

		}
		else if (iX < -params[0])
		{
			temp = iX + params[0];

			temp = std::sqrt(params[1] * params[1] - temp * temp);

			std::uniform_real_distribution<double> rangeY(-temp, temp);
			iY = rangeY(engine);

		}
		else
		{
			std::uniform_real_distribution<double> rangeY(-params[1], params[1]);
			iY = rangeY(engine);
		}
	}
	else
	{
		printf("NO\n");
		iY = 0;
		iX = 0;
	}

	initial.fX = iX;
	initial.fY = iY;
	
	velocity = Vector(0.0, 0.0);
	std::uniform_real_distribution<double> rangeV(-1,1);

	while (velocity.fX == 0.0 && velocity.fY == 0.0)
	{
		velocity.fX = rangeV(engine);
		velocity.fY = rangeV(engine);
	}

	return;
}

void Help()
{
	printf("\nThis program simulates billiard balls bouncing off the walls of a billiards"); 
	printf("\ntable. The four options correspond to the different types of table available.");
	printf("\nEach table has a seperate geometry which you will be asked to specify, although");
	printf("\nevery table has a centre at (0,0).");
	printf("\n");
	printf("\nEach table can be run with regular plot options or fractal plot options, which");
	printf("\nwill produce output in different files. The fractal data is useful for observing");
	printf("\nchaotic (and hence fractal) properties of the system. The regular data is more");
	printf("\nuseful for observing other system properties.");
	printf("\n");
	printf("\nEnter a menu choice (0 - 6) to see details or to exit help: ");
	while (true)
	{
		int choice;
		while (!(std::cin >> choice) || choice < 0 || choice > 6)
		{
			printf("Enter a valid choice.\n");
			std::cin.clear();
			std::cin.ignore();
		}
	
		if (choice == 0) break;

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
				printf("\nThe Lorentz table is a rectangular table with a circle cut out of the middle.\n");
				printf("The ball can therefore bounce of the inside walls of the rectangle, or the outside\n");
				printf("walls of the inner circle. All possible trajectories are ergodic (apparently.)\n\n");
			case 6:
				printf("\n'Help' displays above message and then prompts for further help or to quit.\n\n");
				break;
		}
		printf("Enter a menu choice (1 - 6) to see details for a table or to exit help: ");
	}
}
