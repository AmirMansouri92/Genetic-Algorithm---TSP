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

### Steps

1. Clone this repository:
   ```bash
   git clone https://github.com/AmirMansouri92/Genetic-Algorithm---TSP
   cd Genetic-Algorithm---TSP

