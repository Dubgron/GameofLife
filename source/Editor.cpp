#include "Editor.h"


void Editor::edit(sf::RenderWindow &window, sf::Event &event, Map &map, int windowSize, std::string title) {

	info();
	window.create(sf::VideoMode(windowSize, windowSize), title, sf::Style::Close);

	// Coordinates of square on which a mouse indicates
	sf::Vector2i covered;

	while (window.isOpen()) {

		while (window.pollEvent(event)) {

			switch (event.type) { 

				case sf::Event::Closed:
					window.close();
					break;
				case sf::Event::KeyPressed:
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
						window.close();
					if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
						window.close();
						map.save();
						window.create(sf::VideoMode(windowSize, windowSize), title, sf::Style::Close);
					}
					break;			
			}
		}

		window.clear();

		covered = sf::Mouse::getPosition(window) / map.cellSize;

		if (covered.x >= 0 && covered.y >= 0 && covered.x < map.squaresAmount && covered.y < map.squaresAmount) {

			// Display coordinates
			//std::cout << covered.x << " " << covered.y << std::endl;

			if (!map.isAlive[covered.x][covered.y]) {

				map.statusChange(&map.squares[(covered.x + covered.y * map.squaresAmount) * 4], sf::Color(66, 209, 66));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {

					map.isAlive[covered.x][covered.y] = true;
				}
			}
			else {

				map.statusChange(&map.squares[(covered.x + covered.y * map.squaresAmount) * 4], sf::Color(216, 55, 55));
				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
				
					map.isAlive[covered.x][covered.y] = false;
				}
			}
		}

		window.draw(map.squares);

		for (int y = 0; y < map.squaresAmount; y++) {
			for (int x = 0; x < map.squaresAmount; x++) {

				map.statusChange(map.isAlive[x][y], x, y);
			}
		}

		window.display();
	}
}

void Editor::info() {

	system("cls");
	std::cout << "-= The Game of Life =-\n\n";
	std::cout << "Welcome! You're in the Conway's Game of Life's Editor!" << std::endl << std::endl;
	std::cout << "If you want to draw, press LMB." << std::endl;
	std::cout << "If you want to erase what you drew, press RMB." << std::endl;
	std::cout << "If you want to save your map, press S." << std::endl;
	std::cout << "If you want to start simulation, press ENTER." << std::endl;
}
