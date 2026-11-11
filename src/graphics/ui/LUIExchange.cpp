#include "european_conquest/graphics/ui/LUIExchange.h"

namespace european_conquest
{

LUIExchange::LUIExchange() {}

void LUIExchange::updateGraphics(
    const Map& map, const std::vector<Player>& players, const GameState& gameState,
    std::unordered_map<TerritoryID, TerritoryGraphics>& territoryGraphicsMap,
    std::vector<PlayerGraphics>& playerGraphics, const GameSetupState* gameSetupState)
{
    // UPDATE TERRITORY GRAPHICS
    for (const auto& [territoryID, territory] : map.getTerritories())
    {
        auto graphicsTerritory = territoryGraphicsMap.find(territoryID);
        if (graphicsTerritory == territoryGraphicsMap.end()) continue;

        int troopCount = territory.getTroopCount();
        bool selected = false;

        // GAME SETUP PENDING TROOP
        if (gameSetupState != nullptr && gameSetupState->getTerritorySelected() == territoryID)
        {
            selected = true;
            troopCount++;
        }

        // REINFORCE PENDING TROOPS
        if (gameState.getPhase() == PhaseType::Reinforce &&
            gameState.getToTerritorySelection() == territoryID)
        {
            selected = true;
            troopCount += gameState.getLastReinforceOrder().getReinforceTroopCount();
        }

        // ATTACK TERRITORY SELECTIONS
        if (gameState.getPhase() == PhaseType::Attack)
        {
            if (gameState.getFromTerritorySelection() == territoryID) selected = true;
            if (gameState.getToTerritorySelection() == territoryID) selected = true;
        }

        // FORTIFY PENDING TROOPS
        if (gameState.getPhase() == PhaseType::Fortify)
        {
            if (gameState.getFromTerritorySelection() == territoryID)
            {
                selected = true;
                if (gameState.getToTerritorySelection() != TerritoryID::None)
                    troopCount -= gameState.getLastFortifyOrder().getFortifyTroopCount();
            }
            if (gameState.getToTerritorySelection() == territoryID)
            {
                selected = true;
                troopCount += gameState.getLastFortifyOrder().getFortifyTroopCount();
            }
        }

        auto& graphics = graphicsTerritory->second;
        graphics.setTroopCount(troopCount);

        const int ownerID = territory.getOwnerID();
        graphics.setPlayerID(ownerID);

        // Match the territory fill to its owner's chosen avatar.
        int avatarID = -1;
        for (const auto& graphicsPlayer : playerGraphics)
        {
            if (graphicsPlayer.getPlayerID() == ownerID)
            {
                avatarID = graphicsPlayer.getAvatarID();
                break;
            }
        }
        graphics.setFactionColour(avatarID);
        graphics.setSelected(selected);
    }

    // UPDATE PLAYER GRAPHICS
    for (const auto& player : players)
    {
        for (auto& graphicsPlayer : playerGraphics)
        {
            if (graphicsPlayer.getPlayerID() == player.getPlayerID())
            {
                graphicsPlayer.setTroopCount(player.getTroopCount());
                graphicsPlayer.setCardCount(static_cast<int>(player.getPlayerSet().size()));
                break;
            }
        }
    }
}

}  // namespace european_conquest
