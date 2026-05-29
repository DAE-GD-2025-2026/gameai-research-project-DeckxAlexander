# 🧠 GOAP Enemy AI

> Alexander Deckx

---

# 📖 What is GOAP?

**GOAP (Goal-Oriented Action Planning)** is a Stanford Research Institute Problem Solver that allows npc's to behave in a believable dynamic way. 
Instead of following scripted behaviours the agents make decisions based on goals they want to achieve during the game. Breaking down a complex task into a sequence of actions.
This sequence is dependant on both the state of the world and the state of the agent. Meaning that the actions of one agent might differ from the other.

---

## 🔫 F.E.A.R.
**First Encounter Assault Recon**, developed by Monolith Productions, was one of the earliest and most influential examples of GOAP in games. Instead of relying on a large FSM, agents dynamically calculated plans to achieve goals.
Each agent had multiple goals with dynamic priorities and a set of actions. Their action plans were continuously validated during planning and execution, since they could become invalid because of changes in the game world.
Once a plan was completed, the agent selected a new goal.

### Performance
In F.E.A.R., GOAP introduced a major drawback: performance overhead. 
Even the rats in the game used a GOAP-based AI system. 
Their behavior didn’t account for the player’s location, meaning they continued planning and executing actions even when the player was far away.

Also, since F.E.A.R. is a fast-paced shooter, the world state changed constantly. As a result, enemies often had to recalculate their action plans frequently, which became quite expensive.

---


# 🎮 Purpose of the Project

The project demonstrates how GOAP can create believable AI without relying heavily on scripted behaviors. 
Instead of using a large finite state machine or behavior tree, the program plans sequences of actions to achieve goals within the game.
The system is modular and highly customizable, making it a good solution for creating intelligent NPCs in games.

Each AI agent has the following behaviour:
- Clear hazards within the scene
- Sound the alarm when the player is spotted
- Kill the player when alerted

---

# ⚙️ Core System
A solid GOAP system consists of the following components:

## 🌍 (World) State

The AI-Controller holds the state of the agent and the world.
In this implementation the state is a map of names and booleans.
Based on these states the GOAP system generates a plan of **actions** to achieve a specific **goal**

Individual states are updated by the actions and the controller, while world states are updated by the gamemode.
Aside from this, there is no major distinction between a world state and an individual state.

### Examples (Individual states)
- HasAmmo
- SeesPlayer

### Examples (World states)
- AlarmOn
- HazardsInScene

---

## 🧩 Goals

A goal represents the objective the agent wants to achieve, or more specifically, the state the agent wants to reach.
The planner creates a sequence of actions intended to transform the agent’s current state into the goal state.

### Examples
- PlayerAlive *false*
- AreaSafe *false*
- HasAmmo *true*

Goals can be changed manually by the developer or dynamically in response to events that occur within the game, such as:
- An alarm being triggered
- The player dying


---

## 🔨 Actions

An action is a task performed by the agent.
Each action contains:
- Preconditions
- Effects
- Failed Effects
- Cost

The preconditions define the state the agent must be in before the action can be executed.
The effects are the changes of the agent's state when the action finishes.
The cost is used by the planner to prioritize certain actions over others.
In this implementation, actions can either succeed or fail, both have effects on the state of the agent.

I decided to use inheritance for the actions. BaseAction contains Start and Tick functions, as well as IsApplicable, Apply, and ApplyFailed:

The IsApplicable function checks whether the agent’s current state satisfies the conditions required for the action.
The Apply and ApplyFailed functions update the agent’s state based on the outcome of the action, either when it succeeds or when it fails.

![Action Code](RepoImages/ActionCode.png)

---

## 🗒️ Planner

The planner is the core system that drives the entire process.
It calculates a sequence of actions by using an A* algorithm to determine the most efficient plan for reaching the desired goal.

The GOAP planner is an A* planner where each node contains a state, GCost, HCost, a plan, and a list of remaining actions. Since each action can only be performed once, actions are removed from the remaining action list after being used.

