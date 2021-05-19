#include "Scientist.hpp"

using namespace pandemic;
using namespace std;

Player& Scientist::discover_cure(Color c) {
    if (numOfCardsEachColor.at(c) < n) {
        throw invalid_argument{
                "illegal action: you only have " + to_string(numOfCardsEachColor.at(c)) + " " + printColor(c) + " cards remaining."};
    }
    if (!this->board.board.at(currentCity).researchStation) {
        throw invalid_argument{"there is no research station!, you can not discover cure"};
    }
    if (!this->board.discoveredCuresInColors.at(c)) {
        unsigned index = 0;
        int countsFiveCards = 0;
        for (auto const &city: this->board.board) {
            if (city.second.color == c && cards.at(index) && countsFiveCards < n) {
                cards.at(index) = false;
                countsFiveCards++;
            }
            index++;
        }
        numOfCardsEachColor.at(c) -= n;
        this->board.discoveredCuresInColors.at(c) = true;
    }
    return *this;
}

std::string Scientist::role() {
    return roleName;
}

