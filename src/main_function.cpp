#include "main_function.hpp"

void init(struct main_info &main_information, struct clock_info &clock_information)
{
    cout << "Restarting the game" << endl;

    clock_information.delayCommand = sf::milliseconds(10);
    clock_information.delayProjectile = sf::milliseconds(10);
    clock_information.delayMonster = sf::milliseconds(50);
    clock_information.delayShoot = sf::milliseconds(500);
    clock_information.delayExplosion = sf::milliseconds(150);
    clock_information.delayRefreshScreen = sf::milliseconds(17);

    main_information.endScreenPrinted = false;
    main_information.shipDestroyed = false;
    *main_information.ship = new SpaceShip(&main_information.win, main_information.winH, main_information.winW, main_information.winW / 2, main_information.winH / 1.2, "col");
    *main_information.monsterL = new MonsterLine *[main_information.numberOfLine];
    *main_information.explo = new bool *[main_information.numberOfLine];
    for (int i = 0; i < main_information.numberOfLine; i++)
    {
        (*main_information.explo)[i] = nullptr;
        (*main_information.monsterL)[i] = new MonsterLine(&main_information.win, main_information.winH, main_information.winW, main_information.winW / 2 - (1 + i * 2 * 4), main_information.winH / 2 - (1 + i * 2 * 4), i * 2 + 1, "col");
    }
    main_information.change = false;
    main_information.allMonsDestroyed = false;

    /* Sending to esp the initialisation signal*/
    if (main_information.uControler.isConnected())
    {
        string messageToESP = "[RST]";
        main_information.uControler.sendUSART(messageToESP);
    }
}

/*Delete monsters line allocated, ship allocated and explosion bool vector*/
void freeMem(main_info &main_information)
{
    // Delete allocated ship
    delete (*main_information.ship);
    // Delete allocated monsters line
    for (int j = 0; j < main_information.numberOfLine; j++)
    {
        delete (*main_information.monsterL)[j];

        // Delete allocated bool vector
        if ((*main_information.explo)[j] != nullptr)
        {
            delete (*main_information.explo)[j];
        }
    }
}

void manageKeyboard(main_info &main_information, clock_info &clock_information)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        try
        {
            (*main_information.ship)->xAdd();
        }
        catch (SpaceShip::Exept exp)
        {
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        try
        {
            (*main_information.ship)->xSub();
        }
        catch (SpaceShip::Exept exp)
        {
        }
    }

    /*Managing the shooting*/
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        if (clock_information.clockShoot.getElapsedTime() >= clock_information.delayShoot)
        {
            (*main_information.ship)->shoot();
            for (int j = 0; j < main_information.numberOfLine; j++)
            {
                for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
                {
                    Monster &tempMonster = (*(*main_information.monsterL)[j])[i];
                    if (tempMonster.isAlive())
                    {
                        tempMonster.shoot();
                    }
                }
            }
            //cout << clock_information.clockShoot.getElapsedTime().asMilliseconds() << endl;
            clock_information.clockShoot.restart(); // Redémarre l'horloge pour le prochain intervalle
        }
    }
}

void updateCollision(main_info &main_information)
{
    for (int j = 0; j < main_information.numberOfLine; j++)
    {

        if ((*main_information.monsterL)[j] != nullptr)
        {
            (*main_information.monsterL)[j]->updateCollision(*(*main_information.ship), &(*main_information.explo)[j]);
        }
    }
}

void detectImpact(main_info &main_information)
{
    main_information.shipDestroyed = (*main_information.ship)->detectImpact((*main_information.monsterL), main_information.numberOfLine);
}

void updateProjectile(main_info &main_information, clock_info &clock_information)
{
    /*Managing the projectile*/
    if (clock_information.clockProjectile.getElapsedTime() >= clock_information.delayProjectile)
    {
        (*main_information.ship)->updateProjectiles();
        for (int j = 0; j < main_information.numberOfLine; j++)
        {
            for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
            {
                Monster &tempMonster = (*(*main_information.monsterL)[j])[i];
                tempMonster.updateProjectiles();
            }
        }
        clock_information.clockProjectile.restart();
    }
}

void manageMonsters(main_info &main_information, clock_info &clock_information)
{
    /*Managing the monsters's movement*/
    if (clock_information.clockMonster.getElapsedTime() >= clock_information.delayMonster)
    {
        for (int j = 0; j < main_information.numberOfLine; j++)
        {
            if ((*main_information.monsterL)[j]->getDirection() == 0) // go left
            {
                try
                {
                    (*main_information.monsterL)[j]->xSub();
                }
                catch (SpaceShip::Exept &exp)
                {
                    main_information.change = true;
                }
            }
            else if ((*main_information.monsterL)[j]->getDirection() == 1) // go right
            {
                try
                {
                    (*main_information.monsterL)[j]->xAdd();
                }
                catch (SpaceShip::Exept &exp)
                {
                    main_information.change = true;
                }
            }

            if (main_information.change)
            {
                (*main_information.monsterL)[j]->changeDirection();
                main_information.change = false;
            }
        }

        /*Checking if all monsters are dead*/
        for (int i = 0; i < main_information.numberOfLine; i++)
        {
            if (!(*main_information.monsterL)[i]->isLineDestoyed())
            {
                break;
            }
            else
            {
                if (i == (main_information.numberOfLine - 1))
                {
                    main_information.allMonsDestroyed = true;
                }
            }
        }
        // cout << clock_information.clockMonster.getElapsedTime().asMilliseconds() << endl;
        clock_information.clockMonster.restart();
    }
}

void manageExplosion(main_info &main_information, clock_info &clock_information)
{
    /*Explosion management*/
    for (int j = 0; j < main_information.numberOfLine; j++)
    {
        if (*main_information.explo != nullptr)
        {
            if ((*main_information.explo)[j] != nullptr)
            {
                for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
                {
                    // Check if we should update the explosion particles
                    Monster &tempMonster = (*(*main_information.monsterL)[j])[i];
                    if ((*main_information.monsterL)[j]->isExplosing(i) && tempMonster.getElapsedTimeClockExplosion() >= clock_information.delayExplosion)
                    {
                        (*main_information.monsterL)[j]->updateParticule(i);
                        tempMonster.resetClockExplosion();
                    }

                    // Only trigger an explosion if needed and the monster is alive
                    if ((*main_information.explo)[j][i] && (*main_information.monsterL)[j]->isAlive(i))
                    {
                        (*main_information.monsterL)[j]->explode(i); // Start explosion
                        // cout << "Monster " << i << " in line " << j << " exploded." << endl;
                        clock_information.clockExplosion.restart(); // Only reset timer when an explosion starts
                    }
                }
            }
        }
    }
}

void displayGame(main_info &main_information, clock_info &clock_information)
{
    if (clock_information.clockRefreshScreen.getElapsedTime() >= clock_information.delayRefreshScreen)
    {
        // Erase the screen in white
        main_information.win.clear(sf::Color::White);

        /*Displaying ship and monsters*/
        main_information.win.draw(*(*main_information.ship));
        for (int j = 0; j < main_information.numberOfLine; j++)
        {
            for (int i = 0; i < (*main_information.monsterL)[j]->getNumberOfMonster(); i++)
            {
                main_information.win.draw((*(*main_information.monsterL)[j])[i]);
            }
        }
        main_information.win.display();
        clock_information.clockRefreshScreen.restart();
    }
}