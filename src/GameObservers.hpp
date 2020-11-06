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

#include <algorithm>
#include <iostream>
#include <vector>

struct State
{
    // TODO Determine what needs to be here
};


class Observer
{
public:
    void update();
    virtual ~Observer();
};

class Subject
{
protected:
    std::vector<Observer *> obs;

public:
    void attach(Observer *o);

    void detach(Observer *o);

    virtual void notify() = 0;
    virtual ~Subject();
};



class ConcreteSubject : public Subject
{
    int state = 0;

public:
    ConcreteSubject(int i) : state(i){};

    void setState(int i);

    int getState() { return state; };

    void notify();

    virtual ~ConcreteSubject();
};

class PhaseObserver : public Observer
{
    ConcreteSubject *phase_subject;

public:
    PhaseObserver(ConcreteSubject *passed_phase_subject);

    void update();

    virtual ~PhaseObserver();
};

class GameStatisticsObserver : public Observer
{
    ConcreteSubject *game_observer_subject;

public:
    GameStatisticsObserver(ConcreteSubject *passed_game_observer_subject);

    void update();

    virtual ~GameStatisticsObserver();
};