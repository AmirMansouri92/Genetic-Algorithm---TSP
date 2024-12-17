# TSP Solver Using Genetic Algorithm

This repository contains a C++ implementation of the Traveling Salesperson Problem (TSP) using Genetic Algorithms (GA). The goal is to find an optimal or near-optimal route that visits a set of cities exactly once and returns to the starting city, minimizing the total distance.

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Algorithm Overview](#algorithm-overview)
  - [Encoding](#encoding)
  - [Selection](#selection)
  - [Crossover](#crossover)
  - [Mutation](#mutation)
- [Results](#results)
- [Future Work](#future-work)
- [Contributing](#contributing)
- [License](#license)
- [references] (#references)

## Introduction

The Traveling Salesperson Problem (TSP) is a classic optimization problem in computer science and operations research. Due to its NP-hard nature, exact solutions become computationally expensive as the number of cities increases. Genetic Algorithms (GAs) provide a heuristic approach to solving TSP efficiently for larger datasets.

## Features

- Flexible input for defining cities and distances.
- Customizable genetic algorithm parameters:
  - Population size
  - Crossover and mutation rates
  - Number of generations
- Visual representation of results (optional with graphical libraries).
- Outputs the best route and its total distance.

## Installation

### Prerequisites

- A C++17 compatible compiler (e.g., GCC, Clang, MSVC)
- [CMake](https://cmake.org/) for build management
- [SFML](https://www.sfml-dev.org/) (optional, for visualization)

## Algorithm Overview
In this section I describe the methods used for mutation and crossover. 
### crossover
According to [[1]](#1),  I use the standard crossover method, which creates offspring by selecting a subsequence of genes from parent 1 and preserving the relative order of the remaining cities from parent 2.

To illustrate how this works, consider the following parents:
genes1 = [1, 2, 3, 4, 0] (parent 1)
genes2 = [1, 0, 4, 3, 2] (parent 2)

Next, we generate two random numbers representing the starting and ending indexes of the subsequence. Suppose the random numbers are 1 and 2. This means the offspring will inherit the cities at index 1 (city 2) and index 2 (city 3) from parent 1. Since the first city is already fixed, the initial state of the offspring becomes:
offspring = [1, 2, 3, -, -]

Now, we preserve the relative order of the remaining cities from parent 2. To achieve this, we start reordering parent 2 from the first city after index 2 (i.e., city 3). The updated order of cities from parent 2, starting at index 3 (city 3), is:
new_complete_order_of_parent2 = [3, 2, 1, 0, 4].

After removing the already inherited cities (1, 2, and 3), the reduced sequence becomes:
new_order_of_parent2 = [0, 4].

Finally, we fill in the missing slots in the offspring with the remaining cities from new_order_of_parent2 in their respective order. The completed offspring is:
offspring = [1, 2, 3, 0, 4].
### mutation
For mutation, we use a method called Twors, where the positions of two cities are randomly selected and swapped. For example, consider a gene sequence represented as genes = [1, 0, 3, 4, 2] (with its corresponding index vector being [0, 1, 2, 3, 4]).

Now, suppose two random numbers are generated, representing the indexes of the cities to be exchanged. Let’s say the random numbers are 2 and 4. This means that the cities at index 2 (city 3) and index 4 (city 2) are chosen to be swapped.

After the swap, the updated gene sequence becomes:
new_genes = [1, 0, 2, 4, 3].

Important tip: The position of the first city is never changed, as it has already been determined.

### Steps

1. Clone this repository:
   ```bash
   git clone https://github.com/AmirMansouri92/Genetic-Algorithm---TSP
   cd Genetic-Algorithm---TSP

## references
<a id="1">[1]</a> 
New Variations of Order Crossover for Travelling Salesman Problem
