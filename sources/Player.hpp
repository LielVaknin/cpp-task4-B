#pragma once

#include <string>
#include <utility>
#include <array>
#include <vector>
#include <stdexcept>
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include <array>

const int cardsSize = 48;
const int fiveCards = 5;

namespace pandemic{
    class Player{

    protected:
        Board& board;
        City currentCity;
        std::array <bool, cardsSize> cards;
        std::map<pandemic::Color, int> numOfCardsEachColor;

    public:
        Player(Board &b,City c): board(b), currentCity(c), cards({false}), numOfCardsEachColor({{Blue, 0}, {Yellow, 0}, {Black, 0}, {Red, 0}}){};
        virtual ~Player() = default;

        virtual Player& drive(City c);
        virtual Player& fly_direct(City c);
        virtual Player& fly_charter(City c);
        virtual Player& fly_shuttle(City c);
        virtual Player& build();
        virtual Player& discover_cure(Color c);
        virtual Player& treat(City c);
        virtual std::string role() = 0; // Pure virtual method - so you can not create an object of type Player
        Player& take_card(City c);
        void remove_cards();
    };
}