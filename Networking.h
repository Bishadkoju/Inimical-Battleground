#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
#include<SFML/Network.hpp>
#include<string>
class Networking
{
private:
	sf::IpAddress ip;
	sf::TcpSocket socket;
	sf::Packet pack;
	char connectionType{};
	int portNumber;


public:
	Networking()
	{
		ip = sf::IpAddress::getLocalAddress();
		setServer();
		portNumber = 2000;
	}
	void setServer()
	{
		std::string text = "Connected to:";
		std::cout << "Enter (S) for Server , Enter(C)for client:" << std::endl;
		std::cin >> connectionType;

		if (connectionType == 'S' || connectionType == 's')
		{
			sf::TcpListener listener;
			listener.listen(portNumber);
			if (listener.accept(socket) != sf::Socket::Done)
			{
				std::cerr << "Error while connecting:";

			}
			text += "Server\n";
			std::cout << text;
		}
		if (connectionType == 'C' || connectionType == 'c')
		{
			socket.connect(ip, portNumber);
			text += "Client\n";
			std::cout << text;
		}

	}
	bool isServer()
	{
		if (connectionType == 's' || connectionType == 'S')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	bool isClient()
	{
		if (connectionType == 'c' || connectionType == 'C')
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void sendData(std::string sender)
	{
		pack << sender;
		socket.send(pack);
	}
	void sendData(int sender)
	{
		pack << sender;
		socket.send(pack);
	}
	void sendData(float sender)
	{
		pack << sender;
		socket.send(pack);
	}
	void sendData(sf::Vector2f sender)
	{
		pack << sender.x << sender.y;
		socket.send(pack);
	}
	
	void sendData(playerController controller) {
	    
		pack << controller.isPressedLeft << controller.isPressedRight << controller.isPressedUp <<
			controller.isLeftMouseButtonPressed << controller.isRightMouseButtonPressed <<
			controller.mousePosition.x << controller.mousePosition.y;
		socket.send(pack);
	}
	playerController getPlayerData() {
		socket.receive(pack);
		bool isPressedLeft, isPressedRight, isPressedUp;
		bool isLeftMouseButtonPressed, isRightMouseButtonPressed;
		sf::Vector2f mousePosition;
		pack >> isPressedLeft >> isPressedRight >> isPressedUp >> isLeftMouseButtonPressed
			>> isRightMouseButtonPressed >> mousePosition.x >> mousePosition.y;

		return playerController( isPressedLeft,  isPressedRight, isPressedUp, isLeftMouseButtonPressed, 
			 isRightMouseButtonPressed, sf::Vector2f(mousePosition.x,mousePosition.y));
	}
	std::string getStringdata()
	{
		socket.receive(pack);
		//pack.getData();
		std::string getdata;
		pack >> getdata;
		return getdata;
	}
	int getIntdata()
	{
		socket.receive(pack);
		//pack.getData();
		int getdata;
		pack >> getdata;
		//std::cout << getdata;
		return getdata;
	}
	float getFloatdata()
	{
		socket.receive(pack);
		//pack.getData();
		float getdata;
		pack >> getdata;
		return getdata;
	}
	sf::Vector2f getVectordata()
	{
		float x1, y1;
		socket.receive(pack);
		//pack.getData();
		pack >> x1 >> y1;
		return sf::Vector2f(x1, y1);
	}

	sf::Packet getData()
	{
		socket.receive(pack);
		return pack;
	}
};







