#include <cstdio>
#include <cmath>
#include <random>

#include "RectangleTable.h"

int main()
{
	RectangleTable rec = RectangleTable(1,1);

	std::uniform_real_distribution<double> unif(-1,1);
	std::default_random_engine def;
	
	Vector initial = Vector(unif(def),unif(def));
	Vector velocity = Vector(unif(def),unif(def));

	double angle = velocity.Arg();

	FILE * file;

	file = fopen("out", "w");

	fprintf(file, "%-20s%-20s%-20s\n", "x", "y", "a");

	for (int i = 0; i != 50; i++)
	{
		fprintf(file, "%-20.15f%-20.15f%-20.15f\n", initial.fX, initial.fY, angle);
		initial = rec.CollisionPoint(initial, velocity);
		angle = std::fmod(rec.AngleIncidence(initial, velocity), 2*M_PI);
		velocity = velocity.Rotate(2*angle + M_PI);
	}

	fclose(file);
	
	return 0;
}
