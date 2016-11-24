#include <cstdio>
#include <cmath>
#include <random>
#include <ctime>

#include "RectangleTable.h"
#include "CircleTable.h"

int main()
{
	CircleTable table = CircleTable(1);

	std::uniform_real_distribution<double> unif(-1,1);
	std::default_random_engine def;

	def.seed(std::time(0));
	
	Vector initial = Vector(0,0.5);
	Vector velocity = Vector(unif(def),unif(def));

	double angle = velocity.Arg();

	FILE * file;

	file = fopen("out", "w");

	fprintf(file, "%-10s%-20s%-20s%-20s%-20s%-20s\n", "i", "x", "y", "a", "vx", "vy");

	for (int i = 0; i != 50; i++)
	{
		fprintf(file, "%-10i%-20.15f%-20.15f%-20.15f%-20.15f%-20.15f\n", i, initial.fX, initial.fY, angle, velocity.fX, velocity.fY);
		initial = table.CollisionPoint(initial, velocity);
		angle = std::fmod(table.AngleIncidence(initial, velocity), 2*M_PI);
		velocity = velocity.Rotate(2*angle + M_PI);
	}

	fclose(file);
	
	return 0;
}
