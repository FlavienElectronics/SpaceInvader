#include "GameOver.hpp"

GameOver::Letter::Letter(float x, float y, int numberOfPoint, int width)
{
	this->x = x;
	this->y = y;
	this->numberOfPoint = numberOfPoint;
	this->width = width;
}

GameOver::Letter::~Letter()
{
	if (this->pt != nullptr)
	{
		for (int i = 0; i < this->numberOfPoint; i++)
		{
			delete this->pt[i];
		}
		delete[] this->pt;
	}
}

GameOver::G::G(float x, float y) : Letter(x, y, 10, 4)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 2, "W");
	this->pt[2] = new Point(this->x + 0, this->y + 3, "W");
	this->pt[3] = new Point(this->x + 1, this->y + 0, "W");
	this->pt[4] = new Point(this->x + 1, this->y + 4, "W");
	this->pt[5] = new Point(this->x + 2, this->y + 0, "W");
	this->pt[6] = new Point(this->x + 2, this->y + 2, "W");
	this->pt[7] = new Point(this->x + 2, this->y + 4, "W");
	this->pt[8] = new Point(this->x + 3, this->y + 2, "W");
	this->pt[9] = new Point(this->x + 3, this->y + 3, "W");
}
GameOver::G::~G() {}

GameOver::A::A(float x, float y) : Letter(x, y, 12, 4)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 2, "W");
	this->pt[2] = new Point(this->x + 0, this->y + 3, "W");
	this->pt[3] = new Point(this->x + 0, this->y + 4, "W");
	this->pt[4] = new Point(this->x + 1, this->y + 0, "W");
	this->pt[5] = new Point(this->x + 1, this->y + 2, "W");
	this->pt[6] = new Point(this->x + 2, this->y + 0, "W");
	this->pt[7] = new Point(this->x + 2, this->y + 2, "W");
	this->pt[8] = new Point(this->x + 3, this->y + 1, "W");
	this->pt[9] = new Point(this->x + 3, this->y + 2, "W");
	this->pt[10] = new Point(this->x + 3, this->y + 3, "W");
	this->pt[11] = new Point(this->x + 3, this->y + 4, "W");
}
GameOver::A::~A() {}

GameOver::M::M(float x, float y) : Letter(x, y, 13, 5)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 0, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[2] = new Point(this->x + 0, this->y + 2, "W");
	this->pt[3] = new Point(this->x + 0, this->y + 3, "W");
	this->pt[4] = new Point(this->x + 0, this->y + 4, "W");
	this->pt[5] = new Point(this->x + 1, this->y + 1, "W");
	this->pt[6] = new Point(this->x + 2, this->y + 2, "W");
	this->pt[7] = new Point(this->x + 3, this->y + 1, "W");
	this->pt[8] = new Point(this->x + 4, this->y + 0, "W");
	this->pt[9] = new Point(this->x + 4, this->y + 1, "W");
	this->pt[10] = new Point(this->x + 4, this->y + 2, "W");
	this->pt[11] = new Point(this->x + 4, this->y + 3, "W");
	this->pt[12] = new Point(this->x + 4, this->y + 4, "W");
}
GameOver::M::~M() {}

GameOver::E::E(float x, float y) : Letter(x, y, 10, 3)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 0, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[2] = new Point(this->x + 0, this->y + 2, "W");
	this->pt[3] = new Point(this->x + 0, this->y + 3, "W");
	this->pt[4] = new Point(this->x + 0, this->y + 4, "W");
	this->pt[5] = new Point(this->x + 1, this->y + 0, "W");
	this->pt[6] = new Point(this->x + 1, this->y + 2, "W");
	this->pt[7] = new Point(this->x + 1, this->y + 4, "W");
	this->pt[8] = new Point(this->x + 2, this->y + 0, "W");
	this->pt[9] = new Point(this->x + 2, this->y + 4, "W");
}
GameOver::E::~E() {}

GameOver::O::O(float x, float y) : Letter(x, y, 10, 4)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 2, "W");
	this->pt[2] = new Point(this->x + 0, this->y + 3, "W");
	this->pt[3] = new Point(this->x + 1, this->y + 0, "W");
	this->pt[4] = new Point(this->x + 1, this->y + 4, "W");
	this->pt[5] = new Point(this->x + 2, this->y + 0, "W");
	this->pt[6] = new Point(this->x + 2, this->y + 4, "W");
	this->pt[7] = new Point(this->x + 3, this->y + 1, "W");
	this->pt[8] = new Point(this->x + 3, this->y + 2, "W");
	this->pt[9] = new Point(this->x + 3, this->y + 3, "W");
}
GameOver::O::~O() {}

