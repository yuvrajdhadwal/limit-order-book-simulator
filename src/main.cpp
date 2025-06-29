#include <iostream>
#include "MatchingEngine.hpp"

int main() {
    MatchingEngine engine;

    engine.placeLimitOrder(Order{1, Side::SELL, 100, 10.5, 1000});
    engine.placeLimitOrder(Order{2, Side::SELL, 50, 10.0, 1001});
    engine.placeLimitOrder(Order{3, Side::SELL, 150, 10.2, 1002});

    engine.placeLimitOrder(Order{4, Side::BUY, 180, 10.3, 1003});

    engine.placeMarketOrder(Order{5, Side::BUY, 30, 0.0, 1004});

    engine.cancelOrder(1);

    engine.placeLimitOrder(Order{6, Side::BUY, 100, 10.1, 1005});
    engine.placeMarketOrder(Order{7, Side::SELL, 60, 0.0, 1006});
    return 0;
}
