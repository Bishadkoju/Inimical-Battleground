#include "Graph.h"

bool Graph::is_freespace(sf::Vector2f position, sf::RectangleShape blocks[])
{
    sf::RectangleShape limit_box;
    limit_box.setPosition(0, 0);
    limit_box.setSize(sf::Vector2f(1700,1000));
    if (!limit_box.getGlobalBounds().contains(position))
    {
        return false;
    }
    for (const auto block : blocks)
    {

    }
}
