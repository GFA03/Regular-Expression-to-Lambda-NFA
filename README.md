# C++ Regular Expressions Project

Welcome to the Regular Expressions to Lambda NFA project in C++! This project focuses on implementing Regular Expressions and Lambda NFA using classes. The goal is to transform a given regular expression into a Lambda NFA (Nondeterministic Finite Automaton) representation.

## Table of Contents

- [Features](#features)
- [Getting Started](#getting-started)
  - [Prerequisites](#prerequisites)
  - [Installation](#installation)
- [Usage](#usage)
- [Classes](#classes)
- [Examples](#examples)

## Features

1. **LambdaNFA Class:** A class representing a Lambda NFA with methods to define states, transitions, and evaluate strings.

2. **RegularExpression Class:** A class for working with regular expressions, including methods to parse and convert a regular expression into a Lambda NFA.

3. **Transformation:** The project provides functionality to transform a regular expression into a corresponding Lambda NFA for further analysis and processing.

## Getting Started

### Prerequisites

- C++ compiler (Supporting C++11 or later)

### Installation

1. Clone the repository:

```bash
git clone https://github.com/GFA03/Regular-Expression-to-Lambda-NFA.git
```

2. Compile the main solution:
```bash
g++ -std=c++17 -o main main.cpp lambda-nfa.cpp regular-expression.cpp
```

3. Enjoy the project
```bash
./main
```

## Usage

1. Open the main program and write a Regular Expression. The program will do its job.

## Classes

### LambdaNFA Class

The `LambdaNFA` class provides methods for working with Lambda NFAs, including state and transition management, and string evaluation.

### RegularExpression Class

The `RegularExpression` class is designed to handle regular expressions, with methods for parsing and transforming expressions into Lambda NFAs.

## Examples

Here's a simple example of using the Regular Expressions project:
```bash
./main
a+b+c
abc++
Automata nodes: 0 1 2 3 4 5 6 7
Initial state: 0
Final states: 2 5 7
Transitions:
0 # 3 1
1 a 2
3 # 4 6
4 b 5
6 c 7
```

