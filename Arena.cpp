#include "Arena.h"

Arena::Arena()
{
	limit_box.setPosition(0, 0);
	limit_box.setSize(sf::Vector2f(1700, 1000));
	textureBackImag.loadFromFile("pic/newarena.png");
	spriteBackGroundImage.setTexture(textureBackImag);
	spriteBackGroundImage.scale(2,1.3);
	/*direction[0] = sf::Vector2f(0, step);
	direction[1] = sf::Vector2f(step, step);
	direction[2] = sf::Vector2f(step, 0);
	direction[3] = sf::Vector2f(step, -step);
	direction[4] = sf::Vector2f(0, -step);
	direction[5] = sf::Vector2f(-step, -step);
	direction[6] = sf::Vector2f(-step,0);
	direction[7] = sf::Vector2f(-step, step);*/
	direction.push_back(sf::Vector2f(0, step));
	direction.push_back(sf::Vector2f(step, 0));
	direction.push_back(sf::Vector2f(0, -step));
	direction.push_back(sf::Vector2f(-step, 0));

	for (int i = 0; i < noOfBlocks; i++)
	{
		blocks[i].setFillColor(sf::Color::Transparent);
		blocks[i].setSize(sizes[i]);
		blocks[i].setPosition(positions[i]);
	}

	startingNode=createNode(sf::Vector2f(100, 100));
	node_object.push_back(startingNode);
	generateNode(startingNode);
}

void Arena::draw(sf::RenderWindow& window)
{
	window.draw(spriteBackGroundImage);
	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		mp.x = sf::Mouse::getPosition().x;
		mp.y = sf::Mouse::getPosition().y;
		std::cout << "(" << mp.x << "," << mp.y << ")" << std::endl;
	}*/
	for (const auto block : blocks) {
		window.draw(block);
	}
	for (const auto node : node_object)
	{
		node->draw(window);
	}
	for (const auto node : node_object)
	{
		for (const auto neighbour : node->neighbours)
		{
			if (getNodeById(neighbour))
			{
				sf::Vertex line[]{
						sf::Vertex(node->getPosition()),
						sf::Vertex(getNodeById(neighbour)->getPosition())
				};
				window.draw(line, 2, sf::Lines);
			}
		}
	}
}

bool Arena::is_freespace(sf::Vector2f position)
{
	if (!limit_box.getGlobalBounds().contains(position))
	{
		return false;
	}
	for (const auto block : blocks)
	{
		if (block.getGlobalBounds().contains(position))
		{
			return false;
		}
	}
	return true;
}

bool Arena::nodeExists(sf::Vector2f position)
{
	for (auto node : node_object)
	{
		if (node->getPosition()==position)
		{
			return true;
		}
	}
	return false;
}

Nodes* Arena::getnode(sf::Vector2f position)
{
	for (auto node : node_object)
	{
		if (node->getPosition() == position)
		{
			return node;
		}
	}
	return NULL;
}

void Arena::generateNode(Nodes* self)
{
	sf::Vector2f projectedCoord;
	Nodes* neighbour,*newNode;
	for (int i = 0; i < direction.size(); i++)
	{
		projectedCoord = self->getPosition()+direction[i];
		if (nodeExists(projectedCoord))
		{
			neighbour=getnode(projectedCoord);
			if (neighbour)
			{
				neighbour->add_to_neighbours(self->getId());
				self->add_to_neighbours(neighbour->getId());
			}
		}
		else
		{
			if (is_freespace(projectedCoord))
			{
				newNode = createNode(projectedCoord);
				node_object.push_back(newNode);
				generateNode(newNode);
			}
		}
	}
}

Nodes* Arena::createNode(sf::Vector2f position)
{
	Nodes* node = new Nodes(position);
	node->body.setOutlineColor(sf::Color::Blue);
	node->body.setOutlineThickness(1);
	node->body.setRadius(2);
	return node;
}

Nodes* Arena::getNodeById(int id)
{
	for (auto node : node_object)
	{
		if (node->getId() == id)
		{
			return node;
		}
	}
	return NULL;
}
