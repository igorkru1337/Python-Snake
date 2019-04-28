
void menu(RenderWindow & window)
{
	Texture  BackgroudTexture,ButtonStartTexture,ButtonRecordTexture,ButtonDevelopTexture,ButtonExitTexture;

	BackgroudTexture.loadFromFile("Fon.jpg");
	ButtonStartTexture.loadFromFile("Start.jpg");
	ButtonRecordTexture.loadFromFile("Record.jpg");
	ButtonDevelopTexture.loadFromFile("Dev.jpg");
	ButtonExitTexture.loadFromFile("Exit.jpg");
	Sprite background(BackgroudTexture),start(ButtonStartTexture),record(ButtonRecordTexture),develop(ButtonDevelopTexture),exit(ButtonExitTexture);

	bool isMenu = 1;
	int menuNum = 0;
	background.setPosition(0,0);
	start.setPosition(50, 300);
	record.setPosition(50,500);
	develop.setPosition(50,600);
	exit.setPosition(50,800);
	while (window.isOpen())
	{

		exit.setColor(Color::White);
		start.setColor(Color::White);
		record.setColor(Color::White);
		develop.setColor(Color::White);

		menuNum = 0;
		if (IntRect(50, 300, 474, 86).contains(Mouse::getPosition(window)))
		{
			start.setColor(Color::Red);
			menuNum = 1;
		}
		if (IntRect(50, 500, 474, 86).contains(Mouse::getPosition(window)))
		{
			record.setColor(Color::Red);
			menuNum = 2;
		}
		if (IntRect(50, 600, 474, 86).contains(Mouse::getPosition(window)))
		{
			develop.setColor(Color::Red);
			menuNum = 3;
		}
		if (IntRect(50, 800, 474, 86).contains(Mouse::getPosition(window)))
		{
			exit.setColor(Color::Red);
			menuNum = 4;
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			if(menuNum == 1) //game(window);
			if(menuNum == 3)
			{
				while(1)
				{
					window.clear();
					//dev(window);
				}
			}
			if(menuNum == 4) window.close();
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

		window.clear(sf::Color::Black);
		window.draw(background);
		window.draw(start);
		window.draw(record);
		window.draw(develop);
		window.draw(exit);
		window.display();
	}
}
