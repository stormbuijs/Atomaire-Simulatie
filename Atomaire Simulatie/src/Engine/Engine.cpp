#include "Engine/Engine.h"

#include <vector>
#include <random>

#include "Math/Vector2.h"
#include "Physics/Particle.h"


Engine::Engine(): simulation(1280.0, 720.0)
{
}


void Engine::Start()
{
	// Maak een nieuw venster aan
	window.create(
		sf::VideoMode({ 1280, 720 }),
		"Atomaire Simulatie"
	);


	simulation = Simulation(1280.0, 720.0);


	// Testmolecuul
	Simulation::Atom oxygen = simulation.CreateAtom(
		ElementType::Oxygen, Vector2(640.0, 360.0)
	);

	Simulation::Atom hydrogen1 = simulation.CreateAtom(
		ElementType::Hydrogen, Vector2(600.0, 320.0)
	);

	Simulation::Atom hydrogen2 = simulation.CreateAtom(
		ElementType::Hydrogen, Vector2(680.0, 320.0)
	);

	simulation.BondAtoms(oxygen, hydrogen1);
	simulation.BondAtoms(oxygen, hydrogen2);


	simulation.PreSolveBondConstraints();

	Run();
}


void Engine::Run()
{
	while (window.isOpen())
	{
		// Controleer op het sluiten van het venster
		while (const std::optional event = window.pollEvent())
		{
			if (event->is<sf::Event::Closed>())
			{
				window.close();
			}
		}


		// Bereken hoeveel tijd er sinds de vorige frame is verstreken
		// en voer één stap uit van de simulaite
		Real deltaTime = clock.restart().asSeconds();
		simulation.Step(deltaTime);

		renderer.Update(simulation.GetParticles());

		window.clear(sf::Color::Black);
		renderer.Draw(window);
		window.display();
	}
}