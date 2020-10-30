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

// abstract classes
class Observer;

struct State{
    // TODO Determine what needs to be here
};

class Subject {
protected:
  std::vector<Observer *> obs;

public:
  void attach(Observer *o) { obs.push_back(o); }

  void detach(Observer *o) {
    obs.erase(std::remove(obs.begin(), obs.end(), o), obs.end());
  }

  virtual void notify() = 0;
};

class Observer {
public:
  virtual void update() = 0;
};

class ConcreteSubject : public Subject {
  int state = 0;

public:
  ConcreteSubject(int i) : state(i){};

  void setState(int i) { state = i; };

  int getState() { return state; };

  void notify() {
    for (auto o : obs) {
      o->update();
    }
  }
};

class PhaseObserver : public Observer {
    void update() {
        std::cout << "Phase Observer Updating" << std::endl;
    };
};

class GameStatisticsObserver : public Observer {
    void update() {
        std::cout << "Game Statistics Observer Updating" << std::endl;
    };
};