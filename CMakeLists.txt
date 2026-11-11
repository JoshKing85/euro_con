
cmake_minimum_required(VERSION 3.14)

project(EuropeanConquest)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# FETCHCONTENT

include(FetchContent)

# SFML

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

set(BUILD_SHARED_LIBS ON)
FetchContent_MakeAvailable(SFML)
set(BUILD_SHARED_LIBS OFF)

# MAIN GAME EXECUTABLE

add_executable(EuropeanConquest

    src/main.cpp

    # Entities
    src/entities/Territory.cpp
    src/entities/Player.cpp
    src/entities/Card.cpp

    # World
    src/world/Region.cpp
    src/world/Map.cpp
    src/world/MapLoader.cpp
    src/world/Deck.cpp
    src/world/DeckLoader.cpp
    src/world/FeatureLoader.cpp

    # Orders
    src/core/orders/Order.cpp
    src/core/orders/AttackOrder.cpp
    src/core/orders/CashSetOrder.cpp
    src/core/orders/FortifyOrder.cpp
    src/core/orders/ReinforceOrder.cpp
    src/core/orders/RollDiceOrder.cpp
    src/core/orders/MoveTroopsOrder.cpp

    # Managers
    src/core/managers/GameStateManager.cpp
    src/core/managers/AttackManager.cpp
    src/core/managers/LogManager.cpp
    src/core/managers/TroopManager.cpp

    # Session
    src/core/session/GameInitializer.cpp
    src/core/session/GameSession.cpp
    src/core/session/GameState.cpp
    src/core/session/GameSetupState.cpp

    # Graphics elements
    src/graphics/game_elements/BoardGraphics.cpp
    src/graphics/game_elements/TerritoryGraphics.cpp
    src/graphics/game_elements/PlayerGraphics.cpp
    src/graphics/game_elements/CardGraphics.cpp
    src/graphics/game_elements/FeatureGraphics.cpp

    # Graphics UI
    src/graphics/ui/GameWindow.cpp
    src/graphics/ui/MenuUI.cpp
    src/graphics/ui/LUIExchange.cpp
    src/graphics/ui/LoadingUI.cpp
    src/graphics/ui/ProfileUI.cpp
    src/graphics/ui/GameSessionUI.cpp
    src/graphics/ui/GameSetupUI.cpp
    src/graphics/ui/ReinforceUI.cpp
    src/graphics/ui/AttackUI.cpp
    src/graphics/ui/FortifyUI.cpp

    # Graphics components
    src/graphics/components/PlayerIndicator.cpp
    src/graphics/components/SetupControls.cpp
    src/graphics/components/RegionValueBoard.cpp
    src/graphics/components/ReinforceControls.cpp
    src/graphics/components/CardContainer.cpp
    src/graphics/components/PreAttack.cpp
    src/graphics/components/AttackWindow.cpp
    src/graphics/components/FortifyControls.cpp
    src/graphics/components/MapSelector.cpp
    src/graphics/components/DebugGrid.cpp
    src/graphics/components/FineMesh.cpp

    # Validation
    src/core/validation/ValidateTerritorySelection.cpp
    src/core/validation/ValidateAttackInput.cpp
    src/core/validation/ValidateDiceInput.cpp
    src/core/validation/ValidateTroopCountInput.cpp
    src/core/validation/ValidateSetInput.cpp
    src/core/validation/ValidateFortifyInput.cpp
    src/core/validation/ValidateAttackSelection.cpp

    # Utilities
    src/utils/TerritoryConverter.cpp
    src/utils/RegionConverter.cpp
    src/utils/PolygonTriangulator.cpp
)

target_include_directories(EuropeanConquest PRIVATE
    include
)

target_link_libraries(EuropeanConquest PRIVATE
    SFML::Graphics
)

# RUNTIME FILES

add_custom_command(TARGET EuropeanConquest PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SFML::Graphics>
        $<TARGET_FILE:SFML::Window>
        $<TARGET_FILE:SFML::System>
        $<TARGET_FILE_DIR:EuropeanConquest>
)

add_custom_command(TARGET EuropeanConquest POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/data"
        "$<TARGET_FILE_DIR:EuropeanConquest>/data"
)

# GOOGLE TEST

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

# TEST EXECUTABLE

add_executable(unit_tests

    # Entity tests
    tests/entityTests/CardTests.cpp
    tests/entityTests/PlayerTests.cpp
    tests/entityTests/TerritoryTests.cpp

    # World tests
    tests/worldTests/RegionTests.cpp
    tests/worldTests/DeckTests.cpp
    tests/worldTests/DeckLoaderTests.cpp
    tests/worldTests/MapTests.cpp
    tests/worldTests/MapLoaderTests.cpp

    # Order tests
    tests/coreTests/orderTests/AttackOrderTests.cpp
    tests/coreTests/orderTests/CashSetOrderTests.cpp
    tests/coreTests/orderTests/FortifyOrderTests.cpp
    tests/coreTests/orderTests/ReinforceOrderTests.cpp
    tests/coreTests/orderTests/RollDiceOrderTests.cpp
    tests/coreTests/orderTests/MoveTroopsOrderTests.cpp

    # Manager tests
    tests/coreTests/managerTests/GameStateManagerTests.cpp
    tests/coreTests/managerTests/AttackManagerTests.cpp
    tests/coreTests/managerTests/TroopManagerTests.cpp

    # Session tests
    tests/coreTests/sessionTests/GameInitializerTests.cpp

    # Validation tests
    tests/coreTests/validationTests/ValidationTests.cpp

    # Entity implementations
    src/entities/Card.cpp
    src/entities/Player.cpp
    src/entities/Territory.cpp

    # World implementations
    src/world/Region.cpp
    src/world/Deck.cpp
    src/world/DeckLoader.cpp
    src/world/Map.cpp
    src/world/MapLoader.cpp

    # Order implementations
    src/core/orders/Order.cpp
    src/core/orders/AttackOrder.cpp
    src/core/orders/CashSetOrder.cpp
    src/core/orders/FortifyOrder.cpp
    src/core/orders/ReinforceOrder.cpp
    src/core/orders/RollDiceOrder.cpp
    src/core/orders/MoveTroopsOrder.cpp

    # Manager implementations
    src/core/managers/GameStateManager.cpp
    src/core/managers/AttackManager.cpp
    src/core/managers/TroopManager.cpp

    # Session implementations
    src/core/session/GameInitializer.cpp

    # Validation implementations
    src/core/validation/ValidateTerritorySelection.cpp
    src/core/validation/ValidateAttackInput.cpp
    src/core/validation/ValidateDiceInput.cpp
    src/core/validation/ValidateTroopCountInput.cpp
    src/core/validation/ValidateSetInput.cpp
    src/core/validation/ValidateFortifyInput.cpp
    src/core/validation/ValidateAttackSelection.cpp

    # Utility implementations
    src/utils/RegionConverter.cpp
    src/utils/TerritoryConverter.cpp
)

target_include_directories(unit_tests PRIVATE
    include
)

target_link_libraries(unit_tests PRIVATE
    GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(unit_tests)
