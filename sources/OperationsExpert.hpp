#pragma once

#include <string>
#include <utility>
#include "Player.hpp"
#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"

namespace pandemic{
    class OperationsExpert: public Player{
        std::string roleName;
    public:
        OperationsExpert(Board& b,City c): Player(b,c), roleName("OperationsExpert"){};

        Player& build() override;
        std::string role() override;
    };
}