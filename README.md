# European Conquest

# European Conquest

European Conquest is a Napoleonic-era, turn-based strategy game developed in C++17 using SFML 3.

Inspired by classic territory-conquest board games, the project focuses on modular software architecture, 
object-oriented design, game-state management and algorithmic decision-making.

Developed independently as a software engineering portfolio project, incorporating AI-assisted development.


**Development status:** Active Development — core gameplay implemented, Game Interface under development,  AI opponents planned late this year.

## Screenshots

*Screenshots of the current game interface will be added here.*

Suggested screenshots:
- Main menu and map selection
- Player profile configuration
- European campaign map
- Reinforcement and attack interfaces

## Features

### Implemented

- **Turn-based gameplay:** Structured game phases for setup, reinforcement, attack and fortification.
- **Territory management:** Ownership, troop allocation, adjacency and regional control.
- **Combat system:** Dice-based attack resolution, troop losses and territory capture.
- **Reinforcement and fortification:** Troop deployment and movement between eligible territories.
- **Card mechanics:** Territory cards, card-set validation and reinforcement rewards.
- **JSON-driven map:** External configuration of territories, regions, connections and strategic bonuses.

- **Order-based actions:** Dedicated order objects representing gameplay operations.
- 
### Under Development
- **Graphical interface:** Custom SFML interface with interactive territories, player panels and phase-specific controls.
- 
### Planned

- AI-controlled opponents with strategic decision-making.
- Improved AI difficulty and decision evaluation.
- Additional gameplay balancing and interface refinements.
- Expanded automated testing and regression coverage.

## Technologies

| Technology | Purpose |
|---|---|
| C++17 | Core application and game logic |
| SFML 3.1 | Rendering, window management and user interaction |
| CMake | Build configuration and dependency management |
| Google Test | Unit testing |
| JSON | External map and configuration data |
| Visual Studio 2022 | Primary development environment |


## Software Architecture
European Conquest follows a modular, object-oriented architecture built around the separation of presentation, gameplay coordination and domain logic.

A central architectural principle is the mirroring of domain and presentation state through two separate containers.

The domain container maintains the authoritative game state, including territory ownership, troop counts, player information and gameplay rules. 
The presentation container maintains the corresponding graphical representation, including territory colours, 
displayed troop counts, player panels and UI indicators.

These containers are coordinated through a unidirectional, cyclical data flow. Player interactions initiate requests to the domain through GameSession, 
where gameplay operations are validated and executed. The domain state changes are transferred to the presentation container, 
ensuring that the graphical representation remains consistent with the literal game state.

This separation allows gameplay logic and graphical rendering to evolve independently.

Player Input → UI → GameSession → Validation / Domain Managers → State Update → Presentation Refresh



### Presentation Layer

The graphical interface is implemented using SFML.

Phase-specific UI classes manage user interaction and visual presentation, including reinforcement, combat and fortification controls.

Graphics components are responsible for rendering territories, player information, cards and interactive controls.

### Game Session and State Management

`GameSession` coordinates the active game, providing a central interface between the graphical layer and the underlying game systems.

`GameState` maintains turn-specific information, including the current phase, player selections and pending gameplay actions.

### Domain and Game Logic

Dedicated manager classes implement gameplay operations:

- `GameStateManager` — territory ownership, troop updates and player elimination.
- `AttackManager` — attack orders, dice resolution and territory capture.
- `TroopManager` — reinforcement, fortification and card-set operations.
- `LogManager` — gameplay order logging.

Gameplay actions are represented by order objects, allowing operations to be created, validated and processed through dedicated systems.

### World and Data Management

The world model contains territories, regions, players and cards.

Map and data-loading components construct the game world from external JSON configuration files, separating map content from the executable gameplay logic.

### Architecture Diagram

*Insert system architecture diagram here.*

## Gameplay

A standard player turn follows four principal stages:

1. **Setup:** Players receive territories and deploy their initial armies.
2. **Reinforcement:** Additional troops are allocated according to territory ownership, regional bonuses and applicable card rewards.
3. **Attack:** Players attack adjacent enemy territories, with combat outcomes determined through dice rolls.
4. **Fortification:** Players reposition eligible troops between connected territories they control.

After fortification, play proceeds to the next active player.

### Combat Resolution

Combat is resolved by rolling attacker and defender dice, sorting the results and comparing corresponding values.

The defender wins tied comparisons. Troop losses are applied according to the outcome, and successful territory captures update ownership and initiate troop movement.

*Insert combat data-flow diagram here.*

## Project Structure

