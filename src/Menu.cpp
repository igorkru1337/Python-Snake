#include "Menu.hpp"

extern struct Player {
    int place;
    char name[80];
    int record;
} p[10];

bool isMenu = 1;

FILE* Rec;
char temp[80];
char temp1[80];

void menu(RenderWindow& window)
{
    Texture BackgroudTexture, ButtonStartTexture, ButtonRecordTexture, ButtonDevelopTexture, ButtonExitTexture, BackgrounddevTexture, BackgroundrecTexture;
    BackgrounddevTexture.loadFromFile("image/Developers.jpg");
    BackgroundrecTexture.loadFromFile("image/Records.jpg");
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
            if (menuNum == 1) {
                game(window);
                window.setTitle("Snake");
            }
            if (menuNum == 2) {
                isMenu = 0;
                rec(window, BackgroundrecTexture, ButtonExitTexture);
            }
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

void rec(RenderWindow& window, Texture& BackgroundTexture, Texture& ButtonExitTexture)
{
    if ((Rec = fopen("thirdparty/txt/Records.txt", "r")) == NULL) {
        Rec = fopen("thirdparty/txt/Records.txt", "w");
        fclose(Rec);
    }
    filesee();
    Text text1;
    Font font;
    if (!font.loadFromFile("thirdparty/font/sansation.ttf"))
        return;
    text1.setFont(font);
    text1.setPosition(200.f, 300.f);
    // text1.setFillColor(Color::White);
    std::string str;
    std::string str1;
    for (int i = 0; i < 10; i++) {
        str = intToStr(p[i].place) + ". " + p[i].name + " - " + intToStr(p[i].record) + "\n";
        str1 = str1 + str;
        text1.setString(str1);
    }
    Sprite background(BackgroundTexture), Exit(ButtonExitTexture);
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
                return;
            }
        }
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
        }
        window.clear();
        window.draw(background);
        window.draw(text1);
        window.draw(Exit);
        window.display();
    }
}

void dev(RenderWindow& window, Texture& BackgrounddevTexture, Texture& ButtonExitTexture)
{
    Text text1;
    Font font;
    if (!font.loadFromFile("thirdparty/font/sansation.ttf"))
        return;
    text1.setFont(font);
    text1.setPosition(150.f, 325.f);
    text1.setString("Krupennikov Igor: Main Developer/Teamleader\n\nAlexey Sarvetnikov: Graphic developer\n\nMihail Zaharov: Game engine developer");
    // text1.setFillColor(Color::White);
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
        window.draw(text1);
        window.draw(Exit);
        window.display();
    }
}

std::string intToStr(int a)
{
    std::string str;
    std::stringstream ss;
    ss << a;
    return str = ss.str();
}

void Pars(char* str, int j)
{
    int i = 0, y = 0;
    char* pEnd;
    while (str[i] != '-') {
        if ((str[i] > 48 && str[i] < 58) || (str[i] > 64 && str[i] < 91) || (str[i] > 96 && str[i] < 127))
            p[j].name[i] = str[i];
        i++;
    }
    i++;
    y = 0;
    while (str[i] != '.') {
        temp1[y] = str[i];
        i++;
        y++;
    }
    p[j].record = strtol(temp1, &pEnd, 10);
}

void filesave()
{
    Rec = fopen("thirdparty/txt/Records.txt", "w");
    for (int i = 0; i < 10; i++) {
        if (p[i].place == i + 1) {
            fprintf(Rec, "%d.%s-%d.\n", p[i].place, p[i].name, p[i].record);
            printf("%d.%s-%d.\n", p[i].place, p[i].name, p[i].record);
        }
    }
    fclose(Rec);
}
void filesee()
{
    Rec = fopen("thirdparty/txt/Records.txt", "r");
    for (int i = 0; i < 10; i++) {
        fscanf(Rec, "%d.%s", &p[i].place, temp);
        if (p[i].place != i + 1) {
            break;
        }
        Pars(temp, i);
    }
    fclose(Rec);
}
