#include <SFML/Graphics.hpp>
#include <vector>

int main()
{
    double maskOpacity = 35;

    // Create the main window
    sf::RenderWindow app(sf::VideoMode::getDesktopMode(), "Gina's Screensaver", sf::Style::Fullscreen);

    // Create a view
    sf::View view(sf::FloatRect(0, 0, app.getSize().x, app.getSize().y));
    view.setCenter(app.getSize().x/2, app.getSize().y/2);
    view.setViewport(sf::FloatRect(0, 0, 1, 1));
    view.zoom(0.27f);

    // Create background
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("background.png");
    sf::IntRect backgroundSpriteSize(0, 0, 512,  387);
    sf::Sprite background(backgroundTexture, backgroundSpriteSize);

    background.setOrigin(background.getLocalBounds().width/2, background.getLocalBounds().height/2);
    background.setPosition(app.getSize().x/2, app.getSize().y/2);

    // Create color mask
    sf::RectangleShape mask(sf::Vector2f(background.getLocalBounds().width, background.getLocalBounds().height));
    mask.setFillColor(sf::Color(81,55,55, maskOpacity));

    mask.setOrigin(mask.getLocalBounds().width/2, mask.getLocalBounds().height/2);
    mask.setPosition(app.getSize().x/2, app.getSize().y/2);

    // Create cloud
    sf::Texture cloudSprite;
    cloudSprite.loadFromFile("cloud.png");
    sf::IntRect cloudSpriteSize(0, 0, 64, 42.67f);
    sf::Sprite cloud(cloudSprite, cloudSpriteSize);

    cloud.setOrigin(cloud.getLocalBounds().width/2, cloud.getLocalBounds().height/2);
    cloud.setPosition(app.getSize().x/2, app.getSize().y/2 + 52);
    cloud.scale(3,3);

    //Create sleeping cat
    sf::Texture catSprite;
    catSprite.loadFromFile("catSpritesheet.png");
    sf::IntRect catsSpriteSize(0, 0, 64, 64);
    sf::Sprite cat(catSprite, catsSpriteSize);

    cat.setOrigin(cat.getLocalBounds().width/2, cat.getLocalBounds().height/2);
    cat.setPosition(app.getSize().x/2 + 7, app.getSize().y/2);
    cat.scale(2,2);



    // Create timer
    sf::Clock cloudTimer;
    sf::Clock catTimer;
    sf::Clock backgroundTimer;
    sf::Clock maskTimer;

	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
        }


        // cloud animation
        if (cloudTimer.getElapsedTime().asSeconds() > 0.5f)
        {
            if (cloudSpriteSize.left == 512)
            {
                cloudSpriteSize.left = 0;
            }
            else
            {
                cloudSpriteSize.left += 64;
            }
            cloud.setTextureRect(cloudSpriteSize);
            cloudTimer.restart();
        }


        // cat animation
        if (catTimer.getElapsedTime().asSeconds() > 0.2f)
        {
            if (catsSpriteSize.left == 2816)
            {
                catsSpriteSize.left = 0;
            }
            else
            {
                catsSpriteSize.left += 64;
            }
            cat.setTextureRect(catsSpriteSize);
            catTimer.restart();
        }


        // background animation
        if (backgroundTimer.getElapsedTime().asSeconds() > 0.07f)
        {
            if (backgroundSpriteSize.left == 512)
            {
                backgroundSpriteSize.left = 0;
            }
            else
            {
                backgroundSpriteSize.left++;
            }
            background.setTextureRect(backgroundSpriteSize);
            backgroundTimer.restart();
        }

        //changeColorOfMask
        if (maskTimer.getElapsedTime().asSeconds() > 0.2f)
        {

                if (maskOpacity > 170)
                {
                    maskOpacity--;
                }
                else
                {
                    maskOpacity++;
                }
                mask.setFillColor(sf::Color(81,55,55, maskOpacity));
                maskTimer.restart();
        }


        // Clear screen
        app.clear();

        // View
        app.setView(view);

        // Draw background
        app.draw(background);
        app.draw(mask);

         // Draw the sprite
        app.draw(cloud);

        // Draw the sprite
        app.draw(cat);

        // Update the window
        app.display();


        // exit screen saver
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::TextEntered)
        {
        return EXIT_SUCCESS;
        }

    }

    return EXIT_SUCCESS;
}

