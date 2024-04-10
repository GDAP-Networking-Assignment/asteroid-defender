#include "GameCore.h"

extern void GameRegisterClasses();

int main(int argc, char** argv)
{
	GameRegisterClasses();

	if (argc < 2) {
		int serverClientChoice = -1;
		std::cout << "Server [0] or Client [1]: ";
		std::cin >> serverClientChoice;
		Engine::Instance().Initialize(serverClientChoice);
	}
	else {
		Engine::Instance().Initialize(std::stoi(argv[1]));
	}
	Engine::Instance().GameLoop();
	Engine::Instance().Destroy();

	return 0;
}
