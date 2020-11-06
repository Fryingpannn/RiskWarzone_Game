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


class Observer
{
public:
    void update();
};

struct State
{
    // TODO Determine what needs to be here
};

class Subject
{
private:
    int state = 0;

protected:
    std::vector<Observer *> obs;

public:
    void attach(Observer *o) { obs.push_back(o); }

    void detach(Observer *o)
    {
        obs.erase(std::remove(obs.begin(), obs.end(), o), obs.end());
    }

    void notify()
    {
        // Copy the current observer list to a clone to avoid one being deleted mid-operation
        std::vector<Observer *> obs_clone;
        for (auto obs_item : obs) 
            obs_clone.push_back(new Observer(*obs_item));

        // Update all the observers
        for (auto o : obs_clone)
        {
            o->update();
        }

        // Delete the clone
        for (auto o : obs_clone)
            delete o;
        obs_clone.clear();
    }

    ~Subject() {
        std::cout << "Deleting Observer Subject" << std::endl;
    };
};



class ConcreteSubject : public Subject
{
    int state = 0;

public:
    ConcreteSubject(int i) : state(i){};

    void setState(int i) { state = i; };

    int getState() { return state; };

    void notify()
    {
        // Copy the current observer list to a clone to avoid one being deleted mid-operation
        std::vector<Observer *> obs_clone;
        for (auto obs_item : obs) 
            obs_clone.push_back(new Observer(*obs_item));

        // Update all the observers
        for (auto o : obs_clone)
        {
            o->update();
        }

        // Delete the clone
        for (auto o : obs_clone)
            delete o;
        obs_clone.clear();
    }

    virtual ~ConcreteSubject() {
        std::cout << "Deleting ConcreteSubject" << std::endl;
    }
};

class PhaseObserver : public Observer
{
    ConcreteSubject *phase_subject;

public:
    PhaseObserver(ConcreteSubject *passed_phase_subject)
    {
        phase_subject = passed_phase_subject;
    };

    void update()
    {
        std::cout << "Game Statistics Observer Updating" << std::endl;
    };

    virtual ~PhaseObserver() {
        std::cout << "Deleting PhaseObserver" << std::endl;
    }
};

class GameStatisticsObserver : public Observer
{
    ConcreteSubject *game_observer_subject;

public:
    GameStatisticsObserver(ConcreteSubject *passed_game_observer_subject)
    {
        game_observer_subject = passed_game_observer_subject;
    };

    void update()
    {
        std::cout << "Phase Observer Updating" << std::endl;
    };

    virtual ~GameStatisticsObserver() {
        std::cout << "Deleting GameStatisticsObserver." << std::endl;
    }
};