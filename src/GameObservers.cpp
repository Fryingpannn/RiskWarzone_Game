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
#include <list>
#include "Player.h"

#include "GameObservers.hpp"

/////////////////////////////////////////////
// Observer Class
/////////////////////////////////////////////

Observer::Observer()
{
    // std::cout << "Observer constructor" << std::endl;
}

Observer::~Observer()
{
    std::cout << "Observer destructor" << std::endl;
}

/////////////////////////////////////////////
// Subject Class
/////////////////////////////////////////////
Subject::Subject()
{
    _observers = new std::list<Observer *>;
}
void Subject::Attach(Observer *o)
{
    _observers->push_back(o);
}

void Subject::Detach(Observer *o)
{
    _observers->remove(o);
}

void Subject::Notify()
{
    std::list<Observer *>::iterator i = _observers->begin();
    for (; i != _observers->end(); ++i)
    {
        (*i)->Update();
    }
}

Subject::~Subject()
{
    std::cout << "Deleting Observer Subject" << std::endl;
    delete _observers;
}

void Subject::setState(State_enum new_state)
{
    current_state = new_state;
};
State_enum Subject::getState()
{
    State_enum returnState = current_state;
    return returnState;
};

/////////////////////////////////////////////
// PhaseObserver Class
/////////////////////////////////////////////

PhaseObserver::PhaseObserver(Subject *passed_phase_subject)
{
    _phase_subject = passed_phase_subject;
    _phase_subject->Attach(this);
}

void PhaseObserver::Update()
{
    // std::cout << "Game Statistics Observer Updating" << std::endl;
    switch (_phase_subject->getState())
    {
    case State_enum::SETUP_PHASE:
        std::cout << "[Phase Observer] Setup Phase " << std::endl;
        break;
    case State_enum::REINFORCEMENT_PHASE:
        std::cout << "[Phase Observer] Reinforcement Phase " << std::endl;
        break;
    case State_enum::ISSUE_ORDERS_PHASE:
        std::cout << "[Phase Observer] Issue Orders Phase " << std::endl;
        break;
    case State_enum::EXECUTE_ORDERS_PHASE:
        std::cout << "[Phase Observer] Execute Orders Phase " << std::endl;
        break;
    default:
        break;
    }
}

PhaseObserver::~PhaseObserver()
{
    std::cout << "Deleting PhaseObserver" << std::endl;
    _phase_subject->Detach(this);
}

/////////////////////////////////////////////
// Game Statistics Observer Class
/////////////////////////////////////////////

GameStatisticsObserver::GameStatisticsObserver(Subject *passed_game_observer_subject)
{
    _game_observer_subject = passed_game_observer_subject;
    _game_observer_subject->Attach(this);
}

void GameStatisticsObserver::Update()
{
    // std::cout << "Phase Observer Updating" << std::endl;

    // switch (new_state)
    // {
    // case State_enum::TERRITORY_CONQUERED:
    //     std::cout << "[Game Statistics Observer] Territory Conquered" << std::endl;
    //     break;
    // case State_enum::PLAYER_ELIMINATED:
    //     std::cout << "[Game Statistics Observer] Player Eliminated" << std::endl;
    //     break;
    // case State_enum::PLAYER_OWNS_ALL_TERRITORIES:
    //     std::cout << "[Game Statistics Observer] Player Owns All Territories. Game Won." << std::endl;
    //     break;
    // default:
    //     break;
    // }
}

GameStatisticsObserver::~GameStatisticsObserver()
{
    std::cout << "Deleting GameStatisticsObserver." << std::endl;
    _game_observer_subject->Detach(this);
}
