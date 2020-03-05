
#include<iostream>
#include "MainMenu.h"
#include"Networking.h"
#include "Connect.h"

int main()
{
MainMenu menu(800, 800);
menu.display();
//Game game(800, 800);
//	game.run();

	//Connect connect(800,800);
	//connect.run();
	return 0;
}

//int main(){
//
//	bool t1, t2, t3; float f1, f2;
//	std::cout << "Enter 3 bool,2 float\n";
//	std::cin >> t1 >> t2 >> t3 >> f1 >> f2;
//	Networking net;
//	
//	
//	if (net.isServer()) {
//		playerController player(true, true, t1,t2,t3, sf::Vector2f(f1, f2));
//		net.sendData(player);
//	}
//	if (net.isClient()) {
//		playerController p = net.getPlayerData();
//		std::cout << p.isPressedLeft << "\n" << p.isPressedRight << "\n" <<
//			p.isPressedUp << "\n" << p.isLeftMouseButtonPressed << "\n" <<
//			p.isRightMouseButtonPressed << "\n" <<
//			"MP: X:(" << p.mousePosition.x << " , " << p.mousePosition.y << ")\n";
//	}
//	system("pause");
//	return 0;
//}