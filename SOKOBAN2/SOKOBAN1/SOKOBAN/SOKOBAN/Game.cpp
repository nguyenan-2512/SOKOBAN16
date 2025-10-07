#include "Game.h"
#include <iostream>
using namespace std;

Game::Game() : window(sf::VideoMode(800, 600), "Sokoban"), currentMap(nullptr), gameState(GameState::MENU) {
    window.setFramerateLimit(60);

    if (!backgroundMusic.openFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\hi.ogg")) {
        cerr << "Failed to load background music!" << endl;
    }

    if (!moveSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\step.ogg")) {
        cerr << "Failed to load move sound!" << endl;
    }
    moveSound.setBuffer(moveSoundBuffer);

    if (!winSoundBuffer.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\win.ogg")) {
        cerr << "Failed to load win sound!" << endl;
    }
    winSound.setBuffer(winSoundBuffer);

    menu.loadResources();
    setupWinScreen();
}

Game::~Game() {
    cleanupGame();
}

void Game::setupWinScreen() {
    if (!winTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\win.jpg")) {
        cerr << "Failed to load win image!" << endl;
        winTexture.create(400, 300);
        sf::Uint8* pixels = new sf::Uint8[400 * 300 * 4];
        for (int i = 0; i < 400 * 300 * 4; i += 4) {
            pixels[i] = 0;       
            pixels[i + 1] = 255; 
            pixels[i + 2] = 0;   
            pixels[i + 3] = 255; 
        }
        winTexture.update(pixels);
        delete[] pixels;
    }

    winSprite.setTexture(winTexture);

    sf::FloatRect spriteBounds = winSprite.getLocalBounds();
    winSprite.setOrigin(spriteBounds.width / 2, spriteBounds.height / 2);
    winSprite.setPosition(400, 300);  

    winOverlay.setSize(sf::Vector2f(800, 600));
    winOverlay.setFillColor(sf::Color(0, 0, 0, 150));  
}

void Game::run() {
    backgroundMusic.setLoop(true);
    backgroundMusic.play();

    while (window.isOpen()) {
        handleEvents();
        update();
        render();
    }
}

void Game::handleEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (gameState == GameState::MENU) {
            menu.handleEvent(event, window);
        }
        else if (gameState == GameState::WIN) {
            // Xử lý sự kiện ở màn hình win
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    gameState = GameState::MENU;
                    menu.setState(MenuState::MENU);
                    cleanupGame();
                }
            }
        }
        else if (gameState == GameState::PLAYING) {
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape) {
                    gameState = GameState::MENU;
                    menu.setState(MenuState::MENU);
                    cleanupGame();
                }

                // XU LY PHIM U DE UNDO
                else if (event.key.code == sf::Keyboard::U) {
                    if (currentMap) {
                        currentMap->undo();
                        cout << "Undo! Con lai " << currentMap->getMoveCount() << " nuoc di." << endl;
                    }
                }

                else if (currentMap) {
                    bool moved = false;
                    if (event.key.code == sf::Keyboard::Up || event.key.code == sf::Keyboard::W) {
                        moved = currentMap->tryMovePlayer(0, -1);
                    }
                    else if (event.key.code == sf::Keyboard::Down || event.key.code == sf::Keyboard::S) {
                        moved = currentMap->tryMovePlayer(0, 1);
                    }
                    else if (event.key.code == sf::Keyboard::Left || event.key.code == sf::Keyboard::A) {
                        moved = currentMap->tryMovePlayer(-1, 0);
                    }
                    else if (event.key.code == sf::Keyboard::Right || event.key.code == sf::Keyboard::D) {
                        moved = currentMap->tryMovePlayer(1, 0);
                    }

                    if (moved) {
                        playMoveSound();

                        // KIỂM TRA THẮNG SAU MỖI NƯỚC ĐI
                        if (currentMap->checkWin()) {
                            cout << "Chuc mung! Ban da thang!" << endl;
                            gameState = GameState::WIN;
                            playWinSound();  // Phát âm thanh chiến thắng
                        }
                    }
                }
            }
        }
    }
}

void Game::playMoveSound() {
    moveSound.play();
}

void Game::playWinSound() {
    winSound.play();
}

void Game::update() {
    if (gameState == GameState::MENU) {
        menu.update();

        MenuState menuState = menu.getState();
        if (menuState == MenuState::PLAYING) {
            gameState = GameState::PLAYING;
            initializeGame();
        }
        else if (menuState == MenuState::EXIT) {
            window.close();
        }
    }
    else if (gameState == GameState::PLAYING) {
        // Có thể thêm logic update khác ở đây
    }
    else if (gameState == GameState::WIN) {
        // Có thể thêm animation win ở đây
    }
}

void Game::render() {
    window.clear();

    if (gameState == GameState::MENU) {
        menu.draw(window);
    }
    else if (gameState == GameState::PLAYING) {
        if (currentMap) {
            currentMap->draw(window);
        }
    }
    else if (gameState == GameState::WIN) {
        // Vẽ map phía sau
        if (currentMap) {
            currentMap->draw(window);
        }
        // Vẽ màn hình win lên trên
        drawWinScreen(window);
    }

    window.display();
}

void Game::drawWinScreen(sf::RenderWindow& window) {
    window.draw(winOverlay);  // Vẽ overlay tối
    window.draw(winSprite);    // Vẽ ảnh chiến thắng
}

void Game::initializeGame() {
    cleanupGame();
    currentMap = new Map("map1.txt", 32);
    cout << "Game initialized!" << endl;
}

void Game::cleanupGame() {
    if (currentMap) {
        delete currentMap;
        currentMap = nullptr;
    }
}