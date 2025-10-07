#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

enum class MenuState {
    MENU,
    PLAYING,
    EXIT
};

class Menu {
private:
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;
    sf::Font font;
    std::vector<sf::Text> menuItems;
    sf::RectangleShape playButton;
    sf::RectangleShape exitButton;
    sf::Text playText;
    sf::Text exitText;
    int selectedItem;
    MenuState currentState;

public:
    Menu();
    ~Menu();
    bool loadResources();
    void handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void update();
    void draw(sf::RenderWindow& window);
    MenuState getState() const;
    void setState(MenuState state);
    void reset();
private:
    void setupButtons();
    void setupTexts();
    bool isMouseOverButton(const sf::RectangleShape& button, sf::Vector2i mousePos);
};