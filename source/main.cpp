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

/**
 * StadiumFractal creates a stadium table as above in RunStadium, but then
 * initialises the ball position close to the right hand wall (by an amount
 * specified by the user). The velocity is initialised with modulus 1 and 
 * argument -pi radians, and the ball is allowed to bounce 30 times.
 *
 * This process is repeated, but the initial velocity argument is varied at
 * each repetition, going between -pi and pi. The total distance travelled after each bounce is output
 * to the file, along with the initial velocity argument.
 *
 * This should hopefully produce interesting 'mirror room' graphs which may be
 * fractal in nature. Output data to 'fracstadout.dat'.
 *
 * This method calls the InnerFrac method.
 *
 * int n: repetitions of the simulation (I.e. number of different
 * initial velocity arguments between -pi and pi) 
 */
void StadiumFractal(int n);

void StadiumChaos(int n);

/**
 * RunEllipse similarly creates an elliptical table and initialises the
 * simulation, which is run n times with data output to 'elipout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunEllipse(int n);

/**
 * See StadiumFractal for details, uses elliptical table instead of stadium
 * table. Output to 'fracelipout.dat'.
 *
 * int n: repetitions of the simulation to run.
 */
void EllipticalFractal(int n);

void EllipticalChaos(int n);

/**
 * As above, circular table and data output to 'circout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunCircle(int n);

/**
 * Similar to StadiumFractal, using the circular table type. Output to
 * 'fraccircout.dat'.
 *
 * int n: repetitions of the simulation to run.
 */
void CircularFractal(int n);

void CircularChaos(int n);

/**
 * As above, rectangular table and data output to 'rectout'.
 *
 * int n: iterations of the simulation to run.
 */
void RunRectangle(int n);

/**
 * Fractal process for rectangular table. Output to 'fracrectout.dat'.
 *
 * int n: repetitions of the simulation to run.
 */
void RectangularFractal(int n);

void RectangularChaos(int n);

/**
 * Runs the lorentz table simulation. Random args not available. Data output to
 * 'loreout.dat'.
 *
 * int n: iterations of the simulation to run.
 */
void RunLorentz(int n);


/**
 * Fractal lorentz table. Output to 'fracloreout.dat'.
 *
 * int n: repetitions of the simulation to run.
 */
void LorentzFractal(int n);

void LorentzChaos(int n);

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

/**
 * InnerFrac is called iternally by each of the Fractal functions. It takes in
 * an ITable type, and performs the fractal result generation n times.
 *
 * The output file is specified as an argument, along with initial position and
 * velocity.
 *
 * PRE: velocity has argument -pi.
 *
 * ITable & table: billiard table for the simulation.
 * Vector & position: initial position for the billiard ball.
 * Vector & velocity: initial velocity for the billiard ball.
 * int n: number of repetitions of the simulation (I.e. number of different
 * initial velocity angles.)
 * FILE * file: file stream to write to.
 */
void InnerFrac(ITable & table, Vector & position, Vector & velocity, int n, FILE * file);

void InnerChaos(ITable & table, Vector & position1, Vector & position2, Vector & velocity1, Vector & velocity2, int n, FILE * file);

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
		//Print menu choices
		printf("\n(1) Stadium Table\n");
		printf("(2) Elliptical Table\n");
		printf("(3) Circular Table\n");
		printf("(4) Rectangular Table\n");
		printf("(5) Lorentz Table\n");
		printf("(6) Help\n");
		printf("(0) Exit\n");

		printf("Please enter a choice: ");
		int choice, secondChoice;

		//Get menu choice.
		while (!(std::cin >> choice) || choice < 0 || choice > 6)
		{
			printf("Enter a valid choice: ");
			std::cin.clear();
			std::cin.ignore();
		}
		
		//Exit if choice 0
		if (choice == 0) break;
		
		//Initialise variable for number of iterations.
		int n = 0;

		//Don't display simulation options for the help function.
		if (choice != 6)
		{		
			printf("Please enter 0 for regular plots, 1 for fractal plots or 2 for chaotic behaviour analysis: ");
			while (!(std::cin >> secondChoice) || secondChoice < 0 || secondChoice > 2)
			{
				printf("Enter a valid choice: ");
				std::cin.clear();
				std::cin.ignore();
			}

			printf("Please enter number of iterations: ");
			std::cin >> n;
		}

		//Run specified option.
		switch (choice)
		{
			case 1:
				if (secondChoice == 0)
					RunStadium(n);
				else if (secondChoice == 1)
					StadiumFractal(n);
				else
					StadiumChaos(n);
				break;
			case 2:
				if (secondChoice == 0)
					RunEllipse(n);
				else if (secondChoice == 1)
					EllipticalFractal(n);
				else
					EllipticalChaos(n);
				break;
			case 3:
				if (secondChoice == 0)
					RunCircle(n);
				else if (secondChoice == 1)
					CircularFractal(n);
				else
					CircularChaos(n);
				break;
			case 4:
				if (secondChoice == 0)
					RunRectangle(n);
				else if (secondChoice == 1)
					RectangularFractal(n);
				else
					RectangularChaos(n);
				break;
			case 5:
				if (secondChoice == 0)
					RunLorentz(n);
				else if (secondChoice == 1)
					LorentzFractal(n);
				else
					LorentzChaos(n);
				break;
			case 6:
				Help();
				break;
		}
	}
}

