#include "YouWon.hpp"

YouWon::YouWon(string colour, float windowWidth, float windowHeight) : LetterGroup(colour, windowWidth, windowHeight)
{
    this->numberOfLetter = 8;
    this->lettersList = new Letter *[this->numberOfLetter];
    float widthString = 4 + 4 + 5 + 3 + 4 + 5 + 3 + 4 + 6 * 1 + 4; // Y + O + U + W + O + N + ! + ! + 6 small space + 1 big space
    lettersList[0] = new Y(((windowWidth - widthString) / 2), windowHeight / 2, colour);
    lettersList[1] = new O((this->lettersList[0]->getX() + this->lettersList[0]->getWidth() + this->small_space), windowHeight / 2, colour);
    lettersList[2] = new U((this->lettersList[1]->getX() + this->lettersList[1]->getWidth() + this->small_space), windowHeight / 2, colour);
    lettersList[3] = new W((this->lettersList[2]->getX() + this->lettersList[2]->getWidth() + this->big_space), windowHeight / 2, colour);
    lettersList[4] = new O((this->lettersList[3]->getX() + this->lettersList[3]->getWidth() + this->small_space), windowHeight / 2, colour);
    lettersList[5] = new N((this->lettersList[4]->getX() + this->lettersList[4]->getWidth() + this->small_space), windowHeight / 2, colour);
    lettersList[6] = new Exclamation((this->lettersList[5]->getX() + this->lettersList[5]->getWidth() + this->small_space), windowHeight / 2, colour);
    lettersList[7] = new Exclamation((this->lettersList[6]->getX() + this->lettersList[6]->getWidth() + this->small_space), windowHeight / 2, colour);
}
YouWon::~YouWon() {}
