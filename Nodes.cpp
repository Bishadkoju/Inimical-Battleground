#include "Nodes.h"

int Nodes::counter = 0;

Nodes::Nodes()
{
}

Nodes::~Nodes()
{
	delete this;
}

Nodes::Nodes(sf::Vector2f position)
{
	id = counter;
	counter++;
	pos = position;
	body.setPosition(position);
}


void Nodes::draw(sf::RenderWindow& window)
{
	window.draw(body);
}



void Nodes::add_to_neighbours(int id_number)
{
	/*neighbours[neighbours_count] = id_number;
	neighbours_count++;*/
	for (const auto neighbour : neighbours)
	{
		if (neighbour == id_number)
		{
			return;
		}
	}
	neighbours.push_back(id_number);
}

int Nodes::getId()
{
	return id;
}

sf::Vector2f Nodes::getPosition()
{
	return pos;
}
