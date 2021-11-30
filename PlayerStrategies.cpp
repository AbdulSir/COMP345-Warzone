#include "PlayerStrategies.h"

PlayerStrategy::PlayerStrategy(Player* p) {
    this->p = p;
}

Neutral::Neutral(Player* p): PlayerStrategy(p) {}

Cheater::Cheater(Player* p): PlayerStrategy(p) {}

Human::Human(Player* p): PlayerStrategy(p) {}

Agressive::Agressive(Player* p): PlayerStrategy(p) {}

Benevolent::Benevolent(Player* p): PlayerStrategy(p) {}