#include "european_conquest/core/managers/TroopManager.h"
#include "european_conquest/core/managers/GameStateManager.h"

#include "european_conquest/core/orders/CashSetOrder.h"
#include "european_conquest/core/orders/FortifyOrder.h"
#include "european_conquest/core/orders/ReinforceOrder.h"

#include "european_conquest/entities/Card.h"
#include "european_conquest/entities/Player.h"
#include "european_conquest/entities/Territory.h"

#include <algorithm>
#include <vector>

namespace european_conquest {

    // CONSTRUCTOR

    TroopManager::TroopManager()
    {
    }

    // ORDER CREATION

    void TroopManager::createReinforceOrder(
        int playerID,
        TerritoryID territoryID,
        int reinforceTroopCount
    )
    {
        reinforceOrders.emplace_back(
            playerID,
            territoryID,
            reinforceTroopCount
        );
    }

    void TroopManager::createFortifyOrder(
        int playerID,
        TerritoryID fromTerritory,
        TerritoryID toTerritory,
        int fortifyTroopCount
    )
    {
        fortifyOrders.emplace_back(
            playerID,
            fromTerritory,
            toTerritory,
            fortifyTroopCount
        );
    }

    void TroopManager::createCashSetOrder(
        int playerID,
        SetType setType,
        std::vector<Card> cards
    )
    {
        cashSetOrders.emplace_back(
            playerID,
            setType,
            cards
        );
    }

    // REINFORCEMENT CALCULATION

    int TroopManager::calculateReinforcements(
        const Player& player
    )
    {
        const std::vector<TerritoryID>& playerTerritories =
            player.getTerritoriesHeld();

        return std::max(
            3,
            static_cast<int>(playerTerritories.size()) / 3
        );
    }

    // REINFORCEMENT EXECUTION

    void TroopManager::executeReinforceOrder(
        GameStateManager& gameStateManager
    )
    {
        ReinforceOrder& currentReinforceOrder =
            reinforceOrders.back();

        gameStateManager.updateTerritoryTroopCount(
            currentReinforceOrder.getTerritoryID(),
            currentReinforceOrder.getReinforceTroopCount()
        );

        gameStateManager.updatePlayerTroopCount(
            currentReinforceOrder.getPlayerID(),
            currentReinforceOrder.getReinforceTroopCount()
        );

        currentReinforceOrder.complete();
    }

    // FORTIFICATION EXECUTION

    void TroopManager::executeFortifyOrder(
        GameStateManager& gameStateManager
    )
    {
        FortifyOrder& currentFortifyOrder =
            fortifyOrders.back();

        gameStateManager.updateTerritoryTroopCount(
            currentFortifyOrder.getFromTerritory(),
            -currentFortifyOrder.getFortifyTroopCount()
        );

        gameStateManager.updateTerritoryTroopCount(
            currentFortifyOrder.getToTerritory(),
            currentFortifyOrder.getFortifyTroopCount()
        );

        currentFortifyOrder.complete();
    }

    // CASH-SET EXECUTION

    int TroopManager::executeCashSetOrder(
        const Player& player,
        GameStateManager& gameStateManager
    )
    {
        CashSetOrder& currentCashSetOrder =
            cashSetOrders.back();

        std::vector<Card> currentPlayerSet =
            player.getPlayerSet();

        std::vector<Card> cardsToRemove =
            currentCashSetOrder.getCards();

        // remove each cashed card from the player's hand

        for (const Card& cardToRemove : cardsToRemove)
        {
            auto it = std::find_if(
                currentPlayerSet.begin(),
                currentPlayerSet.end(),
                [&](const Card& playerCard)
                {
                    return
                        playerCard.getCardType() ==
                        cardToRemove.getCardType()
                        &&
                        playerCard.getTerritoryID() ==
                        cardToRemove.getTerritoryID()
                        &&
                        playerCard.getRegionID() ==
                        cardToRemove.getRegionID();
                }
            );

            if (it != currentPlayerSet.end())
            {
                currentPlayerSet.erase(it);
            }
        }

        // apply updated player state

        gameStateManager.updatePlayerSet(
            currentCashSetOrder.getPlayerID(),
            currentPlayerSet
        );

        // complete order

        currentCashSetOrder.complete();

        return currentCashSetOrder.getSetValue();
    }

    // UNDO REINFORCEMENT

    void TroopManager::undoReinforceOrder()
    {
        if (!reinforceOrders.empty())
        {
            reinforceOrders.pop_back();
        }
    }

    // UNDO FORTIFICATION

    void TroopManager::undoFortifyOrder()
    {
        if (!fortifyOrders.empty())
        {
            fortifyOrders.pop_back();
        }
    }

    // UNDO CASH SET

    void TroopManager::undoCashSetOrder()
    {
        if (!cashSetOrders.empty())
        {
            cashSetOrders.pop_back();
        }
    }

    // CLEAR ORDERS

    void TroopManager::clearOrders()
    {
        reinforceOrders.clear();
        fortifyOrders.clear();
        cashSetOrders.clear();
    }

    // UPDATE REINFORCEMENT

    void TroopManager::updateReinforceOrder(
        bool add
    )
    {
        ReinforceOrder& currentReinforceOrder =
            reinforceOrders.back();

        if (!currentReinforceOrder.isCompleted())
        {
            int troopCount =
                currentReinforceOrder.getReinforceTroopCount();

            if (add)
            {
                troopCount++;
            }
            else
            {
                troopCount--;
            }

            currentReinforceOrder.setReinforceTroopCount(
                troopCount
            );
        }
    }
    // UPDATE FORTIFICATION

    void TroopManager::updateFortifyOrder(
        bool add
    )
    {
        FortifyOrder& currentFortifyOrder =
            fortifyOrders.back();

        if (!currentFortifyOrder.isCompleted())
        {
            currentFortifyOrder.updateFortifyOrder(add);
        }
    }

    // GETTERS

    const std::vector<ReinforceOrder>&
        TroopManager::getReinforceOrders() const
    {
        return reinforceOrders;
    }

    const std::vector<FortifyOrder>&
        TroopManager::getFortifyOrders() const
    {
        return fortifyOrders;
    }

    const std::vector<CashSetOrder>&
        TroopManager::getCashSetOrders() const
    {
        return cashSetOrders;
    }

    const ReinforceOrder&
        TroopManager::getLastReinforceOrder() const
    {
        return reinforceOrders.back();
    }

    const FortifyOrder&
        TroopManager::getLastFortifyOrder() const
    {
        return fortifyOrders.back();
    }

    const CashSetOrder&
        TroopManager::getLastCashSetOrder() const
    {
        return cashSetOrders.back();
    }

} // namespace european_conquest