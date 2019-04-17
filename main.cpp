
#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "ResourcePath.hpp"


int main()
{
    srand( time( NULL ) );
    sf::Vector2f windowSize(800,600);
    
    
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML window");

    window.setFramerateLimit(15);
    
    sf::Image icon;
    if (!icon.loadFromFile(resourcePath() + "icon.png")) {
        return EXIT_FAILURE;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

    sf::Texture appleTexture;
    
    if (!appleTexture.loadFromFile(resourcePath() + "apple.png")) {
        return EXIT_FAILURE;
    }
    
    
    sf::Texture bcgTexture;
    if (!bcgTexture.loadFromFile(resourcePath() + "backGround.jpg")) {
        return EXIT_FAILURE;
    }
    sf::Sprite sprite(bcgTexture);

    sprite.setScale(windowSize.x/1280, windowSize.y/960);
    sf::Font font;
    if (!font.loadFromFile(resourcePath() + "sansation.ttf")) {
        return EXIT_FAILURE;
    }
    sf::Text score("", font, 100);
    score.setFillColor(sf::Color::White);
    score.setPosition(10, 25);
    
    sf::Music music;
    if (!music.openFromFile(resourcePath() + "nice_music.ogg")) {
        return EXIT_FAILURE;
    }
    
    sf::RectangleShape apple;
    apple.setSize(sf::Vector2f(25,25));
//    apple.setFillColor(sf::Color::Red);
    sf::Vector2f applePosition;
    applePosition.x = (std::rand() % (int)windowSize.x-(int)apple.getSize().x ) + 0;
    applePosition.y = (std::rand() % (int)windowSize.y-(int)apple.getSize().y ) + 0;
    applePosition.x = (int)applePosition.x - (int)applePosition.x % 25;
    applePosition.y = (int)applePosition.y - (int)applePosition.y % 25;
    apple.setPosition(applePosition);
    apple.setTexture(&appleTexture);
    
    const int snakeMaxSize = 255;
    sf::RectangleShape snake[snakeMaxSize]; //MAY CHANGE TO VECTOR BUT IDK
    for(int l = 0; l < snakeMaxSize; ++l)
    {
        
        snake[l].setSize(sf::Vector2f(25,25));
        snake[l].setFillColor(sf::Color::Green);
        snake[l].setPosition(-100, -100);
        snake[0].setPosition(windowSize.x/2,windowSize.y/2);
        snake[l].setOutlineThickness(1);
        snake[l].setOutlineColor(sf::Color::Black);
        
    }

    int snakeLength = 2;
    bool snakeAteApple = false;
    sf::Vector2f snakePosition;
    
    sf::Vector2f snakeMove(0,0);
    

    
    while (window.isOpen())
    {
        
        
        sf::Event event;
        while (window.pollEvent(event))
        {
            
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Q) {
                window.close();
            }
            
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Up) {
                if(snakeMove.y == 0)snakeMove = sf::Vector2f(0,-25);
            }
            
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Down) {
                if(snakeMove.y == 0)snakeMove = sf::Vector2f(0, 25);
            }
            
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Right) {
                if(snakeMove.x == 0)snakeMove = sf::Vector2f(25, 0);
            }
            
            else if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Left) {
                if(snakeMove.x == 0)snakeMove = sf::Vector2f(-25, 0);
            }
            
        
        }
        
        
        snake[0].setPosition(snake[0].getPosition().x + snakeMove.x, snake[0].getPosition().y + snakeMove.y);
        snakePosition = snake[0].getPosition();
        
        if(snakePosition == applePosition) snakeAteApple = true;
        
        if(snakeAteApple)
        {
            applePosition.x = (std::rand() % (int)windowSize.x-(int)apple.getSize().x ) + 25;
            applePosition.y = (std::rand() % (int)windowSize.y-(int)apple.getSize().y ) + 25;
            applePosition.x = (int)applePosition.x - (int)applePosition.x % 25;
            applePosition.y = (int)applePosition.y - (int)applePosition.y % 25;
            apple.setPosition(applePosition);
            snakeLength++;
            snakeAteApple = false;
        }
        //Collisions
        if(snakePosition.x > windowSize.x-snake[0].getSize().x)
        {
            snake[0].setPosition(0, snakePosition.y);
        }
        if(snakePosition.x < 0)
        {
            snake[0].setPosition(windowSize.x-snake[0].getSize().x, snakePosition.y);
        }
        if(snakePosition.y < 0)
        {
            snake[0].setPosition(snakePosition.x, windowSize.y-snake[0].getSize().y);
        }
        if(snakePosition.y > windowSize.y-snake[0].getSize().x)
        {
            snake[0].setPosition(snakePosition.x, 0);
        }
        
        for(int l = snakeLength-1; l > 0; --l)
        {
            snake[l].setPosition(snake[l-1].getPosition());
        }
        for(int l = 3; l < snakeLength; ++l)     if(snake[0].getPosition() == snake[l].getPosition()) window.close();
        
            
        
        
        
        
        score.setString(std::to_string(snakeLength-1));
        window.clear();
        window.draw(sprite);
        
        window.draw(apple);
        window.draw(score);
        
        for(int l = 0; l < snakeLength; ++l)
        {
            window.draw(snake[l]);
        }
        window.display();
    }

    return EXIT_SUCCESS;
}
