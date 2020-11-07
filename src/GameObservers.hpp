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
public:
    virtual void update(State_enum new_state) = 0;
    virtual ~Observer();
};

class Subject
{
private:
    State_enum state = State_enum::DEFAULT_NO_STATE;
    // int state = 0;

protected:
    std::vector<Observer *> obs;

public:
    void attach(Observer *o);

    void detach(Observer *o);

    void notify(State_enum new_state);
    ~Subject();
};

// class ConcreteSubject : public Subject
// {
//     int state = 0;

// public:
//     ConcreteSubject(int i) : state(i){};

//     void setState(int i);

//     int getState() { return state; };

//     void notify();

//     virtual ~ConcreteSubject();
// };

class PhaseObserver : Observer
{
    Subject *phase_subject;

public:
    PhaseObserver(Subject *passed_phase_subject);

    void update(State_enum new_state);

    ~PhaseObserver();
};

class GameStatisticsObserver : Observer
{
    Subject *game_observer_subject;

public:
    GameStatisticsObserver(Subject *passed_game_observer_subject);

    void update(State_enum new_state);

    ~GameStatisticsObserver();
};