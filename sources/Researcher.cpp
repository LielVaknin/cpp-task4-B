#include "Researcher.hpp"

using namespace pandemic;
using namespace std;

Player &Researcher::discover_cure(Color c) {
    if (numOfCardsEachColor.at(c) < fiveCards) {
        throw invalid_argument{
                "illegal action: you only have " + to_string(numOfCardsEachColor.at(c)) + " " + printColor(c) + " cards remaining."};
    }
    if (!this->board.discoveredCuresInColors.at(c)) {
        unsigned index = 0;
        int countsFiveCards = 0;
        for (auto const &city: this->board.board) {
            if (city.second.color == c && cards.at(index) && countsFiveCards < fiveCards) {
                cards.at(index) = false;
                countsFiveCards++;
            }
            index++;
        }
        numOfCardsEachColor.at(c) -= fiveCards;
        this->board.discoveredCuresInColors.at(c) = true;
    }
    return *this;
}

std::string Researcher::role() {
    return roleName;
}
