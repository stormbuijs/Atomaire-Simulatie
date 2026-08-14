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
	Simulation::Atom carbon = simulation.CreateAtom(ElementType::Carbon, Vector2(640.0, 360.0));

	Simulation::Atom hydrogenA = simulation.CreateAtom(ElementType::Hydrogen, Vector2(600.0, 320.0));
	Simulation::Atom hydrogenB = simulation.CreateAtom(ElementType::Hydrogen, Vector2(660.0, 310.0));
	Simulation::Atom hydrogenC = simulation.CreateAtom(ElementType::Hydrogen, Vector2(600.0, 400.0));
	Simulation::Atom hydrogenD = simulation.CreateAtom(ElementType::Hydrogen, Vector2(660.0, 410.0));

	simulation.BondAtoms(carbon, hydrogenA);
	simulation.BondAtoms(carbon, hydrogenB);
	simulation.BondAtoms(carbon, hydrogenC);
	simulation.BondAtoms(carbon, hydrogenD);
	// Testmolecuul


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
		// en voer één stap uit van de simulatie
		Real deltaTime = clock.restart().asSeconds();
		simulation.Step(deltaTime);

		renderer.Update(simulation.GetParticles());

		window.clear(sf::Color::Black);
		renderer.Draw(window);
		window.display();
	}
}