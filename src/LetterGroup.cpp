#include "LetterGroup.hpp"

LetterGroup::Letter::Letter(float x, float y, int numberOfPoint, int width)
{
	this->x = x;
	this->y = y;
	this->numberOfPoint = numberOfPoint;
	this->width = width;
}

LetterGroup::Letter::~Letter()
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

LetterGroup::G::G(float x, float y) : Letter(x, y, 10, 4)
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
LetterGroup::G::~G() {}

LetterGroup::A::A(float x, float y) : Letter(x, y, 12, 4)
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
LetterGroup::A::~A() {}

LetterGroup::M::M(float x, float y) : Letter(x, y, 13, 5)
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
LetterGroup::M::~M() {}

LetterGroup::E::E(float x, float y) : Letter(x, y, 10, 3)
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
LetterGroup::E::~E() {}

LetterGroup::O::O(float x, float y) : Letter(x, y, 10, 4)
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
LetterGroup::O::~O() {}

LetterGroup::V::V(float x, float y) : Letter(x, y, 9, 5)
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
LetterGroup::V::~V() {}

LetterGroup::R::R(float x, float y) : Letter(x, y, 13, 4)
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
LetterGroup::R::~R() {}

LetterGroup::LetterGroup(float windowWidth, float windowHeight) : winW(windowWidth), winH(windowHeight) {}

void LetterGroup::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
	// cout << this->lettersLetterGroup[4]->pt[0]->getX() << endl;
	target.draw(*this->lettersList[0]->pt[0]);
	if (this->lettersList != nullptr)
	{
		for (int i = 0; i < this->numberOfLetter; i++)
		{
			if (this->lettersList[i] != nullptr)
			{
				for (int j = 0; j < this->lettersList[i]->numberOfPoint; j++)
				{
					target.draw(*(this->lettersList[i])->pt[j], states);
				}
			}
		}
	}
}

int LetterGroup::Letter::getWidth()
{
	return (this->width);
}
float LetterGroup::Letter::getX()
{
	return(this->x);
}
float LetterGroup::Letter::getY()
{
	return (this->y);
}
int LetterGroup::Letter::getNumberOfPoint()
{
	return (this->numberOfPoint);
}

LetterGroup::~LetterGroup()
{
	if (this->lettersList != nullptr)
	{
		for (int i = 0; i < this->numberOfLetter; i++)
		{
			if (lettersList[i] != nullptr)
			{
				delete lettersList[i];
			}
		}
		delete[] lettersList;
	}
}