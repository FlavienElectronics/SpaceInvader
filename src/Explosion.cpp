#include "Explosion.hpp"

void Explosion::grow(const Monster &monstr)
{
    /*
    switch (status)
    {
    case -1:
        this->status++;
        // localPoint = new sf::RectangleShape(sf::Vector2f(3, 3));
        if (pt == nullptr)
        {
            pt = new Point *[1];
        }
        pt[0] = new Point(monstr.x + 2, monstr.x + 2, 1, "col");
        break;

    case 0:
        this->status++;
        if (pt[0] != nullptr)
        {
            delete pt[0];
            pt[0] = nullptr;
        }
        if (pt != nullptr)
        {
            delete[] pt;
            pt = nullptr;
        }
        if (pt == nullptr)
        {
            pt = new Point *[3];
        }

        pt[0] = new Point(monstr.x + 2, monstr.y + 1, 1, "col");
        pt[1] = new Point(monstr.x + 1, monstr.y + 2, 1, "col");
        pt[2] = new Point(monstr.x + 3, monstr.y + 2, 1, "col");
        break;

    case 1:
        this->status++;
        for (int i = 0; i < 3; i++)
        {
            if (pt[i] != nullptr)
            {
                delete pt[i];
                pt[i] = nullptr;
            }
        }
        if (pt != nullptr)
        {
            delete[] pt;
            pt = nullptr;
        }
        if (pt == nullptr)
            pt = new Point *[7];
        pt[0] = new Point(monstr.x + 0, monstr.y + 0, 1, "col");
        pt[1] = new Point(monstr.x + 2, monstr.y + 0, 1, "col");
        pt[2] = new Point(monstr.x + 4, monstr.y + 0, 1, "col");
        pt[3] = new Point(monstr.x + 1, monstr.y + 1, 1, "col");
        pt[4] = new Point(monstr.x + 3, monstr.y + 1, 1, "col");
        pt[5] = new Point(monstr.x + 0, monstr.y + 2, 1, "col");
        pt[6] = new Point(monstr.x + 4, monstr.y + 2, 1, "col");
        break;

    case 2:
        this->status++;
        for (int i = 0; i < 7; i++)
        {
            if (pt[i] != nullptr)
            {
                delete pt[i];
                pt[i] = nullptr;
            }
        }
        if (pt != nullptr)
        {
            delete[] pt;
            pt = nullptr;
        }
        break;

    default:
        break;
    }
    */
}