#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() : selectedItem(0), currentState(MenuState::MENU) {
}

Menu::~Menu() {
}

bool Menu::loadResources() {
    // Load background texture
    if (!backgroundTexture.loadFromFile("D:\\PBL2\\SOKOBAN1\\SOKOBAN\\SOKOBAN\\images\\Menu (2).jpg")) {
        std::cerr << "Failed to load menu background texture!" << std::endl;
        // Create a default colored background if image fails to load
        backgroundTexture.create(800, 600);
        sf::Uint8* pixels = new sf::Uint8[800 * 600 * 4];
        for (int i = 0; i < 800 * 600 * 4; i += 4) {
            pixels[i] = 50;     // R
            pixels[i + 1] = 80;  // G
            pixels[i + 2] = 120; // B
            pixels[i + 3] = 255; // A
        }
        backgroundTexture.update(pixels);
        delete[] pixels;
    }
    backgroundSprite.setTexture(backgroundTexture);

    // Scale background to fit window exactly (800x600)
    sf::Vector2u textureSize = backgroundTexture.getSize();
    if (textureSize.x > 0 && textureSize.y > 0) {
        float scaleX = 800.0f / textureSize.x;
        float scaleY = 600.0f / textureSize.y;
        backgroundSprite.setScale(scaleX, scaleY);
    }

    // Load font (you can use default font for now)
    // If you have a font file, replace this path
    if (!font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
        // If system font fails, try to use default font
        std::cerr << "Failed to load font, using default font" << std::endl;
    }

    setupButtons();
    setupTexts();

    return true;
}

void Menu::setupButtons() {
    // Setup Play button (move higher to avoid text overlap)
    playButton.setSize(sf::Vector2f(200, 60));
    playButton.setPosition(300, 200);  // Changed from 300 to avoid overlap
    playButton.setFillColor(sf::Color(70, 130, 180, 200)); // Add transparency
    playButton.setOutlineThickness(3);
    playButton.setOutlineColor(sf::Color::White);

    // Setup Exit button
    exitButton.setSize(sf::Vector2f(200, 60));
    exitButton.setPosition(300, 300);  // Changed from 400 to avoid overlap
    exitButton.setFillColor(sf::Color(180, 70, 70, 200)); // Add transparency
    exitButton.setOutlineThickness(3);
    exitButton.setOutlineColor(sf::Color::White);
}

void Menu::setupTexts() {
    // Play button text
    playText.setFont(font);
    playText.setString("PLAY");
    playText.setCharacterSize(24);
    playText.setFillColor(sf::Color::White);
    playText.setStyle(sf::Text::Bold);

    // Center text in button (updated position)
    sf::FloatRect playBounds = playText.getLocalBounds();
    playText.setPosition(400 - playBounds.width / 2, 215);

    // Exit button text
    exitText.setFont(font);
    exitText.setString("EXIT");
    exitText.setCharacterSize(24);
    exitText.setFillColor(sf::Color::White);
    exitText.setStyle(sf::Text::Bold);

    // Center text in button (updated position)
    sf::FloatRect exitBounds = exitText.getLocalBounds();
    exitText.setPosition(400 - exitBounds.width / 2, 315);
}

void Menu::handleEvent(const sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);

            if (isMouseOverButton(playButton, mousePos)) {
                currentState = MenuState::PLAYING;
            }
            else if (isMouseOverButton(exitButton, mousePos)) {
                currentState = MenuState::EXIT;
            }
        }
    }

    // Handle keyboard input
    if (event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
        case sf::Keyboard::Up:
            selectedItem = (selectedItem - 1 + 2) % 2;
            break;
        case sf::Keyboard::Down:
            selectedItem = (selectedItem + 1) % 2;
            break;
        case sf::Keyboard::Enter:
            if (selectedItem == 0) {
                currentState = MenuState::PLAYING;
            }
            else {
                currentState = MenuState::EXIT;
            }
            break;
        case sf::Keyboard::Escape:
            currentState = MenuState::EXIT;
            break;
        }
    }

    // Handle mouse hover effects
    if (event.type == sf::Event::MouseMoved) {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);

        // Handle mouse hover effects
        if (isMouseOverButton(playButton, mousePos)) {
            selectedItem = 0;
            playButton.setFillColor(sf::Color(100, 160, 210, 200));
        }
        else {
            playButton.setFillColor(sf::Color(70, 130, 180, 200));
        }

        if (isMouseOverButton(exitButton, mousePos)) {
            selectedItem = 1;
            exitButton.setFillColor(sf::Color(210, 100, 100, 200));
        }
        else {
            exitButton.setFillColor(sf::Color(180, 70, 70, 200));
        }
    }
}

void Menu::update() {
    // Update button colors based on selection
    if (selectedItem == 0) {
        playButton.setFillColor(sf::Color(100, 160, 210, 200));
        exitButton.setFillColor(sf::Color(180, 70, 70, 200));
    }
    else {
        playButton.setFillColor(sf::Color(70, 130, 180, 200));
        exitButton.setFillColor(sf::Color(210, 100, 100, 200));
    }
}

void Menu::draw(sf::RenderWindow& window) {
    // Draw background
    window.draw(backgroundSprite);

    // Draw buttons
    window.draw(playButton);
    window.draw(exitButton);

    // Draw button texts
    window.draw(playText);
    window.draw(exitText);
}

MenuState Menu::getState() const {
    return currentState;
}

void Menu::setState(MenuState state) {
    currentState = state;
}

void Menu::reset() {
    currentState = MenuState::MENU;
    selectedItem = 0;
}

bool Menu::isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos) {
    sf::FloatRect buttonBounds = button.getGlobalBounds();
    return buttonBounds.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y));
}