```text
EuropeanConquest/
├── include/european_conquest/
│   ├── core/
│   │   ├── managers/
│   │   ├── orders/
│   │   ├── session/
│   │   └── validation/
│   ├── entities/
│   ├── graphics/
│   │   ├── components/
│   │   ├── game_elements/
│   │   └── ui/
│   ├── utils/
│   └── world/
├── src/
│   ├── core/
│   ├── entities/
│   ├── graphics/
│   ├── utils/
│   └── world/
├── data/
│   └── graphics/
├── tests/
├── CMakeLists.txt
└── README.md
```

## Building and Running

### Requirements

- A C++17-compatible compiler
- CMake 3.14 or later
- Git
- Internet access during initial dependency configuration

SFML and Google Test are retrieved through CMake's `FetchContent` mechanism.

### Build Instructions

Clone the repository:

```bash
git clone https://github.com/<username>/<repository>.git
cd <repository>
```

Configure the project:

```bash
cmake -S . -B build
```

Build the application:

```bash
cmake --build build --config Release
```

On Windows with the Visual Studio generator, the executable is typically located at:

```text
build/Release/EuropeanConquest.exe
```

The build configuration copies the required game data into the executable directory.

## Testing

Unit tests are implemented using Google Test and cover components of the game domain, including:

- Entity behaviour and state changes
- World and map construction
- Order creation and validation
- Combat and troop management
- Game initialisation
- Gameplay input validation

Tests are configured as a separate `unit_tests` executable.

Build and run tests using:

```bash
cmake --build build --config Debug --target unit_tests
ctest --test-dir build -C Debug --output-on-failure
```

**Current status:** The test suite is undergoing verification following the migration to the European map and region-based domain model. Passing test coverage has not yet been confirmed.

## Development Roadmap

| Area | Status |
|---|---|
| Core domain architecture | Implemented |
| Game setup and player profiles | Implemented |
| Reinforcement phase | Implemented |
| Combat and territory capture | Implemented |
| Fortification phase | Implemented |
| European map and JSON loading | Implemented |
| Graphical interface | Implemented, ongoing refinement |
| Automated test verification | In progress |
| AI opponent decision-making | Planned |
| Gameplay balancing and final polish | Planned |

## Engineering Objectives

This project provides practical experience in:

- Designing and maintaining modular C++ applications.
- Applying object-oriented programming principles.
- Separating user-interface logic from domain behaviour.
- Managing complex turn-based application state.
- Representing game actions through order objects.
- Loading structured external data into domain models.
- Implementing and testing gameplay algorithms.
- Managing a multi-component project with CMake and Git.

The longer-term objective is to develop AI-controlled opponents capable of evaluating strategic positions, reinforcement priorities and attack decisions.

## Author

Developed independently with AI incorporated development, as a personal software engineering portfolio project.



- - object-oriented design
- modular architecture 
- game-state management 
- algorithmic decision-making.

**Development status:** Active Development — core gameplay implemented, Game Interface under development,  AI opponents planned late this year.

## Screenshots

*Screenshots of the current game interface will be added here.*

Suggested screenshots:
- Main menu and map selection
- Player profile configuration
- European campaign map
- Reinforcement and attack interfaces

## Features

### Implemented

- **Turn-based gameplay:** Structured game phases for setup, reinforcement, attack and fortification.
- **Territory management:** Ownership, troop allocation, adjacency and regional control.
- **Combat system:** Dice-based attack resolution, troop losses and territory capture.
- **Reinforcement and fortification:** Troop deployment and movement between eligible territories.
- **Card mechanics:** Territory cards, card-set validation and reinforcement rewards.
- **JSON-driven map:** External configuration of territories, regions, connections and strategic bonuses.

- **Order-based actions:** Dedicated order objects representing gameplay operations.
- 
### Under Development
- **Graphical interface:** Custom SFML interface with interactive territories, player panels and phase-specific controls.
- 
### Planned

- AI-controlled opponents with strategic decision-making.
- Improved AI difficulty and decision evaluation.
- Additional gameplay balancing and interface refinements.
- Expanded automated testing and regression coverage.

## Technologies

| Technology | Purpose |
|---|---|
| C++17 | Core application and game logic |
| SFML 3.1 | Rendering, window management and user interaction |
| CMake | Build configuration and dependency management |
| Google Test | Unit testing |
| JSON | External map and configuration data |
| Visual Studio 2022 | Primary development environment |


## Software Architecture
European Conquest follows a modular, object-oriented architecture built around the separation of presentation, gameplay coordination and domain logic.

A central architectural principle is the mirroring of domain and presentation state through two separate containers.

The domain container maintains the authoritative game state, including territory ownership, troop counts, player information and gameplay rules. 
The presentation container maintains the corresponding graphical representation, including territory colours, 
displayed troop counts, player panels and UI indicators.

These containers are coordinated through a unidirectional, cyclical data flow. Player interactions initiate requests to the domain through GameSession, 
where gameplay operations are validated and executed. The domain state changes are transferred to the presentation container, 
ensuring that the graphical representation remains consistent with the literal game state.

