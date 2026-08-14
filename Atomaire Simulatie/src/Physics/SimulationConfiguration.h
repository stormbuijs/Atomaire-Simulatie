#pragma once

#include "Math/Real.h"


struct SimulationConfiguration
{
	// Intergratie
	int substepCount = 8;

	// Position-Based Dynamics
	int constraintIterations = 5;
	Real bondLength = 20.0;

	// Coulomb-kracht
	Real coulombConstant = 1000.0;
	Real coulombSoftening = 5.0;

	// Pauliprincipe
	Real pauliRepulsionStrength = 50000.0;
	Real pauliRepulsionRadius = 12.0;

	// Deeltjes-eigenschappen
	Real nucleusRadius = 12.0;

	Real electronPairRadius = 3.0;
	Real electronPairMass = 0.1;
	Real electronPairCharge = -2.0;

	// Veiligheidsgrens
	Real minimumDistance = 0.0001;
};