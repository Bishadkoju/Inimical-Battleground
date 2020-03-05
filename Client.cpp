#include "Client.h"

#include <iostream>
#include <fstream>
Client::Client() : listenThread(&Client::listen, this)
{
    std::string sIp;
    c_socket.bind(sf::Socket::AnyPort);
    std::cout << "Enter Server Ip: ";
    std::cin >> sIp;
    std::cout << sIp;
    sf::IpAddress send(sIp);
    serverIp = send;
}

Client::Client(sf::IpAddress l_ip) : listenThread(&Client::listen, this)
{
    c_socket.bind(sf::Socket::AnyPort);
    serverIp = l_ip;
    sendConnection();
}


void Client::sendConnection()
{
    sf::Packet packet;
    std::string test = "Connection Sent to Server\n";
    packet << test;
    c_socket.send(packet, serverIp, 8000);
}

void Client::send(sf::Packet packet)
{
    c_socket.send(packet, serverIp, 8000);
}
void Client::listen()
{
    int playerId;
    sf::Socket::Status value;
    sf::IpAddress tempip;
    unsigned short tempport;
    sf::Packet packet;
    while (1)
    {
        value = c_socket.receive(packet, tempip, tempport);
        if (value == 0)
        {
            packet >> a >> playerId;
        }
        if (playerId == 1)
        {
            pControls = reinterpret_cast<playerController*> (a);
        }
        else
        {
            eControls = reinterpret_cast<playerController*>(a);
        }
    }
}



void Client::thread()
{
    listenThread.launch();
}