/////////////////////////////////////////////
// Filename:        GameObservers.hpp
//
// Description:     Header file for the
//                  Implementation of the Observer class
//                  and associated functionality
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

#pragma once

#include <algorithm>
#include <iostream>
#include <vector>
#include <list>

enum class State_enum {
    DEFAULT_NO_STATE = 0,
    SETUP_PHASE = 1,
    REINFORCEMENT_PHASE = 2,
    ISSUE_ORDERS_PHASE = 3,
    EXECUTE_ORDERS_PHASE = 4,
    TERRITORY_CONQUERED = 5,
    PLAYER_ELIMINATED = 6,
    PLAYER_OWNS_ALL_TERRITORIES = 7
};

struct State
{   
    // TODO Determine what needs to be here
    State_enum current_state;
};

class Observer
{
protected:
    Observer();
public:
    virtual void Update() = 0;
    ~Observer();
};

class Subject
{
private:
    State_enum current_state = State_enum::DEFAULT_NO_STATE;
    // int state = 0;

protected:
    std::list<Observer *> *_observers;

public:
    void Attach(Observer *o);

    void Detach(Observer *o);

    void Notify();
    Subject();
    ~Subject();

    void setState(State_enum new_state);
    State_enum getState();
};


class PhaseObserver : public Observer
{
    Subject *_phase_subject;

public:
    PhaseObserver(Subject *passed_phase_subject);

    void Update();

    ~PhaseObserver();
};

class GameStatisticsObserver : Observer
{
    Subject *_game_observer_subject;

public:
    GameStatisticsObserver(Subject *passed_game_observer_subject);

    void Update();

    ~GameStatisticsObserver();
};