# NFA Epsilon Transition Elimination

A C program that removes epsilon (ε) transitions from a Non-Deterministic Finite Automaton (NFA), producing an equivalent NFA without ε-transitions.

## Overview

This program implements the standard algorithm for eliminating epsilon transitions from NFAs. It's a fundamental step in automata theory, typically performed before converting an NFA to a DFA (Deterministic Finite Automaton).

## Features

- Read NFA with epsilon transitions from user input
- Calculate epsilon closure for each state using BFS
- Compute new transition table without epsilon transitions
- Determine new final states based on epsilon reachability
- Display the resulting NFA in a readable format

## How It Works

The program follows these steps:

1. **Read Input**: Takes the NFA definition including states, alphabet, transitions (including ε), and final states
2. **Compute ε-closures**: For each state, finds all states reachable via ε-transitions
3. **Build New Transitions**: Creates new transitions by following symbols after considering ε-closures
4. **Update Final States**: A state becomes final if it can reach any original final state via ε
5. **Display Output**: Shows the NFA without epsilon transitions

## Compilation

```bash
gcc epsilon_nfa.c -o epsilon_nfa
```

## Usage

Run the program:

```bash
./epsilon_nfa
```

### Input Format

The program will prompt you for:

1. Number of states
2. Number of input symbols (excluding epsilon)
3. Input symbols (e.g., `a b`)
4. Transitions for each state and symbol
   - For epsilon transitions, enter destination states when prompted for "epsilon"
   - For regular symbols, enter destination states or leave empty
5. Number of final states
6. Final state numbers

### Example

```
Nombre d'etats: 4
Nombre de symboles: 2
Entrer les symboles:
a b
Entrer les transitions:
Etat 0, epsilon: 1
Etat 0, a: 
Etat 0, b: 
Etat 1, epsilon: 
Etat 1, a: 2
Etat 1, b: 
Etat 2, epsilon: 3
Etat 2, a: 
Etat 2, b: 
Etat 3, epsilon: 
Etat 3, a: 
Etat 3, b: 3
Nombre d'etats finaux: 1
Etats finaux: 3
```

### Output

```
--- NFA sans epsilon ---

Etat    a       b       
0       {2}     {}      
1       {2}     {}      
2       {}      {3}     
3       {}      {3}     

Etats finaux: {0, 1, 2, 3}
```

## Algorithm Details

### Epsilon Closure Calculation

Uses Breadth-First Search (BFS) to find all states reachable from a given state via epsilon transitions:

```
ε-closure(q) = {q} ∪ {p | q →ε* p}
```

### New Transition Function

For each state and input symbol, the new transition is computed as:

```
δ'(q, a) = ε-closure(δ(ε-closure(q), a))
```

### New Final States

A state q is final in the new NFA if:

```
ε-closure(q) ∩ F ≠ ∅
```

where F is the set of original final states.

## Code Structure

- `read_nfa()` - Reads the NFA from user input
- `calc_epsilon_closure()` - Computes ε-closure for all states
- `calc_new_transitions()` - Builds transition table without ε
- `calc_new_final()` - Determines new final states
- `print_result()` - Displays the resulting NFA

## Limitations

- Maximum 20 states (can be increased by changing MAX constant)
- States are numbered from 0 to n-1
- Input symbols are single characters

## Test Cases Included

1. **Simple ε-chain**: NFA with epsilon transitions forming a chain
2. **Multiple ε-transitions**: State with epsilon transitions to multiple states
3. **No ε-transitions**: Verifies the program handles NFAs without epsilon transitions

## Authors

- HAMMOUDI DJAOUAD ABDERRAHMANE
- Kaarouche Mohamed Djamel Eddine