This separation allows gameplay logic and graphical rendering to evolve independently.

Player Input → UI → GameSession → Validation / Domain Managers → State Update → Presentation Refresh



### Presentation Layer

The graphical interface is implemented using SFML.

Phase-specific UI classes manage user interaction and visual presentation, including reinforcement, combat and fortification controls.

Graphics components are responsible for rendering territories, player information, cards and interactive controls.

### Game Session and State Management

`GameSession` coordinates the active game, providing a central interface between the graphical layer and the underlying game systems.

`GameState` maintains turn-specific information, including the current phase, player selections and pending gameplay actions.

### Domain and Game Logic

Dedicated manager classes implement gameplay operations:

- `GameStateManager` — territory ownership, troop updates and player elimination.
- `AttackManager` — attack orders, dice resolution and territory capture.
- `TroopManager` — reinforcement, fortification and card-set operations.
- `LogManager` — gameplay order logging.

Gameplay actions are represented by order objects, allowing operations to be created, validated and processed through dedicated systems.

### World and Data Management

The world model contains territories, regions, players and cards.

Map and data-loading components construct the game world from external JSON configuration files, separating map content from the executable gameplay logic.

### Architecture Diagram

*Insert system architecture diagram here.*

## Gameplay

A standard player turn follows four principal stages:

1. **Setup:** Players receive territories and deploy their initial armies.
2. **Reinforcement:** Additional troops are allocated according to territory ownership, regional bonuses and applicable card rewards.
3. **Attack:** Players attack adjacent enemy territories, with combat outcomes determined through dice rolls.
4. **Fortification:** Players reposition eligible troops between connected territories they control.

After fortification, play proceeds to the next active player.

### Combat Resolution

Combat is resolved by rolling attacker and defender dice, sorting the results and comparing corresponding values.

The defender wins tied comparisons. Troop losses are applied according to the outcome, and successful territory captures update ownership and initiate troop movement.

*Insert combat data-flow diagram here.*

## Project Structure

```text
EuropeanConquest/
├── include/european_conquest/
│   ├── core/
│   │   ├── managers/
│   │   ├── orders/
│   │   ├── session/
│   │   └── validation/
│   ├── entities/
│   ├── graphics/
│   │   ├── components/
│   │   ├── game_elements/
│   │   └── ui/
│   ├── utils/
│   └── world/
├── src/
│   ├── core/
│   ├── entities/
│   ├── graphics/
│   ├── utils/
│   └── world/
├── data/
│   └── graphics/
├── tests/
├── CMakeLists.txt
└── README.md
```

## Building and Running

### Requirements

- A C++17-compatible compiler
- CMake 3.14 or later
- Git
- Internet access during initial dependency configuration

SFML and Google Test are retrieved through CMake's `FetchContent` mechanism.

### Build Instructions

Clone the repository:

```bash
git clone https://github.com/<username>/<repository>.git
cd <repository>
```

Configure the project:

```bash
cmake -S . -B build
```

Build the application:

```bash
cmake --build build --config Release
```

On Windows with the Visual Studio generator, the executable is typically located at:

```text
build/Release/EuropeanConquest.exe
```

The build configuration copies the required game data into the executable directory.

## Testing

Unit tests are implemented using Google Test and cover components of the game domain, including:

- Entity behaviour and state changes
- World and map construction
- Order creation and validation
- Combat and troop management
- Game initialisation
- Gameplay input validation

Tests are configured as a separate `unit_tests` executable.

Build and run tests using:

```bash
cmake --build build --config Debug --target unit_tests
ctest --test-dir build -C Debug --output-on-failure
```

**Current status:** The test suite is undergoing verification following the migration to the European map and region-based domain model. Passing test coverage has not yet been confirmed.

## Development Roadmap

| Area | Status |
|---|---|
| Core domain architecture | Implemented |
| Game setup and player profiles | Implemented |
| Reinforcement phase | Implemented |
| Combat and territory capture | Implemented |
| Fortification phase | Implemented |
| European map and JSON loading | Implemented |
| Graphical interface | Implemented, ongoing refinement |
| Automated test verification | In progress |
| AI opponent decision-making | Planned |
| Gameplay balancing and final polish | Planned |

## Engineering Objectives

This project provides practical experience in:

- Designing and maintaining modular C++ applications.
- Applying object-oriented programming principles.
- Separating user-interface logic from domain behaviour.
- Managing complex turn-based application state.
- Representing game actions through order objects.
- Loading structured external data into domain models.
- Implementing and testing gameplay algorithms.
- Managing a multi-component project with CMake and Git.

The longer-term objective is to develop AI-controlled opponents capable of evaluating strategic positions, reinforcement priorities and attack decisions.

## Author

Developed independently with AI incorporated development, as a personal software engineering portfolio project.

