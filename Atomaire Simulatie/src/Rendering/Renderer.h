#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Math/Vector2.h"
#include "Math/Real.h"
#include "Physics/Particle.h"


class Renderer
{
public:

	Renderer();

	// Een vertex-array om alle huidige deeltjes bij te houden
	void Update(const std::vector<Particle>& particles);

	void Draw(sf::RenderWindow& window) const;

private:

	// Gebruik een eenmalig cirkel-textuur om te hergebruiken per deeltje
	sf::VertexArray vertices;
	sf::Texture circleTexture;

	unsigned int circleTextureSize;

	void GenerateCircleTexture(unsigned int diameter);

};