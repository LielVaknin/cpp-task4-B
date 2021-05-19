#include "Dispatcher.hpp"

using namespace pandemic;
using namespace std;

Player& Dispatcher::fly_direct(City c) {
    if(c == currentCity){
        throw invalid_argument{"illegal action: you can not fly to " + pandemic::printCity(c) + " " + ",you are already in it!"};
    }
    if (this->board.board.at(currentCity).researchStation) {
        currentCity = c;
    }else{
        if (!cards.at(c)) {
            throw invalid_argument{"illegal action: you do not have the card of " + pandemic::printCity(c)};
        }
        cards.at(c) = false;
        numOfCardsEachColor.at(this->board.board.at(c).color)--;
        currentCity = c;
    }
    return *this;
}

std::string Dispatcher::role() {
    return roleName;
}
