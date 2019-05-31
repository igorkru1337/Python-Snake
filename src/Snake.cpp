#include "Snake.hpp"
#include "GlobVar.hpp"

extern FILE* Rec;
extern char temp[80];
extern char temp1[80];

struct Player {
    int place;
    char name[80];
    int record;
} p[10];

struct S {
    int x;
    int y;
} s[100];

class fruct {
public:
    int x1, y1;

    void New()
    {
        x1 = rand() % N;
        y1 = rand() % M;
    }

    void DrawFruct(sf::RenderWindow& win, Texture& FructTexture)
    {
        Sprite Fruct(FructTexture);
        Fruct.setPosition(x1 * scale - 8, y1 * scale - 15);
        win.draw(Fruct);
    }
} m[5];

void Draw(sf::RenderWindow& win, Texture& GamegroundTexture)
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
    for (int i = 1; i < num; i++) {
        sf::RectangleShape line(sf::Vector2f(24, 24));

        line.setPosition(s[i].x * scale, s[i].y * scale + 1);

        line.setFillColor(sf::Color(69, 139, 116));
        Sprite head(HeadLeftTexture);
        RotateHead(dir, head);
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

void setRecord(int Score, char* name)
{
    int i, j, k;
    for (i = 0; i < 10; i++) {
        if (Score > p[i].record) {
            for (k = i; k < 10; k++) {
                if (p[k].place != 0)
                    p[k + 1].place = k + 2;
            }
            if (i == 0)
                p[0].place = 1;
            for (j = 9; j >= i; j--) {
                p[j].record = p[j - 1].record;
                strcpy(p[j].name, p[j - 1].name);
            }
            p[i].record = Score;
            strcpy(p[i].name, name);
            filesave();
            return;
        }
    }
}

void GameOver(RenderWindow& window, Font& font, Texture& GamegroundTexture, int Score)
{
    int i = 0;
    char t[10], str[11];
    for (int i = 0; i < 10; i++)
        t[i] = ' ';
    Text text, text1;
    text.setFont(font);
    text1.setFont(font);
    // text.setOutlineColor(sf::Color::Black);
    // text1.setFillColor(sf::Color::Red);
    text.setPosition(60.f, 45.f);
    text1.setPosition(5.f, 10.f);
    text1.setString("Input player name:");
    sf::RenderWindow WinBox(sf::VideoMode(256, 128), "GAME OVER", sf::Style::Titlebar);
    Sprite fon(GamegroundTexture);
    while (WinBox.isOpen()) {
        // window.setVisible(false);
        WinBox.setActive(true);
        Event event;
        while (WinBox.pollEvent(event)) {
            if (event.type == sf::Event::LostFocus) {
                WinBox.setVisible(true);
            }
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == 8)
                    if (i > 0) {
                        t[--i] = ' ';
                        text.setString(t);
                    }
                if (event.text.unicode < 123 && event.text.unicode > 47 && i < 10) {
                    t[i] = static_cast<char>(event.text.unicode);
                    i++;
                    text.setString(t);
                }
            }
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                window.setVisible(true);
                WinBox.setActive(false);
                WinBox.close();
                strncpy(str, t, i);
                setRecord(Score, str);
                return;
            }
        }
        WinBox.clear(sf::Color::White);
        WinBox.draw(fon);
        WinBox.draw(text1);
        WinBox.draw(text);
        WinBox.display();
    }
}