void RunStadium(int n)
{
	//Get stadium dimensions. See StadiumTable class for details of how
	//this table is parameterised. 
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	//Create table.
	StadiumTable table = StadiumTable(x, y);

	Vector initial, velocity;

	bool choice;

	printf("Enter 1 for random initial coniditions, and 0 for user-input: ");

	//Choose random of specified arguments.
	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	if (choice)
	{
		//Table parameters stored in array to be passed to the random
		//initial condition generator.
		double params[2] = {x, y};
		//Randomly generate based on table parameters.
		RandomArgs(initial, velocity, 4, params);
	}
	else
	{
		//Otherwise ask for user arguments.
		GetArgs(initial, velocity);
	}

	FILE * file;

	file = fopen("stadout.dat", "w");

	printf("\nWriting to 'stadout.dat'...\n");

	//Call internal run function.
	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void StadiumChaos(int n)
{
	//Get stadium dimensions. See StadiumTable class for details of how
	//this table is parameterised. 
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	//Create table.
	StadiumTable table = StadiumTable(x, y);

	Vector initial1, velocity1, initial2, velocity2;

	//No random option.
	GetArgs(initial1, velocity1);

	printf("\nPlease now enter a second set of initial conditions for comparison.\nThese should be very close to the first set, for analysis of how\nsmall changes to initial conditions affect the system.\n");
	//Need two sets of initial conditions for this analysis.
	GetArgs(initial2, velocity2);

	FILE * file;

	file = fopen("chaostadout.dat", "w");

	printf("\nWriting to 'chaostadout.dat'...\n");

	//Call internal chaos function.
	InnerChaos(table, initial1, initial2, velocity1, velocity2, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void StadiumFractal(int n)
{
	//Get table dimensions as before.
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	//Get offset.
	double offset;
	printf("Please enter offset from table edge (rec ~ 0.00001): ");
	std::cin >> offset;

	//Create table.
	StadiumTable table = StadiumTable(x, y);

	//Initialise position using table parameters and offset.
	//Initial position is next to right hand wall, offset a small amount.
	//The offset is needed, as if the ball is initially directly against the
	//wall the simulation fails.
	Vector position(x + y - offset, 0);

	//Initial velocity is directly away from the wall. I.e. mod 1, argument
	//-pi.
	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fracstadout.dat", "w");
	printf("Writing to file fracstadout.dat...\n");

	//Call inner fractal method.
	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
}

void RunEllipse(int n)
{
	//Table dimensions.
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

	printf("Enter 1 for random initial conditions, and 0 for user-input: ");

	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	//Generate random conditions or ask for user input.
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

	//Call inner method.
	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void EllipticalChaos(int n)
{
	//Get stadium dimensions. See StadiumTable class for details of how
	//this table is parameterised. 
	double y, x, r;
	printf("Please enter y coefficient: ");
	std::cin >> y;
	printf("Please enter x coefficient: ");
	std::cin >> x;
	printf("Please enter radius: ");
	std::cin >> r;

	//Create table.
	EllipseTable table = EllipseTable(r, x, y);

	Vector initial1, velocity1, initial2, velocity2;

	//No random option.
	GetArgs(initial1, velocity1);

	printf("\nPlease now enter a second set of initial conditions for comparison.\nThese should be very close to the first set, for analysis of how\nsmall changes to initial conditions affect the system.\n");

	//Need two sets of initial conditions for this analysis.
	GetArgs(initial2, velocity2);

	FILE * file;

	file = fopen("chaoelipout.dat", "w");

	printf("\nWriting to 'chaoelipout.dat'...\n");

	//Call internal chaos function.
	InnerChaos(table, initial1, initial2, velocity1, velocity2, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}


void EllipticalFractal(int n)
{
	//Get dimensions.
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

	//As before, initialise position as offset away from right hand edge. 
	Vector position(r*x - offset, 0);

	//Initial velocity.
	Vector velocity(-1, 0);

	FILE * file;
	file = fopen("fracelipout.dat", "w");
	printf("Writing to file fracelipout.dat...\n");

	//Call inner method.
	InnerFrac(table, position, velocity, n, file);

	printf("Done!\n");
	fclose(file); 
}

void RunCircle(int n)
{
	//Get dimensions.
	double r;
	printf("Please enter radius: ");
	std::cin >> r;

	CircleTable table = CircleTable(r);

	Vector initial, velocity;

	bool choice;

	printf("Enter 1 for random initial conditions, and 0 for user-input: ");

	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore();
		printf("Please enter a valid choice: ");
	}

	//Generate args or ask for user args.
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

	//Call inner method.
	InnerRun(table, initial, velocity, n, file);
	
	fclose(file);

	printf("Done!\n");

	return;
}

void CircularChaos(int n)
{
	//Get dimensions.
	double r;
	printf("Please enter radius: ");
	std::cin >> r;

	//Create table.
	CircleTable table = CircleTable(r);

	Vector initial1, velocity1, initial2, velocity2;

	//No random option.
	GetArgs(initial1, velocity1);

	printf("\nPlease now enter a second set of initial conditions for comparison.\nThese should be very close to the first set, for analysis of how\nsmall changes to initial conditions affect the system.\n");
	//Need two sets of initial conditions for this analysis.
	GetArgs(initial2, velocity2);

	FILE * file;

	file = fopen("chaocircout.dat", "w");

	printf("\nWriting to 'chaocircout.dat'...\n");

	//Call internal chaos function.
	InnerChaos(table, initial1, initial2, velocity1, velocity2, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}


void CircularFractal(int n)
{
	//As in previous fractal functions:
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
	//As in previous run functions:
	double y, x;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	RectangleTable table = RectangleTable(x, y);

	Vector initial, velocity;

	bool choice;

	printf("Enter 1 for random initial conditions, or 0 for user-input: ");

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

void RectangularChaos(int n)
{
	//Get dimensions.
	double x, y;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;

	//Create table.
	RectangleTable table = RectangleTable(x, y);

	Vector initial1, velocity1, initial2, velocity2;

	//No random option.
	GetArgs(initial1, velocity1);

	printf("\nPlease now enter a second set of initial conditions for comparison.\nThese should be very close to the first set, for analysis of how\nsmall changes to initial conditions affect the system.\n");
	//Need two sets of initial conditions for this analysis.
	GetArgs(initial2, velocity2);

	FILE * file;

	file = fopen("chaorectout.dat", "w");

	printf("\nWriting to 'chaorectout.dat'...\n");

	//Call internal chaos function.
	InnerChaos(table, initial1, initial2, velocity1, velocity2, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}


void RectangularFractal(int n)
{
	//As in previous fractal functions:
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
	//As in previous run functions:
	double y, x, r;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;
	printf("Please enter radius of inner circle: ");
	std::cin >> r;

	LorentzTable table = LorentzTable(x, y, r);

	Vector initial, velocity;

	GetArgs(initial, velocity);

	FILE * file;

	file = fopen("loreout.dat", "w");

	printf("\nWriting to 'loreout.dat'...\n");

	InnerRun(table, initial, velocity, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}

void LorentzChaos(int n)
{
	//Get dimensions.
	double x, y, r;
	printf("Please enter y size: ");
	std::cin >> y;
	printf("Please enter x size: ");
	std::cin >> x;
	printf("Please enter radius of inner circle: ");
	std::cin >> r;

	//Create table.
	LorentzTable table = LorentzTable(x, y, r);

	Vector initial1, velocity1, initial2, velocity2;

	//No random option.
	GetArgs(initial1, velocity1);
	printf("\nPlease now enter a second set of initial conditions for comparison.\nThese should be very close to the first set, for analysis of how\nsmall changes to initial conditions affect the system.\n");
	//Need two sets of initial conditions for this analysis.
	GetArgs(initial2, velocity2);

	FILE * file;

	file = fopen("chaoloreout.dat", "w");

	printf("\nWriting to 'chaoloreout.dat'...\n");

	//Call internal chaos function.
	InnerChaos(table, initial1, initial2, velocity1, velocity2, n, file);

	fclose(file);

	printf("Done!\n");

	return;
}


void LorentzFractal(int n)
{
	//As in previous fractal functions:
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
	//Get initial angle.
	double angle = velocity.Arg();

	//Print headers to file.
	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "mp", "pa", "a", "vx", "vy", "mv", "va");

	//For specified number of iterations:
	for (int i = 0; i != n; i++)
	{
		//Print current status.
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", 
			i, position.fX, position.fY, position.Mod(), position.Arg(),
			angle, velocity.fX, velocity.fY, velocity.Mod(), velocity.Arg());
		//Find next position.
		position = table.CollisionPoint(position, velocity);
		//Find angle between table wall and ball trajectory.
		angle = std::fmod(table.AngleIncidence(position, velocity), 2*M_PI);
		//Find velocity after collision.
		velocity = table.ReflectVector(position, velocity);
	}
}

void InnerFrac(ITable & table, Vector & position, Vector & velocity, int n, FILE * file)
{
	//Initialise varibales and temporary variables.
	double tLength, pLength = 0, xLength = 0, yLength = 0, theta;
	//pLength, xLength and yLength are the important data to output,
	//tLength and theta are temporary useful variables.

	//Store initial conditions, as they must be returned to after each run.
	Vector initial = position;
	Vector vInitial = velocity;

	//Temporary position vector.
	Vector tPosition;
	
	//Write header to file.
	fprintf(file, "%-24s%-24s%-24s%-24s%-24s%-24s%-24s\n", "i", "pLength", "angle", "xLength", "yLength", "xVec", "yVec");
	
	for (int i = 0; i != n; i++)
	{
		//One run of the simulation:
		//Initial angle for velocity.
		theta = -M_PI + (2 * M_PI) * (1.0 * i / n);
		for (int j = 0; j != 30; j++)
		{
			//Compute next poisition.
			tPosition = table.CollisionPoint(position, velocity);
			//Path length from current to next position.
			tLength = (position - tPosition).Mod();
			//Add to total path.
			pLength += tLength;

			//Update x and yLengths in similar ways.
			xLength += std::abs(position.fX - tPosition.fX);
			yLength += std::abs(position.fY - tPosition.fY);
			
			//Update position and velocity.
			position = tPosition;
			velocity = table.ReflectVector(position, velocity);
			
			//Now using tPosition for mirror-room plot.
			//tPosition is total path length with same argument as 
			//initial velocity.
			//This can be used to produce (hopefully) fractal
			//images.
			tPosition = Vector(pLength, 0);
			tPosition = tPosition.Rotate(theta);
			
			//Print data to output file.
			fprintf(file, "%-24i%-24.15f%-24.15f%-24.15f%-24.15f%-24.15f%-24.15f\n", j, pLength, theta, xLength, yLength, tPosition.fX, tPosition.fY);
		}
		//Reset position.
		position = initial;
		//vInitial is now rotated around.
		vInitial = vInitial.Rotate(-M_PI*2/n);
		//Reset velocity.
		velocity = vInitial;
		//Reset lengths.
		pLength = 0;
		xLength = 0;
		yLength = 0;
	}
}

void InnerChaos(ITable & table, Vector & position1, Vector & position2, Vector & velocity1, Vector & velocity2, int n, FILE * file)
{
	fprintf(file, "%-24s%-24s%-24s%-24s%-24s%-24s%-24s%-24s\n", "i", "1x", "1y", "1pa", "2x", "2y", "2pa", "dpa");

	for (int i = 0; i != n; i++)
	{
		//Print current status.
		fprintf(file, "%-24i%-24.15f%-24.15f%-24.15f%-24.15f%-24.15f%-24.15f%-24.15f\n", 
			i, position1.fX, position1.fY, position1.Arg(),
			position2.fX, position2.fY, position2.Arg(), std::abs(position1.Arg() - position2.Arg()));
		//Find next position.
		position1 = table.CollisionPoint(position1, velocity1);
		position2 = table.CollisionPoint(position2, velocity2);
		//Find velocity after collision.
		velocity1 = table.ReflectVector(position1, velocity1);
		velocity2 = table.ReflectVector(position2, velocity2);
	}
}

void GetArgs(Vector & initial, Vector & velocity)
{
	//Doubles to store input.
	double iX, iY, vX, vY;

	//Get input:
	printf("Please enter initial x: ");
	std::cin >> iX;
	printf("Initial y: ");
	std::cin >> iY;
	printf("Initial x velocity: ");
	std::cin >> vX;
	printf("Initial y velocity: ");
	std::cin >> vY;

	//Store input in vectors.
	initial = Vector(iX, iY);
	velocity = Vector(vX, vY);

	return; 
}

void RandomArgs(Vector & initial, Vector & velocity, int type, double params[])
{
	//Initialise the random engine.
	std::default_random_engine engine;
	engine.seed(std::time(0));

	//Temporary doubles to store output.
	double temp, iX, iY;
	
	//Type 1 = circle
	if (type == 1)
	{
		//X coord lies between -radius and radius:
		std::uniform_real_distribution<double> rangeX(-params[0], params[0]);
		//Get random x.
		iX = rangeX(engine);

		//Now y coord is constrained by value of x, so calculate
		//possible y range.
		temp = std::sqrt(params[0] * params[0] - iX * iX);

		//Get random y as before.
		std::uniform_real_distribution<double> rangeY(-temp, temp);
		iY = rangeY(engine);
	}
	//Type 2 = ellipse
	else if (type == 2)
	{
		//Possible x range is calculated using y = 0.
		temp = params[0] * params[1];
		std::uniform_real_distribution<double> rangeX(-temp, temp);
		//Get random x.
		iX = rangeX(engine);

		//Y range is now constrained by x, so using x = iX calculate
		//possible y range.
		temp = params[2] * std::sqrt(params[0] * params[0] - (iX * iX)/(params[1] * params[1]));

		//Get y.
		std::uniform_real_distribution<double> rangeY(-temp, temp);
		iY = rangeY(engine);

	}
	//Type 3 = rectangle
	else if (type == 3)
	{
		//Ranges specified by x and y lengths of rectangle.
		std::uniform_real_distribution<double> rangeX(-params[0], params[0]);
		std::uniform_real_distribution<double> rangeY(-params[1], params[1]);
		//Get random values.
		iX = rangeX(engine);
		iY = rangeY(engine);

	}
	//Type 4 = stadium
	else if (type == 4)
	{
		//X range is constrained by x length of table + radius of
		//semicircles (i.e. x + y)
		std::uniform_real_distribution<double> rangeX(-params[0] - params[1], params[0] + params[1]);

		//Generate random x.
		iX = rangeX(engine);

		//If iX is within right side semicircle.
		if (iX > params[0])
		{
			//Generate y as for a circle.
			temp = iX - params[0];

			//Calculate y range.
			temp = std::sqrt(params[1] * params[1] - temp * temp);

			std::uniform_real_distribution<double> rangeY(-temp, temp);
			//Generate y.
			iY = rangeY(engine);

		}
		//If iX is within left side semicircle.
		else if (iX < -params[0])
		{
			//Generate as for circle.
			temp = iX + params[0];

			temp = std::sqrt(params[1] * params[1] - temp * temp);

			std::uniform_real_distribution<double> rangeY(-temp, temp);
			iY = rangeY(engine);

		}
		//iX is within the rectangular section.
		else
		{
			//Generate as for rectangle.
			std::uniform_real_distribution<double> rangeY(-params[1], params[1]);
			iY = rangeY(engine);
		}
	}
	//Type is not recognised. This will never be encountered, as this
	//function is only used internally.
	else
	{
		printf("NO\n");
		iY = 0;
		iX = 0;
	}

	//Put generated position values in initial vector.
	initial.fX = iX;
	initial.fY = iY;
	
	//Velocity is randomised, but less constraint required.
	velocity = Vector(0.0, 0.0);
	std::uniform_real_distribution<double> rangeV(-1,1);

	//Want at least one velocity component to be non-zero.
	while (velocity.fX == 0.0 && velocity.fY == 0.0)
	{
		velocity.fX = rangeV(engine);
		velocity.fY = rangeV(engine);
	}

	return;
}

void Help()
{
	//Print basic help message.
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
		//Get choice for help menu.
		int choice;
		while (!(std::cin >> choice) || choice < 0 || choice > 6)
		{
			printf("Enter a valid choice.\n");
			std::cin.clear();
			std::cin.ignore();
		}
	
		//Exit on 0.
		if (choice == 0) break;

		//Display specific help.
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
