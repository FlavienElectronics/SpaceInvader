/*Ajouter des entête sous chaque fichier*/

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
    class A;
    class E;
    class G;
    class M;
    class N;
    class O;
    class R;
    class U;
    class V;
    class W;
    class Y;
    class Exclamation;

    class Letter
    {
    protected:
        float x;
        float y;
        int numberOfPoint;
        int width;
        string colour;
        Point **pt;

    public:
        Letter(float x, float y,string color, int numberOfPoint, int width);
        ~Letter();
        friend LetterGroup;
        int getWidth();
        float getX();
        float getY();
        int getNumberOfPoint();
    };

    class G : public Letter
    {
    public:
        G(float x, float y,string colour);
        ~G();
    };

        class Exclamation : public Letter
    {
    public:
        Exclamation(float x, float y,string colour);
        ~Exclamation();
    };
    class A : public Letter
    {
    public:
        A(float x, float y,string colour);
        ~A();
    };

    class M : public Letter
    {
    public:
        M(float x, float y,string colour);
        ~M();
    };
    class E : public Letter
    {
    public:
        E(float x, float y,string colour);
        ~E();
    };

    class O : public Letter
    {
    public:
        O(float x, float y,string colour);
        ~O();
    };

    class V : public Letter
    {
    public:
        V(float x, float y,string colour);
        ~V();
    };

    class R : public Letter
    {
    public:
        R(float x, float y,string colour);
        ~R();
    };

    class Y : public Letter
    {
    public:
        Y(float x, float y,string colour);
        ~Y();
    };

    class U : public Letter
    {
    public:
        U(float x, float y,string colour);
        ~U();
    };

    class W : public Letter
    {
    public:
        W(float x, float y,string colour);
        ~W();
    };

    class N : public Letter
    {
    public:
        N(float x, float y,string colour);
        ~N();
    };

    float winW, winH;
    Letter **lettersList;
    int numberOfLetter;
    const int big_space = 4;
    const int small_space = 1;
    string colorGrp;

public:
    LetterGroup(string groupColour, float windowWidth, float windowHeight);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    ~LetterGroup();
};

#endif