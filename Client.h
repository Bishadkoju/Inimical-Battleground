#pragma once
#include <SFML/Network.hpp>
#include "playerController.h"
class Client
{
public:
	Client();
	Client(sf::IpAddress);
	void listen();
	void send(sf::Packet);
	void thread();
	/*sf::Vector2f getPosition(int);
	float getDirection(int);
	unsigned int getHealth(int);
	bool isShooting(int);*/
	void sendConnection();
	sf::UdpSocket c_socket;
	playerController* pControls;
	playerController* eControls;
private:
	char* a;
	int playerId;
	bool readytoplay = false;
	
	sf::IpAddress serverIp;
	sf::Thread listenThread;
	unsigned short port;
};

