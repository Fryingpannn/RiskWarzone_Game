/////////////////////////////////////////////
// Filename:        GameObservers.cpp
//
// Description:     Implementation of the Observer class
//                    and associated functionality
//
// Author:          Stefan Russo - 26683320
//
// Group:           Sandra Buchen - 26317987
//                  Le Cherng Lee - 40122814
//                  Zahra Nikbakht - 40138253
//                  Matthew Pan - 40135588
//                  Stefan Russo - 26683320
//
/////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <vector>
#include "GameObservers.hpp"

Observer::~Observer() {
    std::cout << "Observer destructor" << std::endl;
}

void Subject::attach(Observer *o) { obs.push_back(o); }

void Subject::detach(Observer *o)
{
    obs.erase(std::remove(obs.begin(), obs.end(), o), obs.end());
}

void Subject::notify(State_enum new_state)
{
    // Copy the current observer list to a clone to avoid one being deleted mid-operation
    // std::vector<Observer *> obs_clone;
    // for (auto obs_item : obs)
    //     obs_clone.push_back(new Observer(*obs_item));

    // Update all the observers
    for (auto o : obs)
    {
        o->update(new_state);
    }

    // Delete the clone
    // for (auto o : obs_clone)
    //     delete o;
    // obs_clone.clear();
}

Subject::~Subject()
{
    std::cout << "Deleting Observer Subject" << std::endl;
}



// class ConcreteSubject : public Subject
// {
//     int state = 0;

// public:
//     ConcreteSubject(int i) : state(i){};

//     void setState(int i) { state = i; };

//     int getState() { return state; };

//     void notify()
//     {
//         // Copy the current observer list to a clone to avoid one being deleted mid-operation
//         std::vector<Observer *> obs_clone;
//         for (auto obs_item : obs)
//             obs_clone.push_back(new Observer(*obs_item));

//         // Update all the observers
//         for (auto o : obs_clone)
//         {
//             o->update();
//         }

//         // Delete the clone
//         for (auto o : obs_clone)
//             delete o;
//         obs_clone.clear();
//     }

//     virtual ~ConcreteSubject() {
//         std::cout << "Deleting ConcreteSubject" << std::endl;
//     }
// };

PhaseObserver::PhaseObserver(Subject *passed_phase_subject)
{
    phase_subject = passed_phase_subject;
}

void PhaseObserver::update(State_enum new_state)
{
    
    std::cout << "Game Statistics Observer Updating" << std::endl;
    switch (new_state)
    {
    case State_enum::SETUP_PHASE :
        std::cout << "[Phase Observer] Setup Phase " << std::endl;
        break;
    case State_enum::REINFORCEMENT_PHASE :
        std::cout << "[Phase Observer] Reinforcement Phase " << std::endl;
        break;
    case State_enum::ISSUE_ORDERS_PHASE :
        std::cout << "[Phase Observer] Issue Orders Phase " << std::endl;
        break;
    case State_enum::EXECUTE_ORDERS_PHASE :
        std::cout << "[Phase Observer] Execute Orders Phase " << std::endl;
        break;
    default:
        break;
    }
}

PhaseObserver::~PhaseObserver()
{
    std::cout << "Deleting PhaseObserver" << std::endl;
}

GameStatisticsObserver::GameStatisticsObserver(Subject *passed_game_observer_subject)
{
    game_observer_subject = passed_game_observer_subject;
}

void GameStatisticsObserver::update(State_enum new_state)
{
    std::cout << "Phase Observer Updating" << std::endl;

    switch (new_state)
    {
    case State_enum::TERRITORY_CONQUERED :
        std::cout << "[Game Statistics Observer] Territory Conquered" << std::endl;
        break;
    case State_enum::PLAYER_ELIMINATED :
        std::cout << "[Game Statistics Observer] Player Eliminated" << std::endl;
        break;
    case State_enum::PLAYER_OWNS_ALL_TERRITORIES :
        std::cout << "[Game Statistics Observer] Player Owns All Territories. Game Won." << std::endl;
        break;    
    default:
        break;
    }
}

GameStatisticsObserver::~GameStatisticsObserver()
{
    std::cout << "Deleting GameStatisticsObserver." << std::endl;
}
