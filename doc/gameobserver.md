## Part 5: Observers

Provide a group of C++ classes that implements observers who are used to display information to the user as the game is being played. The user shall have the option to turn on/off any of the two observers during the game start phase (see Part 1).

### Phase Observer

Using the Observer design pattern, implement a view that displays information happening in the current phase. It should first display a header showing what player and what phase is currently being played, e.g. “Player 3: Reinforcement phase” or “Player 1: Issue orders phase” Then it should display important information related to what is happening in this phase, which should be different depending on what phase is being played. This should dynamically be updated as the game goes through different players/phases and be visible at all times during game play. You must deliver a driver that demonstrates that 

1) the information displayed by the phase view is cleared every time the phase is changing 
2) the phase view is displaying the correct player:phase information as soon as the phase changes; 
3) the phase view displays relevant information which is different for every phase. The Observer and Observable classes code must be implemented in the `GameObservers.cpp/GameObservers.h` file duo.

### Game Statistics Observer

Using the Observer design pattern, implement a view that displays some useful statistics about the game, the minimum being a "players world domination view" that shows using some kind of graph or table depicting what percentage of the world is currently being controlled by each player. This should dynamically be updated as the map state changes and be visible at all times during game play. You must deliver a driver that demonstrates that
1) the game statistics view updates itself every time a country has been conquered by a player; 
2) the game statistics updates itself when a player has been eliminated and removes this player from the view; 
3) as soon asa player owns all the countries, the game statistics view updates itself and displays a celebratory message. The Observer and Observable classes code must be implemented in the `GameObservers.cpp/GameObservers.h` file duo.

---

### Phase Observer

#### Relavent information to display:
**Setup Phase**
- player assign territory

**Reinforcement Phase:**
- Number of troops to deploy

**Issuing Orders Phase:**
- player issuing which order

**Orders Execution Phase:**
- player executing which order and its effect


### Game Statistics Observer

#### Relavent Info to Display

---
Player1 has conquered &TERRITORY.

Player2 has been eliminated.

| Player | Status | Countries Owned | Percentage of World |
|---|---|---|---|
| Player1 | Active | 24 | 42% |
| Player2 | Eliminated | 0 | 0% |

Total Countries: 42

---