The planner iterates over the open set, which initially contains only the start node. The open set is sorted based on the total cost, and each node is checked to determine whether the goal has already been reached or whether the GCost exceeds the allowed limit.

Afterwards, the planner iterates over the remaining actions and creates child nodes for the actions whose preconditions are satisfied. These child nodes are then added to the open set.

![Planner Code](RepoImages/PlannerCode.png)

![Planner Image](RepoImages/PlannerImage.png)
---

## 🧠 Controller

The agent’s AI Controller also contains additional logic.
It recalculates the plan whenever a meaningful world state changes or when an action fails.

The controller also maintains the list of available actions and, in this implementation, includes an idle-action failsafe in case no valid plan can be found or the current goal has already been achieved.

In this implementation, the controller also contains logic to determine whether the agent can see the player within the required range.

When an action finishes, it must call either ProcessSuccess or ProcessFailure on the controller. The controller will then either recalculate the plan or continue to the next action.

![Process Code](RepoImages/ProcessFinsihCode.png)

Before executing the next action, the controller checks again whether the action is still applicable and, in this implementation, whether the player is still within shooting range.

As a failsafe, the controller always sets the current action to the idle action while calculating or switching to another action.

![ExecuteNext Code](RepoImages/ExecuteNextCode.png)

---


# 🔫 Implementation

The idea behind the current implementation is that agents aim to make the environment safe by clearing hazards and eliminating players on sight.

## ☣️ Hazard Clearing

The agents begin by clearing hazards in the scene, picking them up and transporting them to the garbage disposal area.

![Hazard Image](RepoImages/HazardsImage.png)

---

## 👁️ Detection

Each agent has a pawn sensing component. If this component detects a player, the agent becomes alerted and is assigned a new goal: "to sound the alarm".

---

## 🚨 Alarm

When the alarm is triggered, all agents become alerted and are assigned the goal of eliminating the player.

![Alarm Image](RepoImages/AlarmImage.png)

---

## 🏃 Pursuit

The agents first attempt to acquire ammunition or a melee weapon, prioritizing ammo.
Once equipped, they move into range of the player and attempt to attack. 
If an attack misses, they lose their current weapon or ammo and will seek out a replacement before trying again.

![Alarm Image](RepoImages/PursuitImage.png)

---

## 💀 Player 

The player is a purple cube controlled with the WASD keys.
If the player dies, the agents return to their primary task of clearing hazards in the scene.

![Alarm Image](RepoImages/PlayerImage.png)

---

# 🕒 Future Improvements

There are a couple of possible future improvements, such as:

### Adding a dynamic goal-selection system based on world state and priorities

At the moment, goals are manually assigned by the game mode or the developer. For more believable AI behavior, goals should change dynamically according to the current world state and changing priorities.

### Implement a Finite State Machine (FSM)

F.E.A.R. used an FSM with its GOAP system. The FSM consisted of three states: Animate, Go To, and Use Smart Object. A similar approach could work very well for this project.

### Create a system that makes the planner more performance friendly

As mentioned earlier, F.E.A.R. experienced performance issues because constantly changing world states forced enemies to frequently recalculate their action plans. 
A similar issue could arise in this project if the worldstates change more. 

Therefore, it would be nice to implement a system that ensures that the agents only recalculate their plans when its absolutely necessary.
Or, maybe a system that doesnt recalculate the entire plans but only certain parts of the plan.

---

# 🛠️ Technical Features

- Unreal Engine 5
- Unreal C++
- GOAP A* Planner
- Pawn Sensing
- Navigation Mesh

---

# 📖 Sources

[Goal Oriented Action Planning - Vedant Chaudhari](https://medium.com/@vedantchaudhari/goal-oriented-action-planning-34035ed40d0b)

[GOAP - CrashKonijn](https://goap.crashkonijn.com/)

[AI in F.E.A.R - AI and Games](https://www.youtube.com/watch?v=PaOLBOuyswI)

---

