#ifndef GAMEOVER_HPP
#define GAMEOVER_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Point.hpp"

class GameOver : public sf::Drawable
{
private:
    class G;
    class A;
    class M;
    class E;
    class O;
    class V;
    class R;
    class Letter
    {
    protected:
        float x;
        float y;
        int numberOfPoint;
        int width;
        Point **pt;

    public:
        Letter(float x, float y, int numberOfPoint, int width);
        ~Letter();
        friend GameOver;
        friend G;
        friend A;
        friend M;
        friend E;
        friend O;
        friend V;
        friend R;
    };
    class G : public Letter
    {
    public:
        G(float x, float y);
        ~G();
    };
    class A : public Letter
    {
    public:
        A(float x, float y);
        ~A();
    };

    class M : public Letter
    {
    public:
        M(float x, float y);
        ~M();
    };
    class E : public Letter
    {
    public:
        E(float x, float y);
        ~E();
    };

    class O : public Letter
    {
    public:
        O(float x, float y);
        ~O();
    };

    class V : public Letter
    {
    public:
        V(float x, float y);
        ~V();
    };

    class R : public Letter
    {
    public:
        R(float x, float y);
        ~R();
    };

    Letter **lettersGameOver;
    int numberOfLetter;
    float winW, winH;

public:
    GameOver(float windowWidth, float windowHeight);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    ~GameOver();
};

#endif