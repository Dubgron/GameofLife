#include "Map.h"


void MapData::set(int squaresAmount, int windowSize, bool isInfinite) {

	this->squaresAmount = squaresAmount;
	this->isInfinite = isInfinite;
	cellSize = windowSize / squaresAmount;

	squares = new sf::RectangleShape*[squaresAmount];
	isAlive = new bool*[squaresAmount];
	willBeAlive = new bool*[squaresAmount];

	for (int x = 0; x < squaresAmount; x++) {

		squares[x] = new sf::RectangleShape[squaresAmount];
		isAlive[x] = new bool[squaresAmount];
		willBeAlive[x] = new bool[squaresAmount];
		
		for (int y = 0; y < squaresAmount; y++) {

			squares[x][y].setPosition(sf::Vector2f(x * (float)cellSize, y * (float)cellSize));
			squares[x][y].setSize(sf::Vector2f((float)cellSize, (float)cellSize));
			squares[x][y].setFillColor(sf::Color::Black);
			isAlive[x][y] = false;
			
		}
	}
}

void MapData::draw(sf::RenderWindow &window) {

	for (int y = 0; y < squaresAmount; y++)
		for (int x = 0; x < squaresAmount; x++)
			if (isAlive[x][y]) window.draw(squares[x][y]);
}

void MapData::loadMap() {

	do {

		system("cls");
		std::cout << "-= The Game of Life =-" << std::endl << std::endl;

		loadList();
		showList();

		std::cout << "Choose map from list above: ";
		std::cin >> iPath;

		std::cout << list[0] << std::endl;
		std::cout << list[iPath - 1] << std::endl;

		file.open("maps/" + list[iPath - 1] + ".txt", std::ios::in);

		file.good() ? system("cls") : loadError();
		
	} while (!file.good());

	std::string lineContent;
	int lineXCounter = 0;
	int lineYCounter = 0;

	while (std::getline(file, lineContent)) {

		for (lineXCounter = 0; lineXCounter < squaresAmount; lineXCounter++) {

			isAlive[lineXCounter][lineYCounter] = (lineContent[lineXCounter] == '1' ? true : false);
		}
		lineXCounter = 0;
		lineYCounter++;
	}

	file.close();
}

void MapData::save() {

	system("cls");
	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "Title of map: ";
	std::cin >> sPath;

	file.open("maps/" + sPath + ".txt", std::ios::out);
	
	for (int y = 0; y < squaresAmount; y++) {
		for (int x = 0; x < squaresAmount; x++) {

			file << isAlive[x][y];
		}
		file << "\n";
	}

	file.close();

	file.open("maps/List.txt", std::ios::out);

	file << sPath << "\n";
	
	file.close();
}

void MapData::loadList() {

	file.open("maps/List.txt", std::ios::in);

	std::string lineContent;

	while (std::getline(file, lineContent)) 
		list.push_back(lineContent);

	file.close();
}

void MapData::showList() {

	int i = 1;

	for (std::vector<std::string>::const_iterator iterator = list.begin(); iterator != list.end(); iterator++) {

		std::cout << i << ". " << *iterator << std::endl;
		i++;
	}
	std::cout << "\n";
}

void MapData::loadError() {

	std::cout << "\nError! File doesn't exist!";
	file.close();
	_getch();
}
