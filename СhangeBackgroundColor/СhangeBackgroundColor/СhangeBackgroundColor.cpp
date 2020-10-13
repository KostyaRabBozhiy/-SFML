#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <chrono>
#include <sstream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <list>

using namespace std;
using namespace sf;

int main(){
	setlocale(0, "ru");
	const unsigned int scrW = 800, scrH = 800, CC_RGB_max = 200, CC_RGB_min = 50;
	const unsigned int CCR_Y = 62, CCG_Y = 107, CCB_Y = 152;
	int R = 255, G = 255, B = 255;
	int mouseAt = 0;
	RenderWindow window(VideoMode(scrW,scrH), "ChangerBackgroundColor", Style::Default);

	//R
	Vertex changeLine_R[] = {
		Vertex(Vector2f(50,50),Color(0,0,0)),
		Vertex(Vector2f(50,75),Color(0,0,0)),
		Vertex(Vector2f(200,75),Color(255,0,0)),
		Vertex(Vector2f(200,50),Color(255,0,0))
	};
	CircleShape changeCircle_R;
	changeCircle_R.setRadius(13);
	changeCircle_R.setOrigin(Vector2f(13,13));
	changeCircle_R.setFillColor(Color(170, 170, 170));
	changeCircle_R.setOutlineThickness(5);
	changeCircle_R.setOutlineColor(Color(100, 100, 100));
	changeCircle_R.setPosition(Vector2f(CC_RGB_max,CCR_Y));

	//G
	Vertex changeLine_G[] = {
		Vertex(Vector2f(50,95),Color(0,0,0)),
		Vertex(Vector2f(50,120),Color(0,0,0)),
		Vertex(Vector2f(200,120),Color(0,255,0)),
		Vertex(Vector2f(200,95),Color(0,255,0))
	};
	CircleShape changeCircle_G;
	changeCircle_G.setRadius(13);
	changeCircle_G.setOrigin(Vector2f(13, 13));
	changeCircle_G.setFillColor(Color(170, 170, 170));
	changeCircle_G.setOutlineThickness(5);
	changeCircle_G.setOutlineColor(Color(100, 100, 100));
	changeCircle_G.setPosition(Vector2f(CC_RGB_max, CCG_Y));

	//B
	Vertex changeLine_B[] = {
		Vertex(Vector2f(50,140),Color(0,0,0)),
		Vertex(Vector2f(50,165),Color(0,0,0)),
		Vertex(Vector2f(200,165),Color(0,0,255)),
		Vertex(Vector2f(200,140),Color(0,0,255))
	};
	CircleShape changeCircle_B;
	changeCircle_B.setRadius(13);
	changeCircle_B.setOrigin(Vector2f(13, 13));
	changeCircle_B.setFillColor(Color(170, 170, 170));
	changeCircle_B.setOutlineThickness(5);
	changeCircle_B.setOutlineColor(Color(100, 100, 100));
	changeCircle_B.setPosition(Vector2f(CC_RGB_max, CCB_Y));

	Clock clock;

	while (window.isOpen()) {

		Event event;
		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) { window.close(); }
			if (event.type == Event::Resized) { window.setSize(Vector2u(scrW, scrH)); }
		}

		Vector2i pixelPos = Mouse::getPosition(window);
		Vector2f pos_cr = window.mapPixelToCoords(pixelPos);

		if (IntRect(50, 50, 150, 25).contains(Mouse::getPosition(window))) { mouseAt = 1; }
		if (IntRect(50, 95, 150, 25).contains(Mouse::getPosition(window))) { mouseAt = 2; }
		if (IntRect(50, 140, 150, 25).contains(Mouse::getPosition(window))) { mouseAt = 3; }

		if (Mouse::isButtonPressed(Mouse::Left)) {
			if (mouseAt == 1) {
				if (pos_cr.x >= 200) { changeCircle_R.setPosition(Vector2f(CC_RGB_max, CCR_Y)); R = 255;}
				else if (pos_cr.x <= 50) { changeCircle_R.setPosition(Vector2f(CC_RGB_min, CCR_Y)); R = 0; }
				else { 
					changeCircle_R.setPosition(Vector2f(pos_cr.x, CCR_Y)); 
					R = float(1.7 * (pos_cr.x - 50));
				}
			}
			if (mouseAt == 2) {
				if (pos_cr.x >= 200) { changeCircle_G.setPosition(Vector2f(CC_RGB_max, CCG_Y)); G = 255; }
				else if (pos_cr.x <= 50) { changeCircle_G.setPosition(Vector2f(CC_RGB_min, CCG_Y)); G = 0; }
				else { 
					changeCircle_G.setPosition(Vector2f(pos_cr.x, CCG_Y)); 
					G = float(1.7 * (pos_cr.x - 50));
				}
			}
			if (mouseAt == 3 ) {
				if (pos_cr.x >= 200) { changeCircle_B.setPosition(Vector2f(CC_RGB_max, CCB_Y)); B = 255; }
				else if (pos_cr.x <= 50) { changeCircle_B.setPosition(Vector2f(CC_RGB_min, CCB_Y)); B = 0; }
				else { 
					changeCircle_B.setPosition(Vector2f(pos_cr.x, CCB_Y)); 
					B = float(1.7 * (pos_cr.x - 50));
				}
			}
		}
		else {
			mouseAt = 0;
		}

		float timeFloat = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		timeFloat /= 1000;

		window.clear(Color(R,G,B));

		window.draw(changeLine_R, 4, Quads);
		window.draw(changeCircle_R);

		window.draw(changeLine_G, 4, Quads);
		window.draw(changeCircle_G);

		window.draw(changeLine_B, 4, Quads);
		window.draw(changeCircle_B);

		window.display();
	}

	cout << "Я люблю Ольгу Фугу!!" << endl;

	return 0;
}