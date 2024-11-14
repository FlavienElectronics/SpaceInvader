#include "GameOver.hpp"

GameOver::GameOver(string colour, float windowWidth, float windowHeight) : LetterGroup(colour, windowWidth, windowHeight)
{
	cout << "constructeur gameover " << endl;
	this->numberOfLetter = 8;
	this->lettersList = new Letter *[this->numberOfLetter];
	float widthString = 4 + 4 + 5 + 3 + 4 + 5 + 3 + 4 + 8 * 1 + 4; // G + A + M + E + O + V + E + R + 8 small space + 1 big space
	lettersList[0] = new G(((windowWidth - widthString) / 2), windowHeight / 2, "W");
	lettersList[1] = new A((this->lettersList[0]->getX() + this->lettersList[0]->getWidth() + this->small_space), windowHeight / 2, "W");
	lettersList[2] = new M((this->lettersList[1]->getX() + this->lettersList[1]->getWidth() + this->small_space), windowHeight / 2, "W");
	lettersList[3] = new E((this->lettersList[2]->getX() + this->lettersList[2]->getWidth() + this->small_space), windowHeight / 2, "W");
	lettersList[4] = new O((this->lettersList[3]->getX() + this->lettersList[3]->getWidth() + this->big_space), windowHeight / 2, "W");
	lettersList[5] = new V((this->lettersList[4]->getX() + this->lettersList[4]->getWidth() + this->small_space), windowHeight / 2, "W");
	lettersList[6] = new E((this->lettersList[5]->getX() + this->lettersList[5]->getWidth() + this->small_space), windowHeight / 2, "W");
	lettersList[7] = new R((this->lettersList[6]->getX() + this->lettersList[6]->getWidth() + this->small_space), windowHeight / 2, "W");
	cout << "En vie constructeur gameover " << endl;
}
