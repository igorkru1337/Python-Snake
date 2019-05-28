#include "Menu.hpp"
bool isMenu = 1;

void menu(RenderWindow& window)
{
    Texture BackgroudTexture, ButtonStartTexture, ButtonRecordTexture, ButtonDevelopTexture, ButtonExitTexture, BackgrounddevTexture;
    BackgrounddevTexture.loadFromFile("image/Developers.jpg");
    BackgroudTexture.loadFromFile("image/Fon.jpg");
    ButtonStartTexture.loadFromFile("image/Start.jpg");
    ButtonRecordTexture.loadFromFile("image/Record.jpg");
    ButtonDevelopTexture.loadFromFile("image/Dev.jpg");
    ButtonExitTexture.loadFromFile("image/Exit.jpg");
    Sprite background(BackgroudTexture), start(ButtonStartTexture), record(ButtonRecordTexture), develop(ButtonDevelopTexture), exit(ButtonExitTexture);
    int menuNum = 0;
    background.setPosition(0, 0);
    start.setPosition(50, 300);
    record.setPosition(50, 500);
    develop.setPosition(50, 600);
    exit.setPosition(50, 800);
    while (window.isOpen()) {
        exit.setColor(Color::White);
        start.setColor(Color::White);
        record.setColor(Color::White);
        develop.setColor(Color::White);

        menuNum = 0;
        if (IntRect(50, 300, 474, 86).contains(Mouse::getPosition(window))) {
            start.setColor(Color::Red);
            menuNum = 1;
        }
        if (IntRect(50, 500, 474, 86).contains(Mouse::getPosition(window))) {
            record.setColor(Color::Red);
            menuNum = 2;
        }
        if (IntRect(50, 600, 474, 86).contains(Mouse::getPosition(window))) {
            develop.setColor(Color::Red);
            menuNum = 3;
        }
        if (IntRect(50, 800, 474, 86).contains(Mouse::getPosition(window))) {
            exit.setColor(Color::Red);
            menuNum = 4;
        }
        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (menuNum == 1)
                game(window);
            if (menuNum == 3) {
                isMenu = 0;
                dev(window, BackgrounddevTexture, ButtonExitTexture);
            }
            if (menuNum == 4)
                window.close();
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(background);
        window.draw(start);
        window.draw(record);
        window.draw(develop);
        window.draw(exit);
        window.display();
    }
}

void dev(RenderWindow& window, Texture& BackgrounddevTexture, Texture& ButtonExitTexture)
{
    Sprite background(BackgrounddevTexture), Exit(ButtonExitTexture);
    int menuNum = 0;
    background.setPosition(0, 0);
    Exit.setPosition(530, 800);
    while (window.isOpen()) {
        Exit.setColor(Color::White);

        if (IntRect(530, 800, 954, 86).contains(Mouse::getPosition(window))) {
            Exit.setColor(Color::Red);
            menuNum = 1;
        } else
            menuNum = 0;

        if (Mouse::isButtonPressed(Mouse::Left)) {
            if (menuNum == 1)

            {
                isMenu = 1;
                menu(window);
            }
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(background);
        window.draw(Exit);
        window.display();
    }
}
