#include "Snake.hpp"

struct {
    int x;
    int y;
} s[100];

class fruct // ????? ???????, ??? ?????, ??????? ????? ???? ???? ????
{
public:
    int x1, y1; //?????????? ???????, ??? ? ??? ????? ?????????

    void New() // ?????? ? ?????? ????????. ?? ????? ?????????? ? ?????? ???? ? ? ??? ??????, ????? ???? ????? ???? ?? ???????
    {
        x1 = rand() % N; // ?????????? X ?????????? ????? ??????
        y1 = rand() % M; // ?????????? Y ?????????? ????? ??????
    }

    void DrawFruct(sf::RenderWindow& win, Texture& FructTexture) // ??????, ?????????????? ??????
    {
        Sprite Fruct(FructTexture);
        Fruct.setPosition(x1 * scale - 8, y1 * scale - 15);
        win.draw(Fruct);
    }
} m[5]; // ????? ? ????????, ????? ???????, ? ??? ???????? ???????????? 5 ??????? ? ?????? ??????, ? ?? ????, ??? ?? ????????

void Draw(sf::RenderWindow& win, Texture& GamegroundTexture) // ???????, ??????? ???????????? ?????
{
    sf::VertexArray linew(sf::Lines, 80);
    sf::VertexArray lineh(sf::Lines, 80);
    Sprite Gameground(GamegroundTexture);
    Gameground.setPosition(0, 0);
    for (int i = 0, j = 0; i < 1000; i += scale, j += 2) {
        lineh[j].position = sf::Vector2f(i, 0);
        lineh[j + 1].position = sf::Vector2f(i, 1000);
        linew[j].position = sf::Vector2f(0, i);
        linew[j + 1].position = sf::Vector2f(1000, i);
    }
    win.draw(Gameground);
    win.draw(lineh);
    win.draw(linew);
}

void Snake(sf::RenderWindow& win, Texture& HeadLeftTexture)
{
    for (int i = 1; i < num; i++) // ???? ?????????.
    {
        sf::RectangleShape line(sf::Vector2f(24, 24));

        line.setPosition(s[i].x * scale, s[i].y * scale + 1);

        line.setFillColor(sf::Color(69, 139, 116));
        Sprite head(HeadLeftTexture);
        if (dir == 1) {
            head.rotate(180);
            head.setPosition(s[0].x * scale + 27, s[0].y * scale + 27);
        }
        if (dir == 0) {
            head.rotate(90);
            head.setPosition(s[0].x * scale + 26, s[0].y * scale - 2);
        }
        if (dir == 2) {
            head.rotate(270);
            head.setPosition(s[0].x * scale - 2, s[0].y * scale + 27);
        }
        if (dir == 3) {
            head.rotate(0);
            head.setPosition(s[0].x * scale - 2, s[0].y * scale - 1);
        }
        win.draw(head);
        win.draw(line);
    }
}

void Key(int& dir)
{
    if ((Keyboard::isKeyPressed(Keyboard::Up) || Keyboard::isKeyPressed(Keyboard::W)) && dir != 2)
        dir = 0;
    else {
        if ((Keyboard::isKeyPressed(Keyboard::Right) || Keyboard::isKeyPressed(Keyboard::D)) && dir != 3)
            dir = 1;
        else {
            if ((Keyboard::isKeyPressed(Keyboard::Down) || Keyboard::isKeyPressed(Keyboard::S)) && dir != 0)
                dir = 2;
            else {
                if ((Keyboard::isKeyPressed(Keyboard::Left) || Keyboard::isKeyPressed(Keyboard::A)) && dir != 1)
                    dir = 3;
            }
        }
    }
}

void Display(sf::RenderWindow& win, Texture& GamegroundTexture, Texture& FructTexture, Texture& HeadLeftTexture)
{
    Draw(win, GamegroundTexture);
    for (int i = 0; i < 5; i++)
        m[i].DrawFruct(win, FructTexture);
    Snake(win, HeadLeftTexture);
}

int game(RenderWindow& window) // ??????? ???????
{
    Image Head;
    Head.loadFromFile("image/Lefthead.png");
    Head.createMaskFromColor(Color(255, 255, 255));
    Texture GamegroundTexture, FructTexture, HeadLeftTexture;
    GamegroundTexture.loadFromFile("image/Gamefon.jpg");
    FructTexture.loadFromFile("image/Apple.png");
    HeadLeftTexture.loadFromImage(Head);
    srand(time(0));
    dir = 0;
    bool isKey = 1;
    bool isPaused = 0;
    for (int i = 0; i < 5; i++)
        m[i].New();
    num = 4;
    s[0].x = 10;
    for (int i = 0; i < num; i++) {
        s[i].y = 10 + (i + 1);
        s[i].x = 10;
    }
    int speed = 500;
    float timer = 0;
    Clock clock;
    while (window.isOpen()) {
        sf::Event event;
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / speed;
        timer += time;
        if (isPaused)
            timer = 0;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::LostFocus)
                isPaused = 1;
            if (event.type == sf::Event::GainedFocus)
                isPaused = 0;
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyReleased) {
                if (event.key.code == sf::Keyboard::Space) {
                    if (isPaused == 0)
                        isPaused = 1;
                    else
                        isPaused = 0;
                }
            }
        }
        if (Keyboard::isKeyPressed(Keyboard::Escape))
            menu(window);
        if (isKey == 1) {
            Key(dir);
            isKey = 0;
        }
        window.clear();
        Display(window, GamegroundTexture, FructTexture, HeadLeftTexture);
        window.display();
        if (timer > speed) {
            for (int i = 1; i < num; i++)
                if (s[0].x == s[i].x && s[0].y == s[i].y)
                    return 0;
            if (s[0].x > 39)
                return 0;
            if (s[0].y > 39)
                return 0;
            if (s[0].x < 0)
                return 0;
            if (s[0].y < 0)
                return 0;
            for (int i = num; i > 0; --i) {
                s[i].x = s[i - 1].x;
                s[i].y = s[i - 1].y;
            }
            if (dir == 2)
                s[0].y += 1;
            if (dir == 3)
                s[0].x -= 1;
            if (dir == 1)
                s[0].x += 1;
            if (dir == 0)
                s[0].y -= 1;
            isKey = 1;
            timer = 0;
            for (int i = 0; i < 5; i++) //????, ? ??????? ???? ???? ????? ?????
            {
                if ((s[0].x == m[i].x1) && (s[0].y == m[i].y1)) {
                    num++;
                    m[i].New();
                }
            }
        }
    }
    return 0;
}
