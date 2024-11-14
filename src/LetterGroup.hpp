#ifndef LETTERGROUP_HPP
#define LETTERGROUP_HPP

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Point.hpp"

class LetterGroup : public sf::Drawable
{
protected:
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
        friend LetterGroup;
        friend G;
        friend A;
        friend M;
        friend E;
        friend O;
        friend V;
        friend R;
        int getWidth();
        float getX();
        float getY();
        int getNumberOfPoint();
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

    float winW, winH;
    Letter **lettersList;
    int numberOfLetter;
    const int big_space = 4;
	const int small_space = 1;

public:
    LetterGroup(float windowWidth, float windowHeight);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    ~LetterGroup();

};

#endif