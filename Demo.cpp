#include "Board.hpp"
#include "City.hpp"
#include "Color.hpp"
#include "OperationsExpert.hpp"
#include "Dispatcher.hpp"
#include "Scientist.hpp"
#include "Researcher.hpp"
#include "Medic.hpp"
#include "Virologist.hpp"
#include "GeneSplicer.hpp"
#include "FieldDoctor.hpp"
#include <iostream>

using namespace pandemic;
using namespace std;

int main() {
    Board board; // Initialize an empty board (with 0 disease cubes in any city).
    cout << boolalpha << board.is_clean() << endl; // Prints true
    board[City::HongKong] = 3; // put 3 red disease cubes in HongKong.
    board[City::HongKong] = 2; // change number of disease cubes in HongKong to 2.
    board[City::LosAngeles] = 4; // put 4 yellow disease cubes in LosAngeles.
    board[City::Milan] = 1; // put 1 blue disease cube in Milan.
    board[City::Madrid] = 1; // put 1 blue disease cube in Madrid.
    board[City::Sydney] = 2; // put 2 red disease cubes in Sydney.

    OperationsExpert operations_expert{board, City::HongKong}; // Red city
    cout << boolalpha << (operations_expert.role() == "OperationsExpert") << endl; // Prints true
    Dispatcher dispatcher{board, City::Bangkok}; // Red city
    cout << boolalpha << (dispatcher.role() == "Dispatcher") << endl; // Prints true
    Scientist scientist{board, City::Shanghai, 2}; // Red city
    cout << boolalpha << (scientist.role() == "Scientist") << endl; // Prints true
    Researcher researcher{board, City::Madrid}; // Blue city
    cout << boolalpha << (researcher.role() == "Researcher") << endl; // Prints true
    Medic medic{board, City::Milan}; // Blue city
    cout << boolalpha << (medic.role() == "Medic") << endl; // Prints true
    Virologist virologist{board, City::Miami}; // Yellow city
    cout << boolalpha << (virologist.role() == "Virologist") << endl; // Prints true
    GeneSplicer geneSplicer{board, City::Santiago}; // Yellow city
    cout << boolalpha << (geneSplicer.role() == "GeneSplicer") << endl; // Prints true
    FieldDoctor fieldDoctor{board, City::LosAngeles}; // Yellow city
    cout << boolalpha << (fieldDoctor.role() == "FieldDoctor") << endl; // Prints true


    cout << "------------------------ OperationsExpert ------------------------" << endl;

    operations_expert.take_card(Jakarta).take_card(HoChiMinhCity).take_card(Beijing); // Takes 3 red cards
    operations_expert.build(); // Builds a research station in HongKong
    cout << boolalpha << board.board.at(
            HongKong).researchStation << endl; // Prints true - OperationsExpert can build a research station without the card of HongKong
    operations_expert.remove_cards();

    cout << "------------------------ Dispatcher ------------------------" << endl;

    try {
        dispatcher.drive(LosAngeles); // LosAngeles is not connected to Bangkok
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl;  // Prints illegal action: LosAngeles is not connected to Bangkok
    }

    try {
        dispatcher.drive(Bangkok); // Dispatcher can not drive to Bangkok, he is already there
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl;  // Prints illegal action: you can not drive to Bangkok ,you are already in it!
    }
    dispatcher.drive(HongKong); // HongKong is connected to Bangkok, now dispatcher is in a city with a research station
    try {
        dispatcher.fly_direct(HongKong); // Dispatcher can not fly to HongKong, he is already there
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl;  // Prints illegal action: you can not fly to HongKong ,you are already in it!
    }
    dispatcher.fly_direct(
            London); // Dispatcher can perform a "fly direct" operation without throwing the card of London because he is in a city with a research station.
    dispatcher.take_card(London);
    dispatcher.fly_charter(
            Bangkok); // Now Dispatcher is in a city without a research station by throwing the current city card (London)
    try {
        dispatcher.fly_direct(
                Jakarta); // Now Dispatcher is in a city without a research station so he can not fly without the card of Jakarta
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: you do not have the card of Jakarta
    }
    cout << "------------------------ Scientist ------------------------" << endl;

    scientist.take_card(Seoul).take_card(Tokyo); // Takes 2 red cards
    try {
        scientist.discover_cure(Red); // Can not discover cure, Scientist is not in a city with a research station
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints there is no research station!, you can not discover cure
    }
    scientist.remove_cards();
    try {
        scientist.build(); // Can not build a research station in Shanghai without throwing the card of it
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: you do not have the Shanghai card so you can not build a research station!
    }
    scientist.take_card(Shanghai);
    scientist.build(); // Builds a research station in Shanghai with throwing the appropriate card
    cout << boolalpha << board.board.at(Shanghai).researchStation << endl; // Prints true
    scientist.take_card(Seoul); // Takes 1 red card
    try {
        scientist.discover_cure(Red); // Can not discover cure with 1 red card
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: you only have 1 Red cards remaining
    }
    scientist.take_card(Tokyo); // Takes 1 more red card - now there are 2 red cards
    scientist.discover_cure(Red); // Can discover cure with n=2 red cards
    cout << boolalpha << board.discoveredCuresInColors.at(Red) << endl; // Prints true
    scientist.remove_cards();

    cout << "------------------------ Researcher ------------------------" << endl;

    researcher.take_card(Atlanta).take_card(Chicago).take_card(Essen).take_card(Milan); // Takes 4 blue cards
    try {
        researcher.discover_cure(Blue); // There are not enough cards for discovering a blue cure
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // illegal action: you only have 4 Blue cards remaining
    }
    researcher.take_card(Montreal); // Now there are 5 blue cards
    researcher.discover_cure(
            Blue); // Can discover cure with 5 blue cards and without being in a city with a research station
    cout << boolalpha << board.discoveredCuresInColors.at(Blue) << endl; // Prints true
    researcher.remove_cards();

    cout << "------------------------ Medic ------------------------" << endl;

    try {
        medic.treat(Montreal);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: you are not in Montreal
    }
    board[City::Milan] = 0;
    try {
        medic.treat(Milan);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: no more cubes remain in Milan
    }
    board[City::Milan] = 1;
    medic.treat(Milan);
    cout << boolalpha << (board.board.at(Milan).diseaseLevel == 0)
         << endl; // Prints true - there is a blue cure so diseaseLevel in Milan is 0 now
    board[City::Atlanta] = 3;
    board[City::Chicago] = 4;
    board[City::Essen] = 5;
    board[City::Milan] = 2;
    medic.take_card(Atlanta).take_card(Essen).take_card(Milan); // Takes 3 blue cards
    try {
        medic.drive(Milan);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: you can not drive to Milan ,you are already in it!
    }
    try {
        medic.drive(LosAngeles);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: LosAngeles is not connected to Milan
    }
    medic.drive(Essen); // Essen is connected to Milan
    cout << boolalpha << (board.board.at(Essen).diseaseLevel == 0)
         << endl; // Prints true - there is a blue cure so diseaseLevel in Essen is 0 now
    try {
        medic.fly_direct(Essen); // Medic can not fly to Essen, he is already there
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: you can not fly to Essen ,you are already in it!
    }
    try {
        medic.fly_direct(Chicago); // illegal action: medic do not have the card of Chicago
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: you do not have the card of Chicago
    }
    medic.take_card(Chicago);
    medic.fly_direct(Chicago);
    cout << boolalpha << (board.board.at(Chicago).diseaseLevel == 0)
         << endl; // Prints true - there is a blue cure so diseaseLevel in Chicago is 0 now
    try {
        medic.fly_charter(Chicago); // Medic can not fly to Chicago, he is already there
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: you can not fly to Chicago ,you are already in it!
    }
    try {
        medic.fly_charter(
                Montreal); // Medic can not fly to Montreal because he does not have the card of his current city (Chicago) to throw
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: you do not have the Chicago card (the card of the city you are in).
    }
    medic.take_card(Chicago);
    medic.fly_charter(Atlanta);
    cout << boolalpha << (board.board.at(Atlanta).diseaseLevel == 0)
         << endl; // Prints true - there is a blue cure so diseaseLevel in Atlanta is 0 now
    try {
        medic.fly_shuttle(Atlanta); // Medic can not fly to Atlanta, he is already there
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: you can not fly to Atlanta ,you are already in it!
    }
    try {
        medic.fly_shuttle(LosAngeles); // There is no research station in LosAngeles and the current city (Atlanta)
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: there is no research station in LosAngeles
    }
    operations_expert.take_card(Milan).take_card(Atlanta);
    operations_expert.fly_direct(Milan);
    operations_expert.build();
    operations_expert.fly_direct(Atlanta);
    operations_expert.build();
    medic.fly_shuttle(Milan); // There is a research station in Atlanta (current city) and in Milan now
    cout << boolalpha << (board.board.at(Milan).diseaseLevel == 0)
         << endl; // Prints true - there is a blue cure so diseaseLevel in Milan is 0 now
    medic.remove_cards();
    operations_expert.remove_cards();

    cout << "------------------------ Virologist ------------------------" << endl;

    try {
        virologist.treat(Miami);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: no more cubes remain in Miami
    }
    board[City::Madrid] = 3;
    try {
        virologist.treat(Madrid); // illegal action: you do not have the card of Madrid
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: you do not have the card of Madrid
    }
    virologist.take_card(Madrid);
    virologist.treat(
            Madrid); // Can perform "treat" operation in any city in the world by throwing the card of this city
    cout << boolalpha << (board.board.at(Madrid).diseaseLevel == 0)
         << endl; // Prints true - there is a blue cure so diseaseLevel in Madrid is 0 now
    virologist.remove_cards();

    cout << "------------------------ GeneSplicer ------------------------" << endl;

    board.discoveredCuresInColors.at(Red) = false; // For testing GeneSplicer

    geneSplicer.take_card(HongKong);
    geneSplicer.fly_direct(
            HongKong); // GeneSplicer can fly to HongKong (a city with a research station) by throwing an appropriate card
    try {
        geneSplicer.discover_cure(Red); // GeneSplicer can not discover cure - needs at least 5 cards
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: you only have 0 cards remaining.
    }
    geneSplicer.take_card(LosAngeles);
    geneSplicer.fly_direct(
            LosAngeles); // GeneSplicer can fly to LosAngeles (a city without a research station) by throwing an appropriate card
    geneSplicer.take_card(Mumbai).take_card(Chicago).take_card(Essen).take_card(MexicoCity).take_card(
            Montreal).take_card(Shanghai); // Takes 6 cards with different colors
    try {
        geneSplicer.discover_cure(
                Red); // Can not discover cure because GeneSplicer is not in a city with a research station
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints there is no research station!, you can not discover cure
    }
    geneSplicer.fly_direct(
            Shanghai); // Fly to Shanghai - a city with a research station, by throwing the card of Shanghai
    geneSplicer.discover_cure(
            Red); // Can discover cure with 5 cards of different colors (not only of the disease's color)
    cout << boolalpha << board.discoveredCuresInColors.at(Red) << endl; // Prints true
    geneSplicer.remove_cards();

    cout << "------------------------ FieldDoctor ------------------------" << endl;

    try {
        fieldDoctor.treat(London);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what() << endl; // Prints illegal action: no more cubes remain in London
    }
    board[City::London] = 3;
    try {
        fieldDoctor.treat(London);
    } catch (const exception &ex) {
        cout << "caught exception: " << ex.what()
             << endl; // Prints illegal action: London is not connected / equals to LosAngeles
    }
    fieldDoctor.treat(Sydney); // Sydney is connected to LosAngeles
    cout << boolalpha << (board.board.at(Sydney).diseaseLevel == 0)
         << endl; // Prints true - diseaseLevel in Sydney is 0 now because there is a cure for red disease already

         cout << "------------------------ The game board ------------------------" << endl;
         cout << board;
}