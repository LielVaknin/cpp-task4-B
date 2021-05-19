#pragma once

#include <string>
#include <utility>
#include <stdexcept>
#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic{
    class Virologist: public Player{
        std::string roleName;
    public:
        Virologist(Board& b,City c): Player(b,c), roleName("Virologist"){};

        Player& treat(City c) override;
        std::string role() override;
    };
}