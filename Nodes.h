#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Window.hpp>
#include<iostream>
class Nodes
{
private:
	sf::Vector2f pos;
	bool visited;
	static int counter;
	int id;
public:
	std::vector<int> neighbours;
	Nodes();
	~Nodes();
	Nodes(sf::Vector2f position);
	static constexpr int noOfNodes = 68;
	sf::CircleShape body;
	void draw(sf::RenderWindow& window);
	void add_to_neighbours(int id_number);
	int getId();
	sf::Vector2f getPosition();
};

