#include "Medic.hpp"

using namespace pandemic;
using namespace std;

Player &Medic::treat(City c) {
    if (c != currentCity) {
        throw invalid_argument{"illegal action: you are not in " + pandemic::printCity(c)};
    }
    if (this->board.board.at(c).diseaseLevel == 0) {
        throw invalid_argument{"illegal action: no more cubes remain in " + pandemic::printCity(c)};
    }
    this->board.board.at(c).diseaseLevel = 0;
    return *this;
}

Player &Medic::drive(City c) {
    if(c == currentCity){
        throw invalid_argument{"illegal action: you can not drive to " + pandemic::printCity(c) + " " + ",you are already in it!"};
    }
    vector<City> vec = this->board.board.at(this->currentCity).cityNeighbours;
    auto it = find(vec.begin(), vec.end(), c);
    if (it == vec.end()) {
        throw invalid_argument{
                " illegal action: " + pandemic::printCity(c) + " is not connected to " +
                pandemic::printCity(currentCity)};
    }
    currentCity = c;
    if (this->board.discoveredCuresInColors.at(this->board.board.at(currentCity).color)) {
        this->board.board.at(currentCity).diseaseLevel = 0;
    }
    return *this;
}

Player &Medic::fly_direct(City c) {
    if(c == currentCity){
        throw invalid_argument{"illegal action: you can not fly to " + pandemic::printCity(c) + " " + ",you are already in it!"};
    }
    if (!cards.at(c)) {
        throw invalid_argument{"illegal action: you do not have the card of " + pandemic::printCity(c)};
    }
    cards.at(c) = false;
    numOfCardsEachColor.at(this->board.board.at(c).color)--;
    currentCity = c;
    if (this->board.discoveredCuresInColors.at(this->board.board.at(currentCity).color)) {
        this->board.board.at(currentCity).diseaseLevel = 0;
    }
    return *this;
}

Player &Medic::fly_charter(City c) {
    if(c == currentCity){
        throw invalid_argument{"illegal action: you can not fly to " + pandemic::printCity(c) + " " + ",you are already in it!"};
    }
    if (!cards.at(currentCity)) {
        throw invalid_argument{"illegal action: you do not have the " + pandemic::printCity(currentCity) +
                               " card (the card of the city you are in)."};
    }
    cards.at(currentCity) = false;
    numOfCardsEachColor.at(this->board.board.at(currentCity).color)--;
    currentCity = c;
    if (this->board.discoveredCuresInColors.at(this->board.board.at(currentCity).color)) {
        this->board.board.at(currentCity).diseaseLevel = 0;
    }
    return *this;
}

Player &Medic::fly_shuttle(City c) {
    if(c == currentCity){
        throw invalid_argument{"illegal action: you can not fly to " + pandemic::printCity(c) + " " + ",you are already in it!"};
    }
    if (!this->board.board.at(c).researchStation) {
        throw invalid_argument{"illegal action: there is no research station in " + pandemic::printCity(c)};
    }
    if (!this->board.board.at(currentCity).researchStation) {
        throw invalid_argument{"illegal action: there is no research station in " + pandemic::printCity(currentCity)};
    }
    if (this->board.board.at(currentCity).researchStation && this->board.board.at(c).researchStation) {
        currentCity = c;
        if (this->board.discoveredCuresInColors.at(this->board.board.at(currentCity).color)) {
            this->board.board.at(currentCity).diseaseLevel = 0;
        }
    }
    return *this;
}

std::string Medic::role() {
    return roleName;
}