GameOver::V::V(float x, float y) : Letter(x, y, 9, 5)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 0, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[2] = new Point(this->x + 1, this->y + 2, "W");
	this->pt[3] = new Point(this->x + 1, this->y + 3, "W");
	this->pt[4] = new Point(this->x + 2, this->y + 4, "W");
	this->pt[5] = new Point(this->x + 3, this->y + 2, "W");
	this->pt[6] = new Point(this->x + 3, this->y + 3, "W");
	this->pt[7] = new Point(this->x + 4, this->y + 0, "W");
	this->pt[8] = new Point(this->x + 4, this->y + 1, "W");
}
GameOver::V::~V() {}

GameOver::R::R(float x, float y) : Letter(x, y, 13, 4)
{
	this->pt = new Point *[this->numberOfPoint];
	this->pt[0] = new Point(this->x + 0, this->y + 0, "W");
	this->pt[1] = new Point(this->x + 0, this->y + 1, "W");
	this->pt[2] = new Point(this->x + 0, this->y + 2, "W");
	this->pt[3] = new Point(this->x + 0, this->y + 3, "W");
	this->pt[4] = new Point(this->x + 0, this->y + 4, "W");
	this->pt[5] = new Point(this->x + 1, this->y + 0, "W");
	this->pt[6] = new Point(this->x + 1, this->y + 2, "W");
	this->pt[7] = new Point(this->x + 2, this->y + 0, "W");
	this->pt[8] = new Point(this->x + 2, this->y + 2, "W");
	this->pt[9] = new Point(this->x + 2, this->y + 3, "W");
	this->pt[10] = new Point(this->x + 3, this->y + 0, "W");
	this->pt[11] = new Point(this->x + 3, this->y + 1, "W");
	this->pt[12] = new Point(this->x + 3, this->y + 4, "W");
}
GameOver::R::~R() {}

GameOver::GameOver(float windowWidth, float windowHeight) : winW(windowWidth), winH(windowHeight)
{
	this->numberOfLetter = 8;
	lettersGameOver = new Letter *[this->numberOfLetter];
	int big_space = 4;
	int small_space = 1;
	float widthString = 4 + 4 + 5 + 3 + 4 + 5 + 3 + 4 + 8 * 1 + 4; // G + A + M + E + O + V + E + R + 8 small space + 1 big space
	lettersGameOver[0] = new G(((windowWidth - widthString) / 2), windowHeight / 2);
	lettersGameOver[1] = new A((this->lettersGameOver[0]->x + this->lettersGameOver[0]->width + small_space), windowHeight / 2);
	lettersGameOver[2] = new M((this->lettersGameOver[1]->x + this->lettersGameOver[1]->width + small_space), windowHeight / 2);
	lettersGameOver[3] = new E((this->lettersGameOver[2]->x + this->lettersGameOver[2]->width + small_space), windowHeight / 2);
	lettersGameOver[4] = new O((this->lettersGameOver[3]->x + this->lettersGameOver[3]->width + big_space), windowHeight / 2);
	lettersGameOver[5] = new V((this->lettersGameOver[4]->x + this->lettersGameOver[4]->width + small_space), windowHeight / 2);
	lettersGameOver[6] = new E((this->lettersGameOver[5]->x + this->lettersGameOver[5]->width + small_space), windowHeight / 2);
	lettersGameOver[7] = new R((this->lettersGameOver[6]->x + this->lettersGameOver[6]->width + small_space), windowHeight / 2);
}

void GameOver::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// cout << this->lettersGameOver[4]->pt[0]->getX() << endl;
	target.draw(*this->lettersGameOver[0]->pt[0]);
	if (this->lettersGameOver != nullptr)
	{
		for (int i = 0; i < this->numberOfLetter; i++)
		{
			if (this->lettersGameOver[i] != nullptr)
			{
				for (int j = 0; j < this->lettersGameOver[i]->numberOfPoint; j++)
				{
					target.draw(*(this->lettersGameOver[i])->pt[j], states);
				}
			}
		}
	}
}
GameOver::~GameOver()
{
	if (this->lettersGameOver != nullptr)
	{
		for (int i = 0; i < this->numberOfLetter; i++)
		{
			if (lettersGameOver[i] != nullptr)
			{
				delete lettersGameOver[i];
			}
		}
		delete[] lettersGameOver;
	}
}