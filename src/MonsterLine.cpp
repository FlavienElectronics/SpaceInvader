#include "MonsterLine.hpp"

MonsterLine::MonsterLine(sf::RenderWindow *win, float windowHeight, float windowWidth, float x_pos, float y_pos, int numberOfMonster, string color)
{
    cout << "Constructeur MonsterLine" << endl;
    this->direction = rand() % 2;
    this->numberOfMonster = numberOfMonster;
    this->winHeight = windowHeight;
    this->winWidth = windowWidth;
    this->spacing = 6;
    block = new Monster *[this->numberOfMonster];
    int xLocation = x_pos;
    int yLocation = y_pos;
    if (this->block != nullptr)
    {
        int cnt = 1;
        for (int i = 0; i < this->numberOfMonster; i++)
        {
            block[i] = new Monster(win, winHeight, winWidth, xLocation + (i * spacing), yLocation, "col");
            cnt++;
        }
    }
}

Monster &MonsterLine::operator[](int location)
{
    return (*this->block[location]);
}

void MonsterLine::draw(sf::RenderTarget &target, sf::RenderStates states) const
{
    for (int i = 0; i < this->numberOfMonster; i++)
    {
        if (this->block[i] != nullptr)
        {
            target.draw(*this->block[i], states);
        }
    }
}

bool MonsterLine::isExplosing(int location)
{
    return (this->block[location]->isExplosing());
}

void MonsterLine::updateParticule(int location)
{
    this->block[location]->updateParticule();
}

void MonsterLine::explode(int location)
{
    this->block[location]->explode();
}

bool MonsterLine::isAlive(int location)
{
    return (this->block[location]->isAlive());
}

void MonsterLine::changeDirection()
{
    if (this->direction == 1)
    {
        this->direction = 0;
    }
    else
    {
        this->direction = 1;
    }
    for (int i = 0; i < this->numberOfMonster; i++)
    {
        this->block[i]->changeDirection();
    }
}

void MonsterLine::updateCollision(const SpaceShip &ship, bool **vectorBool)
{
    if (*vectorBool != nullptr)
    {
        delete[] *vectorBool;
        *vectorBool = nullptr;
        cout << "Vector deleted" << endl;
    }
    if (*vectorBool == nullptr)
    {
        *vectorBool = new bool[this->numberOfMonster];
        cout << "Vector allocated " << *vectorBool << " Size " << this->numberOfMonster << endl;
        for (int i = 0; i < this->numberOfMonster; i++)
        {
            (*vectorBool)[i] = false;
        }
    }
    cout << "Number of monster " << this->numberOfMonster << endl;
    for (int i = 0; i < this->numberOfMonster; i++)
    {
        (*vectorBool)[i] = this->block[i]->updateCollision(ship);
    }
}

void MonsterLine::xSub()
{
    if (this->block != nullptr)
    {
        for (int j = 0; j < this->numberOfMonster; j++)
        {
            try
            {
                this->block[j]->xSub();
            }
            catch (SpaceShip::Exept &exp)
            {
                throw(exp);
            }
        }
    }
}

void MonsterLine::xAdd()
{
    if (this->block != nullptr)
    {
        for (int j = this->numberOfMonster - 1; j >= 0; j--)
        {
            try
            {
                this->block[j]->xAdd();
            }
            catch (SpaceShip::Exept &exp)
            {
                throw(exp);
            }
        }
    }
}

int MonsterLine::getDirection()
{
    return (this->direction);
}

int MonsterLine::getNumberOfMonster()
{
    return (this->numberOfMonster);
}

MonsterLine::~MonsterLine()
{
    if (block != nullptr)
    {
        for (int i = 0; i < this->numberOfMonster; i++)
        {
            delete block[i];
        }
        delete[] block;
    }
}
