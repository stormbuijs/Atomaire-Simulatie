#include "Rendering/Renderer.h"


Renderer::Renderer() : vertices(sf::PrimitiveType::Triangles)
{
	GenerateCircleTexture(64);
}


void Renderer::GenerateCircleTexture(unsigned int diameter)
{
	circleTextureSize = diameter;

	sf::CircleShape shape(diameter / 2.0f);
	shape.setFillColor(sf::Color::White);

	sf::RenderTexture renderTexture(sf::Vector2u(diameter, diameter));
	renderTexture.clear(sf::Color::Transparent);
	renderTexture.draw(shape);
	renderTexture.display();

	circleTexture = renderTexture.getTexture();
}

void Renderer::Update(const std::vector<Particle>& particles)
{
	// De array verandert automatisch mee
	// 2 driehoeken zijn 6 vertices per deeltje
	vertices.resize(particles.size() * 6);


	float textureSize = static_cast<float>(circleTextureSize);


	for (size_t index = 0; index < particles.size(); ++index)
	{
		Real particleRadius = particles[index].GetRadius();
		Vector2 particlePosition = particles[index].GetPosition();


		float x = static_cast<float>(particlePosition.x);
		float y = static_cast<float>(particlePosition.y);
		float radius = static_cast<float>(particleRadius);


		sf::Vector2f topLeft(x - radius, y - radius);
		sf::Vector2f topRight(x + radius, y - radius);
		sf::Vector2f bottomRight(x + radius, y + radius);
		sf::Vector2f bottomLeft(x - radius, y + radius);

		sf::Vector2f uvTopLeft(0.0f, 0.0f);
		sf::Vector2f uvTopRight(textureSize, 0.0f);
		sf::Vector2f uvBottomRight(textureSize, textureSize);
		sf::Vector2f uvBottomLeft(0.0f, textureSize);


		sf::Vertex* triangles = &vertices[index * 6];


		// Eerste driehoek: linkboven, rechtsboven en rechtsonder
		triangles[0].position = topLeft;
		triangles[0].texCoords = uvTopLeft;

		triangles[1].position = topRight;
		triangles[1].texCoords = uvTopRight;

		triangles[2].position = bottomRight;
		triangles[2].texCoords = uvBottomRight;


		// Tweede driehoek: linksboven, rechtsonder en linksonder
		triangles[3].position = topLeft;
		triangles[3].texCoords = uvTopLeft;

		triangles[4].position = bottomRight;
		triangles[4].texCoords = uvBottomRight;
		
		triangles[5].position = bottomLeft;
		triangles[5].texCoords = uvBottomLeft;
	}
}

void Renderer::Draw(sf::RenderWindow& window) const
{
	sf::RenderStates states;
	states.texture = &circleTexture;

	window.draw(vertices, states);
}