#ifndef YOUWON_HPP
#define YOUWON_HPP
#include "LetterGroup.hpp"

class YouWon : public LetterGroup
{
public:
	YouWon(string colour, float windowWidth, float windowHeight);
	~YouWon();
};
#endif