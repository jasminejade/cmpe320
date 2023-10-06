#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>

#include "Animation.h"
#include "Player.h"
#include "Terrain.h"

static const float VIEW_HEIGHT = 720;

void resizeWindow(const RenderWindow& window, View& view) {
	float aspectRatio = float(window.getSize().x / float(window.getSize().y));
	view.setSize(VIEW_HEIGHT * aspectRatio, VIEW_HEIGHT);
}

int main() {
	// create window that is 800 by 800 pixels 
	RenderWindow window(VideoMode(768, 720), "Surviving Frosh Week");
	View view(Vector2f(0.0f, 0.0f), Vector2f(768, 720));

	// create player & enemy (car)
	Texture playerTexture, enemyTexture, box1Tex, box2Tex, frecTexture, 
		greasePoleTexture;
	playerTexture.loadFromFile("images/moving_player.png");
	enemyTexture.loadFromFile("images/carSprite.png");
	frecTexture.loadFromFile("images/cloakedFrecs.png");
	greasePoleTexture.loadFromFile("images/grease_pole.png");

	float enemY = 0.33 * 720;
	vector<Vector2f> enemyPos = { Vector2f(700, enemY), Vector2f(1000, enemY), Vector2f(1500,enemY), Vector2f(2100, enemY)};
	Vector2f enemySize(200, 80);

	Player player(&playerTexture, Vector2u(2, 1), 0.3f, 500.0f, 10); 
	Enemy enemy1(&enemyTexture, enemyPos[0], enemySize, Vector2u(1, 1), 0.3f, 500.0f, "smart", 20);
	Enemy enemy2(&enemyTexture, enemyPos[1], enemySize, Vector2u(1, 1), 0.3f, 500.0f, "smart", 20);
	Enemy enemy3(&enemyTexture, enemyPos[2], enemySize, Vector2u(1, 1), 0.3f, 500.0f, "smart", 20);
	Enemy enemy4(&enemyTexture, enemyPos[3], enemySize, Vector2u(1, 1), 0.3f, 500.0f, "smart", 20);
	
	// terrain setup
	box1Tex.loadFromFile("images/box_terrain.png");
	box2Tex.loadFromFile("images/brick_terrain.png");
	Finish finish(&greasePoleTexture, Vector2f(2500.0f, 0.22f * 720), Vector2f(175.0f, 280.0f));

	// JAMES START
	//barrel stack
	Terrain box1(&box1Tex, Vector2f(-2000, 215), Vector2f(100, 100));
	Terrain box2(&box1Tex, Vector2f(-1900, 215), Vector2f(100, 100));
	Terrain box3(&box1Tex, Vector2f(-1900, 115), Vector2f(100, 100));
	Terrain box4(&box1Tex, Vector2f(-1800, 115), Vector2f(100, 100));
	Terrain box5(&box1Tex, Vector2f(-1800, 15), Vector2f(100, 100));
	Terrain box6(&box1Tex, Vector2f(-1500, 215), Vector2f(100, 100));

	//frec after barrel stack
	Frec frecBarrel(&frecTexture, Vector2f(-1600, 0.28f * 720.0), Vector2f(175.0f, 190.0f));
	//frec under platforms
	Frec frecPlat(&frecTexture, Vector2f(-700, 0.28f * 720.0), Vector2f(175.0f, 190.0f));
	//frec on edge of map
	Frec frecEdge(&frecTexture, Vector2f(-2500.0f, 0.28f * 720.0), Vector2f(175.0f, 190.0f));

	//platforms
	Terrain plat1(&box2Tex, Vector2f(-1300, 100), Vector2f(80, 40));
	Terrain plat2(&box2Tex, Vector2f(-1220, 100), Vector2f(80, 40));
	Terrain plat3(&box2Tex, Vector2f(-1000, 100), Vector2f(80, 40));
	Terrain plat4(&box2Tex, Vector2f(-800, -50), Vector2f(80, 40));

	// array of all nonplayer entities
	vector<Entity*> items = {&enemy1, &enemy2, &enemy3, &enemy4,
		&box1, &box2, &box3, &box4, &box5, &box6,
		&plat1, &plat2, &plat3, &plat4,
		&frecBarrel, &frecPlat, &frecEdge, &finish, };

	vector<Enemy*> villains = { &enemy1, &enemy2, &enemy3, &enemy4, };

	vector<Entity*> checkLoss = { &enemy1, &enemy2, &enemy3, &enemy4,
		&frecBarrel, &frecPlat, &frecEdge };

	// setup title screen
	Texture titleScreen, levelEndScreen, gameOverScreen;
	titleScreen.loadFromFile("images/title_screen.png");
	levelEndScreen.loadFromFile("images/level_complete.png");
	gameOverScreen.loadFromFile("images/game_over.png");
	Sprite titleSprite, levelEndSprite, gameOverSprite;
	Vector2u titleSize = titleScreen.getSize();
	Vector2u endLevelSize = titleSize;

	titleSprite.setTexture(titleScreen);
	levelEndSprite.setTexture(levelEndScreen);
	gameOverSprite.setTexture(gameOverScreen);
	titleSprite.setOrigin(titleSize.x / 2.0f, titleSize.y / 2.0f);
	levelEndSprite.setOrigin(titleSize.x / 2.0f, titleSize.y / 2.0f);
	gameOverSprite.setOrigin(titleSize.x / 2.0f, titleSize.y / 2.0f);

	// setup level screen
	Texture backgroundTexture;
	backgroundTexture.loadFromFile("images/longer_stage.png");
	Sprite backgroundSprite;
	Vector2u backgroundSize = backgroundTexture.getSize();
	backgroundSprite.setTexture(backgroundTexture);
	backgroundSprite.setOrigin(backgroundSize.x / 2.0f, backgroundSize.y / 2.0f);

	int gameState = 0;
	float dt = 0.0f;
	Clock clock;

	// main game loop
	while (window.isOpen()) {

		dt = 0.7 * clock.restart().asSeconds();

		Event event;
		
		while (window.pollEvent(event)) {
			switch (event.type) {
			case Event::Closed:
				window.close();
				break;
			case Event::Resized:
				resizeWindow(window, view);
				break;
			case Event::MouseButtonPressed:
				gameState = 1;
				break;
			}
		}

		if (gameState == 0) { // title screen
			window.clear();
			view.setCenter(0, 0);
			window.setView(view);
			window.draw(titleSprite);
		}
		else { // level screen
			window.clear(Color::White);

			player.update(dt, items);
			for (Enemy *i : villains) {
				i->update(dt, player.getPosition(), window.getSize().x);
			}
			//enemy.update(dt, player.getPosition(), window.getSize().x);

			view.setCenter(player.getPosition().x, 0);
			window.setView(view);
			window.draw(backgroundSprite);

			player.draw(window);
			for (int i = 0; i < items.size(); i++) {
				items[i]->draw(window);
			}
			
			if (player.hCollide(finish) != 0 || player.vCollide(finish) != 0) {
				Time delay = seconds(2);
				sleep(delay);
				window.clear();
				view.setCenter(0, 0);
				window.setView(view);
				window.draw(levelEndSprite);
				window.display();
				sleep(delay);
				/*gamestate = 0;
				window.close();
				player.~player();*/
				//main();
				return 0;
			}
			else {
				for (int i = 0; i < checkLoss.size(); i++) {
					Entity* e = checkLoss[i];
					if (player.hCollide(*e) != 0 || player.vCollide(*e) != 0) {
						Time delay = seconds(2);
						sleep(delay);
						window.clear();
						view.setCenter(0, 0);
						window.setView(view);
						window.draw(gameOverSprite);
						window.display();
						sleep(delay);
						return 0;
					}
				}
			}

		}

		window.display();
	}
	return 0;

}