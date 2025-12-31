# Eliminating ε-Transitions from an NFA

This is a C program that takes an NFA (Non-deterministic Finite Automaton) with epsilon transitions and converts it into an NFA without epsilon transitions.

## What it does

When you run the program, it asks you to enter your NFA step by step. Then it figures out all the epsilon closures and creates new transitions to replace the epsilon ones. At the end, it shows you a table with the new NFA that works exactly the same but without any epsilon transitions.

## How to compile and run

To compile:
```
gcc "Eliminating ε-Transitions from an NFA.c" -o nfa
```

To run:
```
./nfa
```

## What you need to enter

The program will ask you for:
1. Number of states in your NFA
2. Number of input symbols (like a, b, c, etc. - not counting epsilon)
3. The input symbols themselves
4. For each state and each symbol (including epsilon), which states you can reach

Just follow the prompts and enter the information. If there are no transitions for a particular state and symbol, just press enter.

## Example

Let's say you have 3 states (0, 1, 2) and two symbols (a, b). Your transitions are:
- From state 0 with epsilon: go to state 1
- From state 1 with 'a': go to state 2
- From state 2 with 'b': go to state 2

The program will show you that state 0 can now go directly to state 2 with 'a' (since it could reach state 1 via epsilon first). The epsilon transition is gone!

## Authors

HAMMOUDI DJAOUAD ABDERRAHMANE G02 Security
Kaarouche Mohamed Djamel Eddine G02 Security

