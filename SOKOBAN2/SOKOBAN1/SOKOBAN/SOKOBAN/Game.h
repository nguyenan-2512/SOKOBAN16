#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp> 
#include "Menu.h"
#include "Map.h"

enum class GameState {
    MENU,
    PLAYING,
    PAUSED,
    GAME_OVER,
    WIN
};

class Game {
private:
    sf::RenderWindow window;
    Menu menu;
    Map* currentMap;
    GameState gameState;
    sf::Music backgroundMusic; 
    sf::SoundBuffer moveSoundBuffer; 
    sf::Sound moveSound;
    sf::SoundBuffer winSoundBuffer;  
    sf::Sound winSound;
    sf::Texture winTexture;
    sf::Sprite winSprite;
    sf::RectangleShape winOverlay; 

public:
    Game();
    ~Game();
    void run();

private:
    void handleEvents();
    void update();
    void render();
    void initializeGame();
    void cleanupGame();
    void playMoveSound();
    void setupWinScreen();  
    void drawWinScreen(sf::RenderWindow& window);
};