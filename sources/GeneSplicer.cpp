#include "GeneSplicer.hpp"

using namespace pandemic;
using namespace std;

Player &GeneSplicer::discover_cure(Color c) {
    if (!this->board.board.at(currentCity).researchStation) {
        throw invalid_argument{"there is no research station!, you can not discover cure"};
    }
    int cardsTakenInAllColors = 0;
    for (auto const &color: numOfCardsEachColor) { // Counts the number of cards taken in all colors
        cardsTakenInAllColors += color.second;
    }
    if (numOfCardsEachColor.at(c) < fiveCards && cardsTakenInAllColors < fiveCards) {
        throw invalid_argument{
                "illegal action: you only have " + to_string(cardsTakenInAllColors) + " cards remaining."};
    }
    if (numOfCardsEachColor.at(c) >= fiveCards || cardsTakenInAllColors >= fiveCards){
        if (!this->board.discoveredCuresInColors.at(c)) {
            unsigned index = 0;
            int countsFiveCards = 0;
            for (auto const &city: this->board.board) {
                if (cards.at(index) && countsFiveCards < fiveCards) {
                    cards.at(index) = false;
                    countsFiveCards++;
                    numOfCardsEachColor.at(city.second.color)--;
                }
                index++;
            }
            this->board.discoveredCuresInColors.at(c) = true;
        }
    }
    return *this;
}

std::string GeneSplicer::role() {
    return roleName;
}