int ChooseWin(RenderWindow& window, Font& font, Texture& GamegroundTexture)
{
    int i = 0;
    std::string Dif[3];
    Dif[0] = "Easy";
    Dif[1] = "Medium";
    Dif[2] = "Hard";
    Text text;
    text.setFont(font);
    // text.setFillColor(sf::Color::Red);
    text.setPosition(80.f, 40.f);
    sf::RenderWindow WinBox(sf::VideoMode(256, 128), "Choose the difficulty", sf::Style::Titlebar);
    Sprite fon(GamegroundTexture);
    while (WinBox.isOpen()) {
        // window.setVisible(false);
        text.setString(Dif[i]);
        WinBox.setActive(true);
        Event event;
        while (WinBox.pollEvent(event)) {
            if (event.type == sf::Event::LostFocus) {
                WinBox.setVisible(true);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)) {
                i++;
                if (i > 2)
                    i = 0;
            }
            if (Keyboard::isKeyPressed(Keyboard::Down)) {
                i--;
                if (i < 0)
                    i = 2;
            }
            if (Keyboard::isKeyPressed(Keyboard::Return)) {
                window.setVisible(true);
                WinBox.setActive(false);
                WinBox.close();
                if (i == 0)
                    return 800;
                if (i == 1)
                    return 500;
                if (i == 2)
                    return 300;
            }
        }
        WinBox.clear(sf::Color::White);
        WinBox.draw(fon);
        WinBox.draw(text);
        WinBox.display();
    }
    return 0;
}

int game(RenderWindow& window)
{
    if ((Rec = fopen("thirdparty/txt/Records.txt", "r")) == NULL) {
        Rec = fopen("thirdparty/txt/Records.txt", "w");
        fclose(Rec);
    }
    filesee();
    Image Head;
    Head.loadFromFile("image/Lefthead.png");
    Head.createMaskFromColor(Color(255, 255, 255));
    Texture GamegroundTexture, FructTexture, HeadLeftTexture;
    GamegroundTexture.loadFromFile("image/Gamefon.jpg");
    FructTexture.loadFromFile("image/Apple.png");
    HeadLeftTexture.loadFromImage(Head);
    Font font;
    if (!font.loadFromFile("thirdparty/font/sansation.ttf"))
        return -1;
    int speed = ChooseWin(window, font, GamegroundTexture);
    window.setTitle("Snake");
    int Score = 0;
    std::string list;
    Text textR;
    textR.setFont(font);
    srand(time(0));
    dir = 0;
    bool isKey = 1;
    bool isPaused = 0;
    for (int i = 0; i < 5; i++)
        m[i].New();
    num = 4;
    s[0].x = 10;
    for (int i = 0; i < num; i++) {
        s[i].y = 20 + (i + 1);
        s[i].x = 10;
    }
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
            return 0;
        if (isKey == 1) {
            Key(dir);
            isKey = 0;
        }
        window.clear();
        Display(window, GamegroundTexture, FructTexture, HeadLeftTexture);
        window.display();
        if (timer > speed) {
            if (SnakeCrush(s) == 0) {
                GameOver(window, font, GamegroundTexture, Score);
                return 0;
            }
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
            for (int i = 0; i < 5; i++) {
                if ((s[0].x == m[i].x1) && (s[0].y == m[i].y1)) {
                    num++;
                    Score += 10;
                    window.setTitle("Snake. Score: " + intToStr(Score));
                    for (int j = 0; j < num; j++)
                        while ((s[j].x == m[i].x1) && (s[j].y == m[i].y1))
                            m[i].New();
                }
            }
        }
    }
    return 0;
}

int RotateHead(int dir, Sprite& head)
{
    int angle = 0;
    if (dir == 1) {
        angle = 180;
        head.rotate(angle);
        head.setPosition(s[0].x * scale + 27, s[0].y * scale + 27);
    }
    if (dir == 0) {
        angle = 90;
        head.rotate(angle);
        head.setPosition(s[0].x * scale + 26, s[0].y * scale - 2);
    }
    if (dir == 2) {
        angle = 270;
        head.rotate(angle);
        head.setPosition(s[0].x * scale - 2, s[0].y * scale + 27);
    }
    if (dir == 3) {
        angle = 0;
        head.rotate(angle);
        head.setPosition(s[0].x * scale - 2, s[0].y * scale - 1);
    }
    return angle;
}
int SnakeCrush(struct S* s)
{
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
    return 1;
}
