/**
 * @file LetterGroup.hpp
 * @brief Defines the LetterGroup class and its associated letter classes (A, E, G, M, N, O, R, U, V, W, Y, Exclamation).
 * 
 * This file provides the declaration of the `LetterGroup` class, which manages a group of letters
 * drawn on a window. Each letter is represented as a set of points, and the group can render the letters
 * on the screen using SFML. The letter shapes are predefined, and each letter (A, E, G, M, N, O, R, U, V, W, Y, Exclamation)
 * is implemented as a subclass of the `Letter` class.
 * 
 * The `LetterGroup` class provides functionality to initialize the group with a specific color and window dimensions,
 * draw the group to the screen, and manage the destruction of all letters within the group.
 * 
 * @version 1.0
 * @date 2024-12-08
 */


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
        /**
         * @brief Constructs a letter with specific coordinates, color, number of points, and width.
         * @param x The x-coordinate of the letter.
         * @param y The y-coordinate of the letter.
         * @param colour The color of the letter.
         * @param numberOfPoint The number of points defining the letter.
         * @param width The width of the letter.
         */
        Letter(float x, float y, string color, int numberOfPoint, int width);
        /**
         * @brief Destroys the letter and deallocates its associated points.
         */
        ~Letter();
        friend LetterGroup;
        /**
         * @brief Gets the width of the letter.
         * @return The width of the letter.
         */
        int getWidth();
        /**
         * @brief Gets the x-coordinate of the letter.
         * @return The x-coordinate of the letter.
         */
        float getX();
        /**
         * @brief Gets the y-coordinate of the letter.
         * @return The y-coordinate of the letter.
         */
        float getY();
        /**
         * @brief Gets the number of points in the letter.
         * @return The number of points.
         */
        int getNumberOfPoint();
    };

    class G : public Letter
    {
    public:
        /**
         * @brief Constructs the letter G with a predefined shape.
         * @param x The x-coordinate of the letter G.
         * @param y The y-coordinate of the letter G.
         * @param colour The color of the letter G.
         */
        G(float x, float y, string colour);
        /**
         * @brief Destroys the letter G.
         */
        ~G();
    };

    class Exclamation : public Letter
    {
    public:
        /**
         * @brief Constructs the letter Exclamation with a predefined shape.
         * @param x The x-coordinate of the letter Exclamation.
         * @param y The y-coordinate of the letter Exclamation.
         * @param colour The color of the letter Exclamation.
         */
        Exclamation(float x, float y, string colour);
        /**
         * @brief Destroys the character Exclamation.
         */
        ~Exclamation();
    };
    class A : public Letter
    {
    public:
        /**
         * @brief Constructs the letter A with a predefined shape.
         * @param x The x-coordinate of the letter A.
         * @param y The y-coordinate of the letter A.
         * @param colour The color of the letter A.
         */
        A(float x, float y, string colour);
        /**
         * @brief Destroys the letter A.
         */
        ~A();
    };

    class M : public Letter
    {
    public:
        /**
         * @brief Constructs the letter M with a predefined shape.
         * @param x The x-coordinate of the letter M.
         * @param y The y-coordinate of the letter M.
         * @param colour The color of the letter M.
         */
        M(float x, float y, string colour);
        /**
         * @brief Destroys the letter M.
         */
        ~M();
    };
    class E : public Letter
    {
    public:
        /**
         * @brief Constructs the letter E with a predefined shape.
         * @param x The x-coordinate of the letter E.
         * @param y The y-coordinate of the letter E.
         * @param colour The color of the letter E.
         */
        E(float x, float y, string colour);
        /**
         * @brief Destroys the letter E.
         */
        ~E();
    };

    class O : public Letter
    {
    public:
        /**
         * @brief Constructs the letter O with a predefined shape.
         * @param x The x-coordinate of the letter O.
         * @param y The y-coordinate of the letter O.
         * @param colour The color of the letter O.
         */
        O(float x, float y, string colour);
        /**
         * @brief Destroys the letter O.
         */
        ~O();
    };

    class V : public Letter
    {
    public:
        /**
         * @brief Constructs the letter V with a predefined shape.
         * @param x The x-coordinate of the letter V.
         * @param y The y-coordinate of the letter V.
         * @param colour The color of the letter V.
         */
        V(float x, float y, string colour);
        /**
         * @brief Destroys the letter V.
         */
        ~V();
    };

    class R : public Letter
    {
    public:
        /**
         * @brief Constructs the letter R with a predefined shape.
         * @param x The x-coordinate of the letter R.
         * @param y The y-coordinate of the letter R.
         * @param colour The color of the letter R.
         */
        R(float x, float y, string colour);
        /**
         * @brief Destroys the letter R.
         */
        ~R();
    };

    class Y : public Letter
    {
    public:
        /**
         * @brief Constructs the letter Y with a predefined shape.
         * @param x The x-coordinate of the letter Y.
         * @param y The y-coordinate of the letter Y.
         * @param colour The color of the letter Y.
         */
        Y(float x, float y, string colour);
        /**
         * @brief Destroys the letter Y.
         */
        ~Y();
    };

    class U : public Letter
    {
    public:
        /**
         * @brief Constructs the letter U with a predefined shape.
         * @param x The x-coordinate of the letter U.
         * @param y The y-coordinate of the letter U.
         * @param colour The color of the letter U.
         */
        U(float x, float y, string colour);
        /**
         * @brief Destroys the letter U.
         */
        ~U();
    };

    class W : public Letter
    {
    public:
        /**
         * @brief Constructs the letter W with a predefined shape.
         * @param x The x-coordinate of the letter W.
         * @param y The y-coordinate of the letter W.
         * @param colour The color of the letter W.
         */
        W(float x, float y, string colour);
        /**
         * @brief Destroys the letter W.
         */
        ~W();
    };

    class N : public Letter
    {
    public:
        /**
         * @brief Constructs the letter N with a predefined shape.
         * @param x The x-coordinate of the letter N.
         * @param y The y-coordinate of the letter N.
         * @param colour The color of the letter N.
         */
        N(float x, float y, string colour);
        /**
         * @brief Destroys the letter N.
         */
        ~N();
    };

    float winW, winH;
    Letter **lettersList;
    int numberOfLetter;
    const int big_space = 4;
    const int small_space = 1;
    string colorGrp;

public:
    /**
     * @brief Constructs a letter group with a specified color and window dimensions.
     * @param groupColour The color for the entire letter group.
     * @param windowWidth The width of the rendering window.
     * @param windowHeight The height of the rendering window.
     */
    LetterGroup(string groupColour, float windowWidth, float windowHeight);
    /**
     * @brief Draws the letter group onto the target.
     * @param target The render target to draw on.
     * @param states The render states to apply during drawing.
     */
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;
    /**
     * @brief Destroys the letter group and deallocates all associated letters.
     */
    ~LetterGroup();
};

#endif